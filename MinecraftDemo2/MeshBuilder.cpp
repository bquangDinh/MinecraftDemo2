#include "MeshBuilder.h"

std::string MeshBuilder::shader = "shader_program";

MeshBuilder::MeshBuilder()
{
	faceCount = 0;
	readyToRender = false;
	glGenVertexArrays(1, &VAO);
}

MeshBuilder::~MeshBuilder()
{
	//unbind everything
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshBuilder::AddQuad(Quad quad, int width, int height, bool backface)
{
	//prevent stupid and culling method duplicate more than one texture !
	if (width <= 1.0f) width = 0;
	if (height <= 1.0f) height = 0;

#ifdef POINT_DEBUG // just using for a small chunk (use it for a large chunk will cause a crash in console)
	cout << "x: " << quad.p1.x << " y: " << quad.p1.y << " z: " << quad.p1.z << endl;
	cout << "x: " << quad.p2.x << " y: " << quad.p2.y << " z: " << quad.p2.z << endl;
	cout << "x: " << quad.p3.x << " y: " << quad.p3.y << " z: " << quad.p3.z << endl;
	cout << "x: " << quad.p4.x << " y: " << quad.p4.y << " z: " << quad.p4.z << endl;
	cout << endl;
#endif // DEBUG

	addIndicates(backface, faceCount);

	glm::vec3 normal = quad.getNormalVector();

	int textureIndex = getTextureIndex(quad.getType(), quad.getFace());

#ifdef DEBUG
	cout << "Face: " << quad.getFace() << " |Texture Index: " << textureIndex << endl;
#endif // DEBUG

	addPointV3(quad.p1);
	addPointV3(normal);
	addPointV2(glm::vec2(1.0f + width, 1.0f + height));
	addPointV2(glm::vec2(textureIndex, textureIndex));

	addPointV3(quad.p2);
	addPointV3(normal);
	addPointV2(glm::vec2(1.0f + width, 0.0f));
	addPointV2(glm::vec2(textureIndex, textureIndex));

	addPointV3(quad.p3);
	addPointV3(normal);
	addPointV2(glm::vec2(0.0f, 0.0f));
	addPointV2(glm::vec2(textureIndex, textureIndex));

	addPointV3(quad.p4);
	addPointV3(normal);
	addPointV2(glm::vec2(0.0f, 1.0f + height));
	addPointV2(glm::vec2(textureIndex, textureIndex));

	faceCount++;
}

void MeshBuilder::GenerateVBO()
{
	if (readyToRender) {
		cout << "VBO has generated already !" << endl;
	}
	else {
		glBindVertexArray(VAO);

		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, this->verticles.size() * sizeof(float), &this->verticles[0], GL_STATIC_DRAW);

		GLuint EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indicates.size() * sizeof(unsigned int), &this->indicates[0], GL_STATIC_DRAW);

		//for position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)0);

		//for normal vector
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(3 * sizeof(float)));

		//for uv
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(6 * sizeof(float)));

		//for texture index
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(8 * sizeof(float)));

		readyToRender = true;

#ifdef REPORT_DEBUG
		printReport();
#endif // DEBUG

	}
}

void MeshBuilder::CleanUp()
{
	vector<float>().swap(verticles);
	vector<unsigned int>().swap(indicates);
}

void MeshBuilder::Render()
{
	if (readyToRender) {
		//render
		if (shader == "shader_program") {
			TextureManager::GetTextureArray("texture_array").Bind();
		}
		ShaderManager::GetShaderProgram(shader).Use();
		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, this->indicates.size(), GL_UNSIGNED_INT, (void*)0);
	}
	else {
		cout << "VBO has not generated yet ! Please call GenerateVBO first !" << endl;
	}
}

void MeshBuilder::addPointV3(glm::vec3 point)
{
	this->verticles.push_back(point.x);
	this->verticles.push_back(point.y);
	this->verticles.push_back(point.z);
}

void MeshBuilder::addPointV2(glm::vec2 point)
{
	this->verticles.push_back(point.x);
	this->verticles.push_back(point.y);
}

void MeshBuilder::addIndicates(bool backface, int offset)
{
	if (!backface) {
		this->indicates.push_back(0 + 4 * offset);
		this->indicates.push_back(1 + 4 * offset);
		this->indicates.push_back(3 + 4 * offset);

		this->indicates.push_back(1 + 4 * offset);
		this->indicates.push_back(2 + 4 * offset);
		this->indicates.push_back(3 + 4 * offset);
	}
	else {
		this->indicates.push_back(3 + 4 * offset);
		this->indicates.push_back(1 + 4 * offset);
		this->indicates.push_back(0 + 4 * offset);

		this->indicates.push_back(3 + 4 * offset);
		this->indicates.push_back(2 + 4 * offset);
		this->indicates.push_back(1 + 4 * offset);
	}
}

int MeshBuilder::getTextureIndex(int type, int face)
{
	if (type == VOXEL_TYPE::GRASS) {

		if (face == SIDE::TOP) {
			return 0;
		}
		else if (face == SIDE::BOTTOM) {
			return 2;
		}
		else {
			return 3;
		}
	}

	if (type == VOXEL_TYPE::DIRT) {
		return 2;
	}

	if (type == VOXEL_TYPE::ROCK) {
		return 1;
	}

	return 2;
}

void MeshBuilder::printReport()
{
	cout << "Face count: " << "\t" << this->faceCount << endl;
	cout << "Verticles: " << "\t" << 4 * this->faceCount << endl;
}
