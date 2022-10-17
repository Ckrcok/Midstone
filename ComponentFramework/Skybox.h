#pragma once
#include "Component.h"
#include "Shader.h"


class Mesh;
class Skybox : public Component
{
private:
	GLuint skyboxTextureID;
	Mesh* mesh;
	Shader* shader;
	const char* posXfilename, * posYfilename, * posZfilename, * negXfilename, * negYfilename, * negZfilename;
public:
	Skybox(const char* posXfilename_, const char* posYfilename_, const char* posZfilename_, const char* negXfilename_, const char* negYfilename_, const char* negZfilename_);
	~Skybox();

	Shader* GetShader() { return shader; }

	GLuint GetSkyboxTextureID() { return skyboxTextureID; }

	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime_) override;
	void Render()const override;
};

