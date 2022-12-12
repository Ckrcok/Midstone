//#pragma once
//#include "Component.h"
//#include <glew.h>
//#include <vector>
//#include "Vector.h"
//using namespace MATH;
//
//class LightMesh : public Component {
//	LightMesh(const LightMesh&) = delete;
//	LightMesh(LightMesh&&) = delete;
//	LightMesh& operator = (const LightMesh&) = delete;
//	LightMesh& operator = (LightMesh&&) = delete;
//
//private:
//	const char* filename;
//	std::vector<Vec3> vertices;
//	std::vector<Vec3> normals;
//	std::vector<Vec2> uvCoords;
//	size_t dateLength;
//	GLenum drawmode;
//
//	/// Private helper methods
//	void LoadModel(const char* filename);
//	void StoreMeshData(GLenum drawmode_);
//	GLuint lightVao, lightVbo;
//public:
//
//	LightMesh(Component* parent_, const char* filename_);
//	~LightMesh();
//	bool OnCreate();
//	void OnDestroy();
//	void Update(const float deltaTime);
//	void Render() const;
//	void Render(GLenum drawmode) const;
//
//};
//
