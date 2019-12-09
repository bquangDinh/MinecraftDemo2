#include "CubeChunk.h"

Voxel CubeChunk::getVoxel(int x, int y, int z)
{
	glm::vec3 position = glm::vec3(x, y, z);
	return getVoxel(position);
}

Voxel CubeChunk::getVoxel(glm::vec3 position)
{
	if (!ContainsIndex(position)) {
		Voxel v(false, AIR_BLOCK);
		return v;
	}

	return this->Cubes[FlattenIndex(position)];
}

void CubeChunk::setVoxel(int x, int y, int z, int type, bool transparent)
{
	Voxel voxel(transparent, type);
	this->Cubes[z + CHUNK_SIZE * (y + CHUNK_SIZE * x)] = voxel;
}

void CubeChunk::stupid()
{
	//this function follow the instruction https://eddieabbondanz.io/post/voxel/greedy-mesh/
	int direction, workAxis1, workAxis2;
	bool merged[CHUNK_SIZE][CHUNK_SIZE] = { false };
	glm::vec3 startPos, currPos, quadSize, m, n, offsetPos;

	Point q_p1, q_p2, q_p3, q_p4;
	glm::vec4 p1 = glm::vec4();
	glm::vec4 p2 = glm::vec4();
	glm::vec4 p3 = glm::vec4();
	glm::vec4 p4 = glm::vec4();

	for (int face = 0; face < NUM_OF_SIDES; face++) {
		bool isBackFace = face % 2 == 0 ? false : true;

		direction = face % 3;
		workAxis1 = (direction + 1) % 3;
		workAxis2 = (direction + 2) % 3;

		startPos = glm::vec3();
		currPos = glm::vec3();

		for (startPos[direction] = 0; startPos[direction] < CHUNK_SIZE; startPos[direction]++) {
			//reset merged array if we've done before
			memset(merged, false, sizeof(merged));

			for (startPos[workAxis1] = 0; startPos[workAxis1] < CHUNK_SIZE; startPos[workAxis1]++) {
				for (startPos[workAxis2] = 0; startPos[workAxis2] < CHUNK_SIZE; startPos[workAxis2]++) {
					Voxel startVoxel = this->getVoxel(startPos);

					quadSize = glm::vec3();

					//width
					quadSize[workAxis2] = this->VOXEL_UNIT;

					//height
					quadSize[workAxis1] = this->VOXEL_UNIT;

					m = glm::vec3();
					n = glm::vec3();
					m[workAxis1] = quadSize[workAxis1];
					n[workAxis2] = quadSize[workAxis2];

					offsetPos = startPos;
					offsetPos[direction] += isBackFace ? 0 : 1;

					p1 = model * glm::vec4(offsetPos, 1.0f);
					p2 = model * glm::vec4(offsetPos + m, 1.0f);
					p3 = model * glm::vec4(offsetPos + m + n, 1.0f);
					p4 = model * glm::vec4(offsetPos + n, 1.0f);

					q_p1 = { p1.x, p1.y, p1.z };
					q_p2 = { p2.x, p2.y, p2.z };
					q_p3 = { p3.x, p3.y, p3.z };
					q_p4 = { p4.x, p4.y, p4.z };

					Voxel voxel = getVoxel(startPos);
					Quad quad(q_p1, q_p2, q_p3, q_p4, voxel.type, face, voxel.transparent);
					this->cubeRenderer.AddQuadToVBO(quad, isBackFace);

					for (int f = 0; f < quadSize[workAxis1]; f++) {
						for (int g = 0; g < quadSize[workAxis2]; g++) {
							merged[(int)startPos[workAxis1] + f][(int)startPos[workAxis2] + g] = true;
						}
					}
				}
			}
		}
	}
}

