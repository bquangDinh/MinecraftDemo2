#include "Shadow.h"

Shadow::Shadow()
{
	
}

Shadow::~Shadow()
{
}

void Shadow::Initialize()
{
	shadowMap = new Texture2D();
	shadowMap->Data_Type = GL_FLOAT;
	shadowMap->Internal_Format = GL_DEPTH_COMPONENT;
	shadowMap->Image_Format = GL_DEPTH_COMPONENT;
	shadowMap->Generate(800, 600, NULL);

	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap->ID, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "Frame buffer is not complete" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Shadow::Update()
{
}
