#include "CubeChunk.h"

void CubeChunk::setDimensions(int x, int y, int z)
{
	if (x <= 0) x = VOXEL_UNIT;
	if (y <= 0) y = VOXEL_UNIT;
	if (z <= 0) z = VOXEL_UNIT;
	Dimensions = glm::vec3(x, y, z);
}

void CubeChunk::setDimensions(glm::vec3 dimensions)
{
	if (dimensions.x <= 0) dimensions.x = VOXEL_UNIT;
	if (dimensions.y <= 0) dimensions.y = VOXEL_UNIT;
	if (dimensions.z <= 0) dimensions.z = VOXEL_UNIT;
	Dimensions = dimensions;
}

int CubeChunk::FlattenIndex(glm::vec3 pos)
{
	//return (pos.z * Dimensions.z * Dimensions.z) + (pos.y * Dimensions.y) + pos.x;
	return pos.z + Dimensions.z * (pos.y + Dimensions.y * pos.x);
}

bool CubeChunk::isContainsPosition(glm::vec3 pos)
{
	return pos.x >= 0 && pos.x < Dimensions.x && pos.y >= 0 && pos.y < Dimensions.y && pos.z >= 0 && pos.z < Dimensions.z;
}

bool CubeChunk::isBlockFaceVisible(glm::vec3 pos, int direction, bool backface)
{
	//NOTE [WARNING A BUG]
	pos[direction] += backface ? -1 : 1;
	if (!isContainsPosition(pos)) {
		return !getVoxelNeighbor(pos, direction, backface).isSolid();
	}
	return !getVoxel(pos).isSolid();
}

bool CubeChunk::compareStep(glm::vec3 pos1, glm::vec3 pos2, int direction, bool backface)
{
	Voxel v1 = getVoxel(pos1);
	Voxel v2 = getVoxel(pos2);

	return v1.equals(v2) && v2.isSolid() && isBlockFaceVisible(pos2, direction, backface);
}

int CubeChunk::getActualFace(int direction, bool backface)
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

void CubeChunk::stupid()
{
	int direction, workAxis1, workAxis2, face;
	glm::vec3 startPos, quadSize, m, n, offsetPos;
	glm::vec4 p1, p2, p3, p4;
	bool backface;
	Voxel startVoxel;

	for (face = 0; face < NUM_OF_SIDES; face++) {
		backface = face % 2 == 0 ? false : true;
		direction = face % 3;
		workAxis1 = (direction + 1) % 3;
		workAxis2 = (direction + 2) % 3;

		startPos = glm::vec3();

		for (startPos[direction] = 0; startPos[direction] < Dimensions[direction]; ++startPos[direction]) {
			for (startPos[workAxis1] = 0; startPos[workAxis1] < Dimensions[workAxis1]; ++startPos[workAxis1]) {
				for (startPos[workAxis2] = 0; startPos[workAxis2] < Dimensions[workAxis2]; ++startPos[workAxis2]) {
					startVoxel = getVoxel(startPos);

					if (!startVoxel.isSolid()) continue;

					quadSize = glm::vec3();

					//width
					quadSize[workAxis2] = VOXEL_UNIT;

					//height
					quadSize[workAxis1] = VOXEL_UNIT;

					m = glm::vec3();
					n = glm::vec3();

					m[workAxis1] = quadSize[workAxis1];
					n[workAxis2] = quadSize[workAxis2];

					offsetPos = startPos;

					if (VOXEL_UNIT < 1.0f) {
						offsetPos.x += offsetPos.x >= 1 ? -VOXEL_UNIT : 0;
						offsetPos.y += offsetPos.y >= 1 ? -VOXEL_UNIT : 0;
						offsetPos.z += offsetPos.z >= 1 ? -VOXEL_UNIT : 0;
					}

					offsetPos[direction] += backface ? 0 : VOXEL_UNIT;

					p1 = model * glm::vec4(offsetPos, 1.0f);
					p2 = model * glm::vec4(offsetPos + m, 1.0f);
					p3 = model * glm::vec4(offsetPos + m + n, 1.0f);
					p4 = model * glm::vec4(offsetPos + n, 1.0f);

					int actualFace = getActualFace(direction, backface);

					Quad quad(
						glm::vec3(p1.x, p1.y, p1.z),
						glm::vec3(p2.x, p2.y, p2.z),
						glm::vec3(p3.x, p3.y, p3.z),
						glm::vec3(p4.x, p4.y, p4.z),
						startVoxel.type,
						actualFace,
						startVoxel.transparent
					);	

					if (direction == 2) {
						quad.RotateQuadOrder90Counter();
						meshBuider.AddQuad(quad, quadSize[workAxis1], quadSize[workAxis2], backface);
					}
					else {
						meshBuider.AddQuad(quad, quadSize[workAxis2], quadSize[workAxis1], backface);
					}
				}
			}
		}
	}

	meshBuider.GenerateVBO();
}

