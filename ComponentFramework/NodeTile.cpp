#include "NodeTile.h"

void NodeTile::AddTile(
	int column, int row,
	int id, int label,
	float tileWidth, float tileHeight,
	Vec3 startPos)
{
	// Debug for tile spawning
	//cout << "Tile with label: " << label << " has been created!" << endl;

	// Set the position to have the origin top left
	position.x = startPos.x + column * tileWidth + (tileWidth * 0.5f);
	position.y = 0.0f;
	position.z = startPos.z + row * tileHeight + (tileHeight * 0.5f);

	// Place node if the tile has a node
	if (hasNode)
		AddNode(column, row, label, tileWidth, tileHeight, startPos);
}

void NodeTile::AddNode(int column, int row, int label, float tileWidth, float tileHeight, Vec3 startPos)
{
	// Create start node
	Node* n = new Node(label);

	// Set the position to have the origin top left
	n->SetPosX(startPos.x + column * tileWidth + (tileWidth * 0.5f));
	n->SetPosY(startPos.y);
	n->SetPosZ(startPos.z + row * tileHeight + (tileHeight * 0.5f));

	//// Transverse the position from viewport to game
	//Vec3 position = Vec3(n->GetPos().x, n->GetPos().y, n->GetPos().z);

	//// Set the position to the game coordinates
	//n->SetPosX(position.x);
	//n->SetPosY(position.y);

	// Set the node of the class to the created one
	node = n;

	// Debug for node position
	/**
	cout << "NodePos from node " << label << ":";
	node->GetPos().print();
	/**/

	node->OnCreate();
}
