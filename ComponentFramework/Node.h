#ifndef NODE_H
#define NODE_H

#include <SDL.h>

#include "MMath.h"
#include "Actor.h"
#include "Shader.h"
#include "Debug.h"
#include "Texture.h"

using namespace std;
using namespace MATH;

class Tile;

class Node
{
private:
	// Model
	Actor* model_3D;
	Shader* shader;

	int	label;
	Vec3 position;
	bool isAccessible;

public:
	Node(int label_, Vec3 position_ = Vec3())
	{
		label = label_;
		position = position_;
	}

	~Node();

	// Standard functions
	bool OnCreate();
	void OnDestroy();
	void Render();

	// Get functions
	int GetLabel() { return label; }
	Vec3 GetPos() { return position; }
	bool GetIsAccesible() { return isAccessible; }

	// Set functions
	void SetPosX(float posX_) { position.x = posX_; }
	void SetPosY(float posY_) { position.y = posY_; }
	void SetPosZ(float posZ_) { position.z = posZ_; }
	void SetIsAccesible(bool isAccessible_) { isAccessible = isAccessible_; }
};

#endif // !NODE_H