void CubeChunk::culling()
{
	int direction, workAxis1, workAxis2, face;
	glm::vec3 startPos, quadSize, m, n, offsetPos;
	glm::vec4 p1, p2, p3, p4;
	bool backface;
	Voxel startVoxel;

	for (int face = 0; face < NUM_OF_SIDES; face++) {
		backface = face % 2 == 0 ? false : true;

		direction = face % 3;
		workAxis1 = (direction + 1) % 3;
		workAxis2 = (direction + 2) % 3;

		startPos = glm::vec3();

		for (startPos[direction] = 0; startPos[direction] < Dimensions.x; startPos[direction]++) {
			for (startPos[workAxis1] = 0; startPos[workAxis1] < Dimensions.y; startPos[workAxis1]++) {
				for (startPos[workAxis2] = 0; startPos[workAxis2] < Dimensions.z; startPos[workAxis2]++) {
					Voxel startVoxel = this->getVoxel(startPos);

					if (!startVoxel.isSolid() || !isBlockFaceVisible(startPos, direction, backface)) {
						continue;
					}

					quadSize = glm::vec3();

					//width
					quadSize[workAxis2] = VOXEL_UNIT;

					//height
					quadSize[workAxis1] = VOXEL_UNIT;

					m = glm::vec3();
					n = glm::vec3();
					m[workAxis1] = quadSize[workAxis1];
					n[workAxis2] = quadSize[workAxis2];

					offsetPos = startPos;

					if (VOXEL_UNIT < 1.0f) {
						offsetPos.x += offsetPos.x >= 1 ? -VOXEL_UNIT : 0;
						offsetPos.y += offsetPos.y >= 1 ? -VOXEL_UNIT : 0;
						offsetPos.z += offsetPos.z >= 1 ? -VOXEL_UNIT : 0;
					}

					offsetPos[direction] += backface ? 0 : VOXEL_UNIT;

					p1 = model * glm::vec4(offsetPos, 1.0f);
					p2 = model * glm::vec4(offsetPos + m, 1.0f);
					p3 = model * glm::vec4(offsetPos + m + n, 1.0f);
					p4 = model * glm::vec4(offsetPos + n, 1.0f);

					int actualFace = getActualFace(direction, backface);

					Quad quad(
						glm::vec3(p1.x, p1.y, p1.z),
						glm::vec3(p2.x, p2.y, p2.z),
						glm::vec3(p3.x, p3.y, p3.z),
						glm::vec3(p4.x, p4.y, p4.z),
						startVoxel.type,
						actualFace,
						startVoxel.transparent
					);

					if (direction == 2) {
						quad.RotateQuadOrder90Counter();
						meshBuider.AddQuad(quad, quadSize[workAxis1], quadSize[workAxis2], backface);
					}
					else {
						meshBuider.AddQuad(quad, quadSize[workAxis2], quadSize[workAxis1], backface);
					}
				}
			}
		}
	}

	meshBuider.GenerateVBO();
}

