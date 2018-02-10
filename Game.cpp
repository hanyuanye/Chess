#include "Game.h"
#include "TextureManager.h"


Game::Game() {}

Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 138, 0, 0);
		}

		running = true;
	}
	else {
		running = false;
	}

	boardHeight = 8;
	boardWidth = 8;

	board.resize(boardHeight, std::vector<Tile>(boardWidth));
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
			board[i][j].white = false;
			board[i][j].black = false;
			board[i][j].targeted = false;
		}
	}

	this->pieceManager = new PieceManager(renderer);
	
	for (int i = 0; i < 8; i++) {
		pieceManager->addGameObject("white pawn", i, 6);
	}
	pieceManager->addGameObject("white rook", 0, 7);
	pieceManager->addGameObject("white rook", 7, 7);
	pieceManager->addGameObject("white knight", 1, 7);
	pieceManager->addGameObject("white knight", 6, 7);
	pieceManager->addGameObject("white bishop", 2, 7);
	pieceManager->addGameObject("white bishop", 5, 7);
	pieceManager->addGameObject("white queen", 3, 7);
	pieceManager->addGameObject("white king", 4, 7);

	for (int i = 0; i < 8; i++) {
		pieceManager->addGameObject("black pawn", i, 1);
	}
	pieceManager->addGameObject("black rook", 0, 0);
	pieceManager->addGameObject("black rook", 7, 0);
	pieceManager->addGameObject("black knight", 1, 0);
	pieceManager->addGameObject("black knight", 6, 0);
	pieceManager->addGameObject("black bishop", 2, 0);
	pieceManager->addGameObject("black bishop", 5, 0);
	pieceManager->addGameObject("black queen", 3, 0);
	pieceManager->addGameObject("black king", 4, 0);

	white = new Player(true);
	black = new Player(false);
	currPlayerIsWhite = true;
	targeting = false;

}

void Game::handleEvent() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		running = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (SDL_BUTTON(SDL_BUTTON_LEFT)) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			handleLeftXYClick(x, y, currPlayerIsWhite);
		}
		else {
			if (SDL_BUTTON(SDL_BUTTON_RIGHT)) {
				handleRightClick();
			}
		}
	default:
		break;
	}
}

void Game::handleLeftXYClick(int x, int y, bool isWhite) {
	std::cout << "handling left click" << std::endl;
	if (x < TileWidth * boardWidth && y < TileHeight * boardHeight) {
		x = x / TileWidth;
		y = y / TileHeight;
	}
	if (!targeting) {
		std::cout << "handling not targeting" << std::endl;
		int piece = -1;
		if (isWhite) {
			std::cout << "isWhite" << std::endl;
			std::cout << board[x][y].black << std::endl;
			if (board[x][y].white) {
				for (int i = 0; i < pieceManager->whitePieceCount; i++) {
					if (pieceManager->gameObjectList[i]->getXPos() == x && pieceManager->gameObjectList[i]->getYPos() == y) {

						piece = i;
					}
				}
			}
		}
		else if(!isWhite) {
			std::cout << "isBlack" << std::endl;
			for (int i = pieceManager->whitePieceCount; i < pieceManager->totalPieceCount; i++) {
				if (pieceManager->gameObjectList[i]->getXPos() == x && pieceManager->gameObjectList[i]->getYPos() == y) {

					piece = i;
				}
			}
		}

		if (piece == -1) {
			return;
		}
		else {
			currPiece = piece;
		}
		pieceManager->generateMoves(pieceManager->gameObjectList[piece], board);
		int xtmp, ytmp;
		for (int i = 0; i < pieceManager->gameObjectList[piece]->possibleMoves.size(); i++) {
			xtmp = pieceManager->gameObjectList[piece]->possibleMoves[i].xpos;
			ytmp = pieceManager->gameObjectList[piece]->possibleMoves[i].ypos;
			board[xtmp][ytmp].targeted = true;
		}
		targeting = true;
	}
	else {
		std::cout << "handling targeting" << std::endl;
		std::cout << currPiece << std::endl;
		if (board[x][y].targeted) {
			if (board[x][y].occupied) {
				pieceManager->removeGameObject(x, y, currPiece);
			}
			pieceManager->gameObjectList[currPiece]->setPos(x, y);
			currPlayerIsWhite = !currPlayerIsWhite;
		}
		targeting = false;
		for (int i = 0; i < boardHeight; i++) {
			for (int j = 0; j < boardWidth; j++) {
				board[i][j].targeted = false;
			}
		}
		currPiece = -1;
	}
}

void Game::handleRightClick() {
	std::cout << "handling right click" << std::endl;
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
			board[i][j].targeted = false;
		}
	}
	targeting = false;
}

void Game::update() {
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
			board[i][j].occupied = false;
			board[i][j].white = false;
			board[i][j].black = false;
		}
	}

	for (int i = 0; i < pieceManager->whitePieceCount; i++) {
		pieceManager->gameObjectList[i]->Update();
		board[pieceManager->gameObjectList[i]->getXPos()][pieceManager->gameObjectList[i]->getYPos()].white = true;
		board[pieceManager->gameObjectList[i]->getXPos()][pieceManager->gameObjectList[i]->getYPos()].occupied = true;
		pieceManager->generateMoves(pieceManager->gameObjectList[i], board);
	}

	for (int i = pieceManager->whitePieceCount; i < pieceManager->gameObjectList.size(); i++) {
		pieceManager->gameObjectList[i]->Update();
		board[pieceManager->gameObjectList[i]->getXPos()][pieceManager->gameObjectList[i]->getYPos()].black = true;
		board[pieceManager->gameObjectList[i]->getXPos()][pieceManager->gameObjectList[i]->getYPos()].occupied = true;
		pieceManager->generateMoves(pieceManager->gameObjectList[i], board);
	}


	white->Update(pieceManager);
	black->Update(pieceManager);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::render() {
	SDL_RenderClear(renderer);
	Game::renderBoard();
	SDL_SetRenderDrawColor(renderer, 0, 102, 0, 0);

	for (int i = 0; i < pieceManager->gameObjectList.size(); i++) {
		pieceManager->gameObjectList[i]->Render();
	}
	SDL_RenderPresent(renderer);
}

void Game::renderBoard() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (!board[i][j].targeted) {
				if ((i - j) % 2) {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				}
				else {
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
				}
			}
			else {
				SDL_SetRenderDrawColor(renderer, 255, 140, 0, 255);
			}

			SDL_Rect r;
			r.x = i * TileWidth;
			r.y = j * TileHeight;
			r.w = TileWidth;
			r.h = TileHeight;

			SDL_RenderFillRect(renderer, &r);
		}
	}
}
