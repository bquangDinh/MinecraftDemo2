#include "CubeChunk.h"

Voxel CubeChunk::getVoxel(int x, int y, int z)
{
	return this->Cubes[z + CHUNK_SIZE * (y + CHUNK_SIZE * x)];
}

void CubeChunk::setVoxel(int x, int y, int z, int type, bool transparent)
{
	Voxel voxel(transparent, type);
	this->Cubes[z + CHUNK_SIZE * (y + CHUNK_SIZE * x)] = voxel;
}

void CubeChunk::stupid()
{
	cout << "Stupid meshing in process..." << endl;

	for (int side = 0; side < NUM_OF_SIDES; side++) {
		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int y = 0; y < CHUNK_SIZE; y++) {
				for (int z = 0; z < CHUNK_SIZE; z++) {
					Point q_p1, q_p2, q_p3, q_p4;
					glm::vec4 p1, p2, p3, p4;

					if (side == FRONTSIDE) {
						p1 = model * glm::vec4(x - this->VOXEL_UNIT, y + this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
						p2 = model * glm::vec4(x + this->VOXEL_UNIT, y + this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
						p3 = model * glm::vec4(x + this->VOXEL_UNIT, y - this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
						p4 = model * glm::vec4(x - this->VOXEL_UNIT, y - this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
					}
					else if (side == BACKSIDE){
						p1 = model * glm::vec4(x - this->VOXEL_UNIT, y + this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
						p2 = model * glm::vec4(x + this->VOXEL_UNIT, y + this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
						p3 = model * glm::vec4(x + this->VOXEL_UNIT, y - this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
						p4 = model * glm::vec4(x - this->VOXEL_UNIT, y - this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
					}
					else if (side == LEFTSIDE) {
						p1 = model * glm::vec4(x - this->VOXEL_UNIT, y + this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
						p2 = model * glm::vec4(x - this->VOXEL_UNIT, y + this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
						p3 = model * glm::vec4(x - this->VOXEL_UNIT, y - this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
						p4 = model * glm::vec4(x - this->VOXEL_UNIT, y - this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
					}
					else if (side == RIGHTSIDE) {
						p1 = model * glm::vec4(x + this->VOXEL_UNIT, y + this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
						p2 = model * glm::vec4(x + this->VOXEL_UNIT, y + this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
						p3 = model * glm::vec4(x + this->VOXEL_UNIT, y - this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
						p4 = model * glm::vec4(x + this->VOXEL_UNIT, y - this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
					}
					else if (side == TOPSIDE) {
						p1 = model * glm::vec4(x + this->VOXEL_UNIT, y + this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
						p2 = model * glm::vec4(x + this->VOXEL_UNIT, y + this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
						p3 = model * glm::vec4(x - this->VOXEL_UNIT, y + this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
						p4 = model * glm::vec4(x - this->VOXEL_UNIT, y + this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
					}
					else if (side == BOTTOMSIDE) {
						p1 = model * glm::vec4(x + this->VOXEL_UNIT, y - this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
						p2 = model * glm::vec4(x + this->VOXEL_UNIT, y - this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
						p3 = model * glm::vec4(x - this->VOXEL_UNIT, y - this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
						p4 = model * glm::vec4(x - this->VOXEL_UNIT, y - this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
					}

					q_p1 = { p1.x, p1.y, p1.z };
					q_p2 = { p2.x, p2.y, p2.z };
					q_p3 = { p3.x, p3.y, p3.z };
					q_p4 = { p4.x, p4.y, p4.z };

					Voxel voxel = this->getVoxel(x, y, z);
					Quad quad(q_p1, q_p2, q_p3, q_p4, voxel.type, side, voxel.transparent);
					this->cubeRenderer.AddQuadToVBO(quad);
				}
			}
		}
	}

	this->cubeRenderer.GenerateVBO();
	cout << "Stupid meshing: Done !" << endl;
}

void CubeChunk::culling()
{
	//cout << "Culling meshing in process..." << endl;
	for (int side = 0; side < NUM_OF_SIDES; side++) {
		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int y = 0; y < CHUNK_SIZE; y++) {
				for (int z = 0; z < CHUNK_SIZE; z++) {
					if (this->isVisibleQuad(x, y, z, side) == true) {
						Point q_p1, q_p2, q_p3, q_p4;
						glm::vec4 p1, p2, p3, p4;

						if (side == FRONTSIDE) {
							p1 = model * glm::vec4(x - this->VOXEL_UNIT, y + this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
							p2 = model * glm::vec4(x + this->VOXEL_UNIT, y + this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
							p3 = model * glm::vec4(x + this->VOXEL_UNIT, y - this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
							p4 = model * glm::vec4(x - this->VOXEL_UNIT, y - this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
						}
						else if (side == BACKSIDE) {
							p1 = model * glm::vec4(x - this->VOXEL_UNIT, y + this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
							p2 = model * glm::vec4(x + this->VOXEL_UNIT, y + this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
							p3 = model * glm::vec4(x + this->VOXEL_UNIT, y - this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
							p4 = model * glm::vec4(x - this->VOXEL_UNIT, y - this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
						}
						else if (side == LEFTSIDE) {
							p1 = model * glm::vec4(x - this->VOXEL_UNIT, y + this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
							p2 = model * glm::vec4(x - this->VOXEL_UNIT, y + this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
							p3 = model * glm::vec4(x - this->VOXEL_UNIT, y - this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
							p4 = model * glm::vec4(x - this->VOXEL_UNIT, y - this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
						}
						else if (side == RIGHTSIDE) {
							p1 = model * glm::vec4(x + this->VOXEL_UNIT, y + this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
							p2 = model * glm::vec4(x + this->VOXEL_UNIT, y + this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
							p3 = model * glm::vec4(x + this->VOXEL_UNIT, y - this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
							p4 = model * glm::vec4(x + this->VOXEL_UNIT, y - this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
						}
						else if (side == TOPSIDE) {
							p1 = model * glm::vec4(x + this->VOXEL_UNIT, y + this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
							p2 = model * glm::vec4(x + this->VOXEL_UNIT, y + this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
							p3 = model * glm::vec4(x - this->VOXEL_UNIT, y + this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
							p4 = model * glm::vec4(x - this->VOXEL_UNIT, y + this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
						}
						else if (side == BOTTOMSIDE) {
							p1 = model * glm::vec4(x + this->VOXEL_UNIT, y - this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
							p2 = model * glm::vec4(x + this->VOXEL_UNIT, y - this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
							p3 = model * glm::vec4(x - this->VOXEL_UNIT, y - this->VOXEL_UNIT, z + VOXEL_UNIT, 1.0f);
							p4 = model * glm::vec4(x - this->VOXEL_UNIT, y - this->VOXEL_UNIT, z - VOXEL_UNIT, 1.0f);
						}

						q_p1 = { p1.x, p1.y, p1.z };
						q_p2 = { p2.x, p2.y, p2.z };
						q_p3 = { p3.x, p3.y, p3.z };
						q_p4 = { p4.x, p4.y, p4.z };

						Voxel voxel = this->getVoxel(x, y, z);
						Quad quad(q_p1, q_p2, q_p3, q_p4, voxel.type, side, voxel.transparent);
						this->cubeRenderer.AddQuadToVBO(quad);
					}
				}
			}
		}
	}

	this->cubeRenderer.GenerateVBO();

	//cout << "Culling meshing: Done !" << endl;
}

bool CubeChunk::isVisibleQuad(int x, int y, int z,int side)
{
	if (this->getVoxel(x, y, z).type == AIR_BLOCK) return false;

	if (side == FRONTSIDE) {
		if (z == CHUNK_SIZE - 1) {
			if (this->getNeighBor(side) != NULL) {
				if (this->getNeighBor(side)->getVoxel(x, y, 0).type == AIR_BLOCK) return true;
				else return false;
			}
			else return true;
		}
		else {
			if (getVoxel(x, y, z + 1).type == AIR_BLOCK) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (side == BACKSIDE) {
		if (z == 0) {
			if (this->getNeighBor(side) != NULL) {
				if (this->getNeighBor(side)->getVoxel(x, y, CHUNK_SIZE - 1).type == AIR_BLOCK) return true;
				else return false;
			}
			else return true;
		}
		else {
			if (getVoxel(x, y, z - 1).type == AIR_BLOCK) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (side == LEFTSIDE) {
		if (x == 0) {
			if (this->getNeighBor(side) != NULL) {
				if (this->getNeighBor(side)->getVoxel(CHUNK_SIZE - 1, y, z).type == AIR_BLOCK) return true;
				else return false;
			}
			else return true;
		}
		else {
			if (getVoxel(x - 1, y, z).type == AIR_BLOCK) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (side == RIGHTSIDE) {
		if (x == CHUNK_SIZE - 1) {
			if (this->getNeighBor(side) != NULL) {
				if (this->getNeighBor(side)->getVoxel(0, y, z).type == AIR_BLOCK) return true;
				else return false;
			}
			else return true;
		}
		else {
			if (getVoxel(x + 1, y, z).type == AIR_BLOCK) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (side == TOPSIDE) {
		if (y == CHUNK_SIZE - 1) {
			if (this->getNeighBor(side) != NULL) {
				if (this->getNeighBor(side)->getVoxel(x, 0, z).type == AIR_BLOCK) return true;
				else return false;
			}
			else return true;
		}
		else {
			if (getVoxel(x, y + 1, z).type == AIR_BLOCK) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (side == BOTTOMSIDE) {
		if (y == 0) {
			if (this->getNeighBor(side) != NULL) {
				if (this->getNeighBor(side)->getVoxel(x, CHUNK_SIZE - 1, z).type == AIR_BLOCK) return true;
				else return false;
			}
			else return true;
		}
		else {
			if (getVoxel(x, y - 1, z).type == AIR_BLOCK) {
				return true;
			}
			else {
				return false;
			}
		}
	}

	return false;
}

void CubeChunk::greedy()
{
		cout << "Greedy Meshing in process..." << endl;

	int i, j, k, l, w, h, u, v, n, side = 0;

	int x[] = { 0,0,0 };
	int q[] = { 0,0,0 };
	int du[] = { 0,0,0 };
	int dv[] = { 0,0,0 };

	Quad mask[CHUNK_SIZE * CHUNK_SIZE];

	Quad quad, quad1;

	for (bool backFace = true, b = false; b != backFace; backFace = backFace && b, b = !b) {
		cout << "1" << endl;

		for (int d = 0; d < 3; d++) {
			cout << "2" << endl;
			u = (d + 1) % 3;
			v = (d + 2) % 3;

			x[0] = 0;
			x[1] = 0;
			x[2] = 0;

			q[0] = 0;
			q[1] = 0;
			q[2] = 0;
			q[d] = 1;

			if (d == 0) { side = backFace ? LEFTSIDE : RIGHTSIDE; }
			else if (d == 1) { side = backFace ? BOTTOMSIDE : TOPSIDE; }
			else if (d == 2) { side = backFace ? FRONTSIDE : BACKSIDE; }

			for (x[d] = -1; x[d] < CHUNK_SIZE;) {
				cout << "3" << endl;
				n = 0;

				for (x[v] = 0; x[v] < CHUNK_SIZE; x[v]++) {
					cout << "4" << endl;
					for (x[u] = 0; x[u] < CHUNK_SIZE; x[u]++) {
						cout << "5" << endl;
						(x[d] >= 0) ? this->getQuad(x[0], x[1], x[2], side, quad) : this->getQuad(x[0], x[1], x[2], -1, quad);
						(x[d] < CHUNK_SIZE - 1) ? this->getQuad(x[0] + q[0], x[1] + q[1], x[2] + q[2], side, quad1) : this->getQuad(x[0] + q[0], x[1] + q[1], x[2] + q[2], -1, quad1);

						if (quad.type != -1 && quad1.type != -1 && quad.equals(quad1)) {
							this->getQuad(x[0], x[1], x[2], -1, mask[n++]);
						}
						else {
							if (backFace) {
								mask[n++] = quad1;
							}
							else {
								mask[n++] = quad;
							}
						}
						//mask[n++] = ((quad.type != -1) && (quad1.type != -1) && quad.equals(quad1)) ? this->getQuad(x[0], x[1], x[2], -1) : backFace ? quad1 : quad;
					}
				}

				x[d]++;

				n = 0; 

				for (j = 0; j < CHUNK_SIZE; j++) {
					cout << "6" << endl;
					for (i = 0; i < CHUNK_SIZE;) {
						cout << "7" << endl;
						if (mask[n].type != -1) {
							for(w = 1; i + w < CHUNK_SIZE && mask[n + w].type != -1 && mask[n + w].equals(mask[n]);w++){
								cout << "8" << endl;
							}

							bool done = false;

							for (h = 1; h < CHUNK_SIZE; h++) {
								cout << "9" << endl;
								for (k = 0; k < CHUNK_SIZE; k++) {
									cout << "10" << endl;
									if (mask[n + k + h * CHUNK_SIZE].type == -1 || !mask[n + k + h * CHUNK_SIZE].equals(mask[n])) { done = true; }
								}
								if (done == true) break;
							}

							if (!mask[n].transparent) {
								x[u] = i;
								x[v] = j;

								du[0] = 0;
								du[1] = 0;
								du[2] = 0;
								du[u] = w;

								dv[0] = 0;
								dv[1] = 0;
								dv[2] = 0;
								dv[v] = h;

								glm::vec4 p1, p2, p3, p4;
								Point q_p1, q_p2, q_p3, q_p4;

								p1 = this->model * glm::vec4(x[0], x[1], x[2], 1.0f);
								p2 = this->model * glm::vec4(x[0] + du[0], x[1] + du[1], x[2] + du[2], 1.0f);
								p3 = this->model * glm::vec4(x[0] + du[0] + dv[0], x[1] + du[1] + dv[1], x[2] + du[2] + dv[2], 1.0f);
								p4 = this->model * glm::vec4(x[0] + dv[0], x[1] + dv[1], x[2] + dv[2], 1.0f);
								p4 = this->model * glm::vec4(x[0] + dv[0], x[1] + dv[1], x[2] + dv[2], 1.0f);

								q_p1 = { p1.x, p1.y, p1.z };
								q_p2 = { p2.x, p2.y, p2.z };
								q_p3 = { p3.x, p3.y, p3.z };
								q_p4 = { p4.x, p4.y, p4.z };

								Voxel voxel = this->getVoxel(x[0], x[1], x[2]);
								Quad quad(q_p1, q_p2, q_p3, q_p4, voxel.type, side, voxel.transparent);
								this->cubeRenderer.AddQuadToVBO(quad);
							}

							for (l = 0; l < h; ++l) {
								for (k = 0; k < w; ++k) {
									mask[n + k + l * CHUNK_SIZE].type = -1;
								}
							}

							i += w;
							n += w;
						}
						else {
							i++;
							n++;
						}
					}
				}
			}
		}

		cubeRenderer.GenerateVBO();

		cout << "Greedy Meshing: Done !" << endl;
	}
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

void CubeChunk::CreateMesh(int* heightmap, int c_x, int c_z)
{
	//create a simple chunk
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				int offset = 16 * c_x + x + 16 * 16 * (16 * c_z + z);
				int height = *(heightmap + offset);
				if (y <= height) {
					if (y >= GRASS_MIN_LIMIT && y <= GRASS_MAX_LIMIT) {
						this->setVoxel(x, y, z, GRASS_BLOCK, false);
					}
					if (y >= ROCK_MIN_LIMIT && y <= ROCK_MAX_LIMIT) {
						this->setVoxel(x, y, z, ROCK_BLOCK, false);
					}
				}
				else {
					this->setVoxel(x, y, z, AIR_BLOCK, false);
				}			
			}
		}
	}
}

void CubeChunk::Generate()
{
	this->culling();
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
