#pragma once
#include "GameObject.h"
#include <string>
#include <vector>
#include <iostream>

struct Tile {
	bool white;
	bool black;
	bool occupied;
	bool targeted;
};

class PieceManager
{
public:
	PieceManager(SDL_Renderer* ren);
	~PieceManager();

	void addGameObject(std::string title, int xpos, int ypos);
	void removeGameObject(int xpos, int ypos, int &currPiece);
	void generateMoves(GameObject* obj, std::vector<std::vector<Tile> > &board);

	std::vector <GameObject*> gameObjectList;

	int whitePieceCount;
	int totalPieceCount;
	int boardHeight = 8;
	int boardWidth = 8;
private:
	SDL_Renderer* ren;
};

