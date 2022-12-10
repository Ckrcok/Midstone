#ifndef NODE_TILE_H
#define NODE_TILE_H

#include "Node.h"

using namespace MATH;
using namespace std;

class NodeTile
{
private:
	Node* node;
	bool hasNode = false;
	Vec3 position;

	void AddNode(int column, int row, int label, float tileWidth, float tileHeight, Vec3 startPos, bool isAccesible);

public:
	NodeTile(Node* node_, bool hasNode_)
	{
		node = node_;
		hasNode = hasNode_;
	}

	void AddTile(int column, int row,
		int id, int label,
		float tileWidth, float tileHeight,
		Vec3 startPos, bool isAccesible);

	Node* GetNode() { return node; }
	bool HasNode() { return hasNode; }

	Vec3 GetPos() { return position; }
};

#endif // !NODE_TILE_H