void CubeChunk::culling()
{
	//this function follow the instruction https://eddieabbondanz.io/post/voxel/greedy-mesh/
	int direction, workAxis1, workAxis2;
	bool merged[CHUNK_SIZE][CHUNK_SIZE] = { false };
	glm::vec3 startPos, currPos, quadSize, m, n, offsetPos;

	Point q_p1, q_p2, q_p3, q_p4;
	glm::vec4 p1 = glm::vec4();
	glm::vec4 p2 = glm::vec4();
	glm::vec4 p3 = glm::vec4();
	glm::vec4 p4 = glm::vec4();

	for (int face = 0; face < NUM_OF_SIDES; face++) {
		bool isBackFace = face % 2 == 0 ? false : true;

		direction = face % 3;
		workAxis1 = (direction + 1) % 3;
		workAxis2 = (direction + 2) % 3;

		startPos = glm::vec3();
		currPos = glm::vec3();

		for (startPos[direction] = 0; startPos[direction] < CHUNK_SIZE; startPos[direction]++) {
			//reset merged array if we've done before
			memset(merged, false, sizeof(merged));

			for (startPos[workAxis1] = 0; startPos[workAxis1] < CHUNK_SIZE; startPos[workAxis1]++) {
				for (startPos[workAxis2] = 0; startPos[workAxis2] < CHUNK_SIZE; startPos[workAxis2]++) {
					Voxel startVoxel = this->getVoxel(startPos);

					if (merged[(int)startPos[workAxis1]][(int)startPos[workAxis2]] == true || !startVoxel.isSolid() || !IsBlockFaceVisible(startPos, direction, isBackFace)) {
						continue;
					}

					quadSize = glm::vec3();

					//width
					quadSize[workAxis2] = this->VOXEL_UNIT;

					//height
					quadSize[workAxis1] = this->VOXEL_UNIT;

					m = glm::vec3();
					n = glm::vec3();
					m[workAxis1] = quadSize[workAxis1];
					n[workAxis2] = quadSize[workAxis2];

					offsetPos = startPos;
					offsetPos[direction] += isBackFace ? 0 : 1;

					p1 = model * glm::vec4(offsetPos, 1.0f);
					p2 = model * glm::vec4(offsetPos + m, 1.0f);
					p3 = model * glm::vec4(offsetPos + m + n, 1.0f);
					p4 = model * glm::vec4(offsetPos + n, 1.0f);

					q_p1 = { p1.x, p1.y, p1.z };
					q_p2 = { p2.x, p2.y, p2.z };
					q_p3 = { p3.x, p3.y, p3.z };
					q_p4 = { p4.x, p4.y, p4.z };

					Voxel voxel = getVoxel(startPos);
					Quad quad(q_p1, q_p2, q_p3, q_p4, voxel.type, face, voxel.transparent);
					this->cubeRenderer.AddQuadToVBO(quad, isBackFace);

					for (int f = 0; f < quadSize[workAxis1]; f++) {
						for (int g = 0; g < quadSize[workAxis2]; g++) {
							merged[(int)startPos[workAxis1] + f][(int)startPos[workAxis2] + g] = true;
						}
					}
				}
			}
		}
	}
}

bool CubeChunk::compareStep(glm::vec3 a, glm::vec3 b, int direction, bool backFace)
{
	Voxel A = getVoxel(a);
	Voxel B = getVoxel(b);

	return A.equals(B) && B.isSolid() && IsBlockFaceVisible(b, direction, backFace);
}

bool CubeChunk::IsBlockFaceVisible(glm::vec3 position, int axis, bool backFace)
{
	position[axis] += backFace ? -1 : 1;
	return !getVoxel(position).isSolid();
}

Voxel CubeChunk::setBlock(glm::vec3 index, int type, bool transparent)
{
	if (!ContainsIndex(index)) {
		cout << "Chunk is not contain this index: " << index.x << " " << index.y << " " << index.z << endl;
		throw std::invalid_argument("Invalid index");
	}
	Voxel v(transparent, type);
	this->Cubes[FlattenIndex(index)] = v;
}

bool CubeChunk::ContainsIndex(glm::vec3 index)
{
	return index.x >= 0 && index.x < CHUNK_SIZE && index.y >= 0 && index.y < CHUNK_SIZE && index.z >= 0 && index.z < CHUNK_SIZE;
}

int CubeChunk::FlattenIndex(glm::vec3 index)
{
	return (index.z * CHUNK_SIZE * CHUNK_SIZE) + (index.y * CHUNK_SIZE) + index.x;
}

