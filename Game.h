#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include "GameObject.h"
#include "Player.h"
#include "PieceManager.h"


const int TileHeight = 100;
const int TileWidth = 100;

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvent();
	void handleLeftXYClick(int x, int y, bool isWhite);
	void handleRightClick();
	void update();
	void clean();
	void render();
	void renderBoard();
	std::vector<GameObject*> gameObjectList;
	PieceManager* pieceManager;

	bool running;
	bool currPlayerIsWhite;

private:

	int count;
	bool isRunning;
	SDL_Window *window;
	SDL_Renderer *renderer;
	std::vector<std::vector<Tile> > board;
	int boardHeight;
	int boardWidth;

	bool targeting;
	int currPiece;

	Player* white;
	Player* black;
};