void CubeChunk::greedy()
{
	int direction, workAxis1, workAxis2, face;
	glm::vec3 startPos, currPos, quadSize, m, n, offsetPos;
	glm::vec4 p1, p2, p3, p4;
	bool backface;
	Voxel startVoxel;

	for (int face = 0; face < NUM_OF_SIDES; face++) {
		backface = face % 2 == 0 ? false : true;

		direction = face % 3;
		workAxis1 = (direction + 1) % 3;
		workAxis2 = (direction + 2) % 3;

		startPos = glm::vec3();
		currPos = glm::vec3();

		for (startPos[direction] = 0; startPos[direction] < Dimensions[direction]; startPos[direction]++) {
			
			bool** merged = new bool* [Dimensions[workAxis1]];
			for (int i = 0; i < Dimensions[workAxis1]; ++i) {
				merged[i] = new bool[Dimensions[workAxis2]];
				memset(merged[i], false, Dimensions[workAxis2] * sizeof(bool));
			}

			for (startPos[workAxis1] = 0; startPos[workAxis1] < Dimensions[workAxis1]; startPos[workAxis1]++) {
				for (startPos[workAxis2] = 0; startPos[workAxis2] < Dimensions[workAxis2]; startPos[workAxis2]++) {
					Voxel startVoxel = this->getVoxel(startPos);

					if (merged[(int)startPos[workAxis1]][(int)startPos[workAxis2]] == true || !startVoxel.isSolid() || !isBlockFaceVisible(startPos, direction, backface)) {
						continue;
					}

					quadSize = glm::vec3();

					//width
					for (currPos = startPos, currPos[workAxis2]++; currPos[workAxis2] < Dimensions[workAxis2] && compareStep(startPos, currPos, direction, backface) && !merged[(int)currPos[workAxis1]][(int)currPos[workAxis2]]; currPos[workAxis2]++) {}
					quadSize[workAxis2] = currPos[workAxis2] - startPos[workAxis2];

					//height
					for (currPos = startPos, currPos[workAxis1]++; currPos[workAxis1] < Dimensions[workAxis1] && compareStep(startPos, currPos, direction, backface) && !merged[(int)currPos[workAxis1]][(int)currPos[workAxis2]]; currPos[workAxis1]++) {
						for (currPos[workAxis2] = startPos[workAxis2]; currPos[workAxis2] < Dimensions[workAxis2] && compareStep(startPos, currPos, direction, backface) && !merged[(int)currPos[workAxis1]][(int)currPos[workAxis2]]; currPos[workAxis2]++) {}

						if (currPos[workAxis2] - startPos[workAxis2] < quadSize[workAxis2]) {
							break;
						}
						else {
							currPos[workAxis2] = startPos[workAxis2];
						}
					}
					quadSize[workAxis1] = currPos[workAxis1] - startPos[workAxis1];


					m = glm::vec3();
					n = glm::vec3();
					m[workAxis1] = quadSize[workAxis1];
					n[workAxis2] = quadSize[workAxis2];

					offsetPos = startPos;

					if (VOXEL_UNIT < 1.0f) {
						offsetPos.x += offsetPos.x >= 1 ? -VOXEL_UNIT : 0;
						offsetPos.y += offsetPos.y >= 1 ? -VOXEL_UNIT : 0;
						offsetPos.z += offsetPos.z >= 1 ? -VOXEL_UNIT : 0;
					}

					offsetPos[direction] += backface ? 0 : VOXEL_UNIT;

					p1 = model * glm::vec4(offsetPos, 1.0f);
					p2 = model * glm::vec4(offsetPos + m, 1.0f);
					p3 = model * glm::vec4(offsetPos + m + n, 1.0f);
					p4 = model * glm::vec4(offsetPos + n, 1.0f);

					int actualFace = getActualFace(direction, backface);

					Quad quad(
						glm::vec3(p1.x, p1.y, p1.z),
						glm::vec3(p2.x, p2.y, p2.z),
						glm::vec3(p3.x, p3.y, p3.z),
						glm::vec3(p4.x, p4.y, p4.z),
						startVoxel.type,
						actualFace,
						startVoxel.transparent
					);

					if (direction == 2) {
						quad.RotateQuadOrder90Counter();
						meshBuider.AddQuad(quad, quadSize[workAxis1], quadSize[workAxis2], backface);
					}
					else {
						meshBuider.AddQuad(quad, quadSize[workAxis2], quadSize[workAxis1], backface);
					}

					for (int f = 0; f < quadSize[workAxis1]; ++f) {
						for (int g = 0; g < quadSize[workAxis2]; ++g) {
							merged[(int)startPos[workAxis1] + f][(int)startPos[workAxis2] + g] = true;
						}
					}
				}
			}
			delete[] merged;
		}
	}

	meshBuider.GenerateVBO();
}

