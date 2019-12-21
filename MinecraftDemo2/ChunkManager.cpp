#include "ChunkManager.h"

int ChunkManager::FlattenIndex(glm::vec3 pos)
{
	return (pos.z * Dimensions.z * Dimensions.z) + (pos.y * Dimensions.y) + pos.x;
}

bool ChunkManager::isContainsIndex(glm::vec3 pos)
{
	return pos.x >= 0 && pos.x < Dimensions.x * ChunkDimensions.x && pos.y >= 0 && pos.y < Dimensions.y * ChunkDimensions.y && pos.z >= 0 && pos.z < Dimensions.z * ChunkDimensions.z;
}

int ChunkManager::getActualSide(int direction, bool backface)
{
	if (direction == 0) {
		//YZ plane
		return backface ? SIDE::LEFT : SIDE::RIGHT;
	}

	if (direction == 1) {
		//XZ plane
		return backface ? SIDE::BOTTOM : SIDE::TOP;
	}

	if (direction == 2) {
		//XY plane
		return backface ? SIDE::BACK : SIDE::FRONT;
	}

	//just make sure I return something if it goes wrong !
	return SIDE::FRONT;
}

CubeChunk* ChunkManager::getChunk(glm::vec3 pos)
{
	if (isContainsIndex(pos)) {
		return &map.at(FlattenIndex(pos));
	}
	return nullptr;
}

CubeChunk* ChunkManager::getChunk(glm::vec3 pos, int direction, bool backface)
{
	pos[direction] += backface ? ChunkDimensions[direction] * (-1) : ChunkDimensions[direction];
	return getChunk(pos);
}

ChunkManager::ChunkManager(glm::vec3 dimensions, glm::vec3 chunkDimensions)
{
	Dimensions = dimensions;
	ChunkDimensions = chunkDimensions;
	hasInitialized = false;
}

ChunkManager::ChunkManager()
{
	Dimensions = glm::vec3(1, 1, 1);
	ChunkDimensions = glm::vec3(1, 1, 1);
	hasInitialized = false;
}

ChunkManager::~ChunkManager()
{
}

void ChunkManager::Initialize()
{
	if (!hasInitialized) {
#ifdef DEBUG
		cout << "Chunk Manager [Dimensions]: " << Dimensions.x << " " << Dimensions.y << " " << Dimensions.z << endl;
		cout << "Chunk [Dimensions]: " << ChunkDimensions.x << " " << ChunkDimensions.y << " " << ChunkDimensions.z << endl;
		cout << "Loading Chunk ..." << endl;
#endif // DEBUG

		for (int x = 0; x < Dimensions.x * ChunkDimensions.x; x += ChunkDimensions.x) {
			for (int y = 0; y < Dimensions.y * ChunkDimensions.y; y += ChunkDimensions.y) {
				for (int z = 0; z < Dimensions.z * ChunkDimensions.z; z += ChunkDimensions.z) {
					//cout << "x: " << x << " |y: " << y << " |z: " << z << endl;
					CubeChunk chunk(glm::vec3(x,y,z), ChunkDimensions);
					map.insert(std::pair<int, CubeChunk>(FlattenIndex(glm::vec3(x,y,z)), chunk));
				}
			}
		}

#ifdef DEBUG
		cout << "Linking Chunk ..." << endl;
#endif // DEBUG

		int direction, workAxis1, workAxis2;
		bool backface;
		glm::vec3 startPos;

		for (int side = 0; side < NUM_OF_SIDES; ++side) {
			backface = side % 2 == 0 ? false : true;
			direction = side % 3;
			workAxis1 = (direction + 1) % 3;
			workAxis2 = (direction + 2) % 3;

			for (startPos[direction] = 0; startPos[direction] < Dimensions[direction] * ChunkDimensions[direction]; startPos[direction] += ChunkDimensions[direction]) {
				for (startPos[workAxis1] = 0; startPos[workAxis1] < Dimensions[workAxis1] * ChunkDimensions[workAxis1]; startPos[workAxis1] += ChunkDimensions[workAxis1]) {
					for (startPos[workAxis2] = 0; startPos[workAxis2] < Dimensions[workAxis2] * ChunkDimensions[workAxis2]; startPos[workAxis2] += ChunkDimensions[workAxis2]) {
						CubeChunk* chunk = getChunk(startPos);

						int actualSide = getActualSide(direction, backface);

						if (chunk->hasNeighbor(static_cast<SIDE>(actualSide))) continue;

						CubeChunk* chunkNeighbor = getChunk(startPos, direction, backface);

						if (chunkNeighbor == nullptr) continue;

						chunk->AddNeighbor(chunkNeighbor, static_cast<SIDE>(actualSide));
					}
				}
			}
		}

#ifdef DEBUG
		cout << "Generating Chunk ..." << endl;
#endif // DEBUG

		for (int x = 0; x < Dimensions.x * ChunkDimensions.x; x += ChunkDimensions.x) {
			for (int y = 0; y < Dimensions.y * ChunkDimensions.y; y += ChunkDimensions.y) {
				for (int z = 0; z < Dimensions.z * ChunkDimensions.z; z += ChunkDimensions.z) {
					CubeChunk* chunk = getChunk(glm::vec3(x, y, z));
					chunk->GenerateTerrain();
				}
			}
		}

#ifdef DEBUG
		cout << "Chunk count: " << map.size() << endl;
#endif // DEBUG

		hasInitialized = true;
	}
	else {
#ifdef DEBUG
		cout << "The chunk manager has initialized already !" << endl;
#endif // DEBUG
	}
}

void ChunkManager::Update()
{
	if (hasInitialized) {
		for (int x = 0; x < Dimensions.x * ChunkDimensions.x; x += ChunkDimensions.x) {
			for (int y = 0; y < Dimensions.y * ChunkDimensions.y; y += ChunkDimensions.y) {
				for (int z = 0; z < Dimensions.z * ChunkDimensions.z; z += ChunkDimensions.z) {
					CubeChunk* chunk = getChunk(glm::vec3(x, y, z));
					chunk->Update();
				}
			}
		}
	}
}
