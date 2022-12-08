#ifndef NODE_H
#define NODE_H

#include "MMath.h"

using namespace std;
using namespace MATH;

class Tile;

class Node
{
private:
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

	// Get functions
	int GetLabel() { return label; }
	Vec3 GetPos() { return position; }
	bool GetIsAccesible() { return isAccessible; }

	// Set functions
	void SetPosX(float posX_) { position.x = posX_; }
	void SetPosY(float posY_) { position.y = posY_; }
};

#endif // !NODE_H
