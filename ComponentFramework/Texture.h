#ifndef TEXTURE_H
#define TEXTURE_H
#include <glew.h>
class Texture {
	GLuint textureID;
	const char* filename;
public:
	Texture();
	~Texture();
	bool LoadImage(const char* filename);
	inline GLuint getTextureID() const { return textureID; }


};
#endif