void CubeChunk::greedy()
{
	//this function follow the instruction https://eddieabbondanz.io/post/voxel/greedy-mesh/
	int direction, workAxis1, workAxis2;
	bool merged[CHUNK_SIZE][CHUNK_SIZE] = { false };
	glm::vec3 startPos, currPos, quadSize, m, n, offsetPos;

	Point q_p1, q_p2, q_p3, q_p4;
	glm::vec4 p1 = glm::vec4();
	glm::vec4 p2 = glm::vec4();
	glm::vec4 p3 = glm::vec4();
	glm::vec4 p4 = glm::vec4();

    for (int face = 0; face < NUM_OF_SIDES; face++) {
		bool isBackFace = face % 2 == 0 ? false : true;

		direction = face % 3;
		workAxis1 = (direction + 1) % 3;
		workAxis2 = (direction + 2) % 3;

		startPos = glm::vec3();
		currPos = glm::vec3();

		for (startPos[direction] = 0; startPos[direction] < CHUNK_SIZE; startPos[direction]++) {
			//reset merged array if we've done before
			memset(merged, false, sizeof(merged));

			for (startPos[workAxis1] = 0; startPos[workAxis1] < CHUNK_SIZE; startPos[workAxis1]++) {
 				for (startPos[workAxis2] = 0; startPos[workAxis2] < CHUNK_SIZE; startPos[workAxis2]++) {
					Voxel startVoxel = this->getVoxel(startPos);

					if (merged[(int)startPos[workAxis1]][(int)startPos[workAxis2]] == true || !startVoxel.isSolid() || !IsBlockFaceVisible(startPos,direction,isBackFace)) {
						continue;
					}

					quadSize = glm::vec3();

					//width
					for(currPos = startPos,currPos[workAxis2]++;currPos[workAxis2] < CHUNK_SIZE && compareStep(startPos,currPos,direction,isBackFace) && !merged[(int)currPos[workAxis1]][(int)currPos[workAxis2]];currPos[workAxis2]++){}
					quadSize[workAxis2] = currPos[workAxis2] - startPos[workAxis2];

					//height
					for (currPos = startPos, currPos[workAxis1]++; currPos[workAxis1] < CHUNK_SIZE && compareStep(startPos, currPos, direction, isBackFace) && !merged[(int)currPos[workAxis1]][(int)currPos[workAxis2]]; currPos[workAxis1]++) {
						for(currPos[workAxis2] = startPos[workAxis2];currPos[workAxis2] < CHUNK_SIZE && compareStep(startPos, currPos, direction, isBackFace) && !merged[(int)currPos[workAxis1]][(int)currPos[workAxis2]];currPos[workAxis2]++){}

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
					//cout << "w: " << quadSize[workAxis2] << " |h: " << quadSize[workAxis1] << endl;

					offsetPos = startPos;
					offsetPos[direction] += isBackFace ? 0 : 1;

					p1 = model * glm::vec4(offsetPos, 1.0f);
					p2 = model * glm::vec4(offsetPos + m, 1.0f);
					p3 = model * glm::vec4(offsetPos + m + n, 1.0f);
					p4 = model * glm::vec4(offsetPos + n, 1.0f);

					q_p1 = { p1.x, p1.y, p1.z };
					q_p2 = { p2.x, p2.y, p2.z };
					q_p3 = { p3.x, p3.y, p3.z };
					q_p4 = { p4.x, p4.y, p4.z };

					Voxel voxel = getVoxel(startPos);
					Quad quad(q_p1, q_p2, q_p3, q_p4, voxel.type, face, voxel.transparent);
					this->cubeRenderer.AddQuadToVBO(quad,isBackFace);

					for (int f = 0; f < quadSize[workAxis1]; f++) {
						for (int g = 0; g < quadSize[workAxis2]; g++) {
							merged[(int)startPos[workAxis1] + f][(int)startPos[workAxis2] + g] = true;
						}
					}
				}
			}
		}
	}
}

bool CubeChunk::isVisibleQuad(int x, int y, int z,int side)
{
	if (!this->getVoxel(x, y, z).isSolid()) return false;

	if (side == FRONTSIDE) {
		if (getVoxel(x, y, z - 1).type == AIR_BLOCK) {
			return true;
		}
		else return false;
	}
	else if (side == BACKSIDE) {
		if (getVoxel(x, y, z + 1).type == AIR_BLOCK) {
			return true;
		}
		else return false;
	}
	else if (side == LEFTSIDE) {
		if (getVoxel(x - 1, y, z).type == AIR_BLOCK) {
			return true;
		}
		else return false;
	}
	else if (side == RIGHTSIDE) {
		if (getVoxel(x + 1, y, z).type == AIR_BLOCK) {
			return true;
		}
		else return false;
	}
	else if (side == TOPSIDE) {
		if (getVoxel(x, y + 1, z).type == AIR_BLOCK) {
			return true;
		}
		else return false;
	}
	else if (side == BOTTOMSIDE) {
		if (getVoxel(x, y - 1, z).type == AIR_BLOCK) {
			return true;
		}
		else return false;
	}

	return false;
}

void CubeChunk::getQuad(int x, int  y, int z, int side,Quad& quad)
{
	Voxel voxel = this->getVoxel(x, y, z);
	quad.direction = side;
	quad.type = voxel.type;
	quad.transparent = voxel.transparent;
}

CubeChunk::CubeChunk()
{
	this->hasCreated = false;
}

CubeChunk::~CubeChunk()
{
}

CubeChunk CubeChunk::operator=(CubeChunk& another)
{
	CubeChunk c;
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				Voxel v = another.getVoxel(x, y, z);
				c.setVoxel(x, y, z, v.type, v.transparent);
			}
		}
	}

	c.hasChanged = another.hasChanged;
	c.hasCreated = another.hasCreated;

	for (int side = 0; side < NUM_OF_SIDES; side++) {
		c.AddNeighBor(another.getNeighBor(side), side);
	}

	return c;
}