Voxel CubeChunk::getVoxelNeighbor(glm::vec3 pos, int direction, bool backface)
{
	if (pos[direction] < 0) {
		pos[direction] = Dimensions[direction] + pos[direction];
	}

	if (pos[direction] >= Dimensions[direction]) {
		pos[direction] = Dimensions[direction] - pos[direction];
	}

	int side = getActualFace(direction, backface);

	CubeChunk* neighbor = getNeighbor(static_cast<SIDE>(side));

	if (neighbor != nullptr) {
		return neighbor->getVoxel(pos);
	}

	Voxel v(VOXEL_TRANSPARENT::TRUE, VOXEL_TYPE::AIR);
	return v;
}

CubeChunk::CubeChunk(glm::vec3 pos, glm::vec3 dimensions) : VOXEL_UNIT(1.0f)
{
	Dimensions = dimensions;
	hasChanged = true;
	hasGeneratedTerrain = false;
	firstMeshing = false;
	for (int i = 0; i < 6; i++) neighbors[i] = nullptr;
	model = glm::mat4(1.0f);
	ChunkPosition = pos;
	model = glm::translate(model, ChunkPosition);
}

CubeChunk::CubeChunk() : VOXEL_UNIT(1.0f) {
	Dimensions = glm::vec3(VOXEL_UNIT, VOXEL_UNIT, VOXEL_UNIT); // one cube only
	hasChanged = true;
	hasGeneratedTerrain = false;
	firstMeshing = false;
	for (int i = 0; i < 6; i++) neighbors[i] = nullptr;
	model = glm::mat4(1.0f);
	ChunkPosition = glm::vec3(0, 0, 0);
	model = glm::translate(model, ChunkPosition);
}

CubeChunk::~CubeChunk()
{

}

Voxel CubeChunk::getVoxel(int x, int y, int z)
{
	if (hasGeneratedTerrain) {
		if (!isContainsPosition(glm::vec3(x, y, z))) {
			Voxel v(VOXEL_TRANSPARENT::TRUE, VOXEL_TYPE::AIR);
			return v;
		}

		return voxels.at(FlattenIndex(glm::vec3(x,y,z)));
	}
	
#ifdef DEBUG
	cout << "The chunk has not generate terrain yet !" << endl;
#endif // DEBUG

	Voxel v(VOXEL_TRANSPARENT::TRUE, VOXEL_TYPE::AIR);
	return v;
}

Voxel CubeChunk::getVoxel(glm::vec3 pos)
{
	if (hasGeneratedTerrain) {
		if (!isContainsPosition(pos)) {
			Voxel v(VOXEL_TRANSPARENT::TRUE, VOXEL_TYPE::AIR);
			return v;
		}

		return voxels.at(FlattenIndex(pos));
	}

#ifdef DEBUG
	cout << "The chunk has not generate terrain yet !" << endl;
#endif // DEBUG

	Voxel v(VOXEL_TRANSPARENT::TRUE, VOXEL_TYPE::AIR);
	return v;
}

void CubeChunk::AddNeighbor(CubeChunk* chunk, SIDE side)
{
	neighbors[side] = chunk;
}

bool CubeChunk::hasNeighbor(SIDE side)
{
	return neighbors[side] != nullptr;
}

CubeChunk* CubeChunk::getNeighbor(SIDE side)
{
	return neighbors[side];
}

void CubeChunk::DoMeshing(MESHING_METHOD meshing_method)
{
	if (hasGeneratedTerrain) {
		if (meshing_method == MESHING_METHOD::STUPID) {
			stupid();
		}

		if (meshing_method == MESHING_METHOD::CULLING) {
			culling();
		}

		if (meshing_method == MESHING_METHOD::GREEDY) {
			greedy();
		}
	}
	else {
#ifdef DEBUG
		cout << "The chunk has not generated terrain yet !" << endl;
#endif // DEBUG
	}
}

void CubeChunk::GenerateTerrain()
{
	if (hasGeneratedTerrain == false) {
		//MeshGenerator::GenerateShape(Dimensions, voxels, MESH_SHAPE::CUBE);
		MeshGenerator::GenerateTerrain(Dimensions, voxels, TERRAIN_GENERATION_METHOD::PERLIN);
		hasGeneratedTerrain = true;
	}
	else {
#ifdef DEBUG
		cout << "The chunk has generated terrain already !" << endl;
#endif // DEBUG

	}
}

void CubeChunk::Update()
{
	if (hasChanged) {
		DoMeshing(MESHING_METHOD::GREEDY);
		hasChanged = false;
	}

	meshBuider.Render();
}