void CubeChunk::Init(glm::vec3 position, int* heightmap, int c_x, int c_z)
{
	this->chunkPos = position;
	this->model = glm::mat4(1.0f);
	this->model = glm::translate(model, this->chunkPos);
	this->CreateMesh(heightmap, c_x, c_z);
	this->hasCreated = true;
}

void CubeChunk::Init(glm::vec3 position)
{
	this->chunkPos = position;
	this->model = glm::mat4(1.0f);
	this->model = glm::translate(model, this->chunkPos);
	this->CreateMesh();
	this->hasCreated = true;
}

void CubeChunk::CreateMesh(int* heightmap, int c_x, int c_z)
{	
	bitmap_image image("C:\\Users\\buiqu\\Downloads\\rsz_heightmap_2.bmp");

	if (!image) {
		cout << "Invalid height map";
		return;
	}

	const unsigned int width = image.width();
	const unsigned int height = image.height();

	cout << "Height map: w: " << width << " |h: " << height << endl;

	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			rgb_t colour;
			image.get_pixel(x, y, colour);
			int height = (colour.red / 255.0f) * 15;
			if (height == 0) height = 1;

			for (int z = 0; z < CHUNK_SIZE; z++) {
				if (height > z) {
					setBlock(glm::vec3(x, z, y), AIR_BLOCK, false);
				}
				else {
					setBlock(glm::vec3(x, z, y), GRASS_BLOCK, true);
				}
			}
		}
	}
}

void CubeChunk::CreateMesh()
{
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				setBlock(glm::vec3(x, z, y), GRASS_BLOCK, true);
			}
		}
	}
}

void CubeChunk::Generate()
{
	this->cubeRenderer.GenerateVBO();
	this->hasGenerated = true;	
}

void CubeChunk::DoMeshing()
{
	this->greedy();
	this->cubeRenderer.isReadyToUse = true;
	this->isReady = true;
}

void CubeChunk::AddNeighBor(CubeChunk* another, int side)
{
	this->neighbors[side] = another;
}

CubeChunk* CubeChunk::getNeighBor(int side)
{
	return this->neighbors[side];
}

void CubeChunk::Update()
{
	cubeRenderer.Render();
}
