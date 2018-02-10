#include "PieceManager.h"



PieceManager::PieceManager(SDL_Renderer* ren)
{
	whitePieceCount = 16;
	totalPieceCount = 32;
	this->ren = ren;
}


PieceManager::~PieceManager()
{
}
void PieceManager::addGameObject(std::string title, int xpos, int ypos) {
	gameObjectList.push_back(new GameObject(title, ren, xpos, ypos));
}

void PieceManager::removeGameObject(int xpos, int ypos, int &currPiece) {
	for (int i = 0; i < gameObjectList.size(); i++) {
		if (gameObjectList[i]->getXPos() == xpos && gameObjectList[i]->getYPos() == ypos) {
			if (currPiece > -1 && currPiece > i) {
				currPiece--;
			}
			std::string title = gameObjectList[i]->title;
			delete gameObjectList[i];
			gameObjectList.erase(gameObjectList.begin() + i);
			if (title == "white pawn" || title == "white knight" ||
				title == "white bishop" || title == "white rook" ||
				title == "white king" || title == "white queen")
			{
				whitePieceCount--;
			}
			totalPieceCount--;
		}
	}
}

void PieceManager::generateMoves(GameObject* obj, std::vector<std::vector<Tile> > &board) {

	obj->possibleMoves.clear();
	int x = obj->getXPos();
	int y = obj->getYPos();

	if (obj->title == "black pawn") {
		if (x < 7 && y < 7) {
			if (board[x + 1][y + 1].white) {
				point p(x + 1, y + 1);
				obj->possibleMoves.push_back(p);
			}
		}
		if (x > 0 && y < 7) {
			if (board[x - 1][y + 1].white) {
				point p(x - 1, y + 1);
				obj->possibleMoves.push_back(p);
			}
		}
		if (y < 7) {
			if (!board[x][y + 1].occupied) {
				point p(x, y + 1);
				obj->possibleMoves.push_back(p);
			}
		}
		if (y = 1) {
			if (!board[x][y + 2].occupied) {
				point p(x, y + 2);
				obj->possibleMoves.push_back(p);
			}
		}
	}

	if (obj->title == "black knight") {
		if (x < 6 && y > 0) {
			if (!board[x + 2][y - 1].black) {
				point p(x + 2, y - 1);
				obj->possibleMoves.push_back(p);
			}
		}

		if (x < 6 && y < 7) {
			if (!board[x + 2][y + 1].black) {
				point p(x + 2, y + 1);
				obj->possibleMoves.push_back(p);
			}
		}

		if (x > 1 && y > 0) {
			if (!board[x - 2][y - 1].black) {
				point p(x - 2, y - 1);
				obj->possibleMoves.push_back(p);
			}
		}

		if (x > 1 && y < 7) {
			if (!board[x - 2][y + 1].black) {
				point p(x - 2, y + 1);
				obj->possibleMoves.push_back(p);
			}
		}

		if (x < 7 && y > 1) {
			if (!board[x + 1][y - 2].black) {
				point p(x + 1, y - 2);
				obj->possibleMoves.push_back(p);
			}
		}

		if (x < 7 && y < 6) {
			if (!board[x + 1][y + 2].black) {
				point p(x + 1, y + 2);
				obj->possibleMoves.push_back(p);
			}
		}

		if (x > 0 && y > 1) {
			if (!board[x - 1][y - 2].black) {
				point p(x - 1, y - 2);
				obj->possibleMoves.push_back(p);
			}
		}

		if (x > 0 && y < 6) {
			if (!board[x - 1][y + 2].black) {
				point p(x - 1, y + 2);
				obj->possibleMoves.push_back(p);
			}
		}
	}

	if (obj->title == "black bishop") {
		int counter = 1;
		bool flag = true;
		while (counter + x < boardWidth && counter + y < boardWidth && flag) {
			if (board[counter + x][counter + y].white) {
				point p(counter + x, counter + y);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[counter + x][counter + y].occupied) {
				point p(counter + x, counter + y);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}


		counter = 1;
		flag = true;
		while (x - counter >= 0 && y + counter < boardWidth && flag) {
			if (board[x - counter][y + counter].white) {
				point p(x - counter, y + counter);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x - counter][y + counter].occupied) {
				point p(x - counter, y + counter);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}

		counter = 1;
		flag = true;
		while (x - counter >= 0 && y - counter >= 0 && flag) {
			if (board[x - counter][y - counter].white) {
				point p(x - counter, y - counter);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x - counter][y - counter].occupied) {
				point p(x - counter, y - counter);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}

		counter = 1;
		flag = true;
		while (x + counter < boardWidth && y - counter >= 0 && flag) {
			if (board[x + counter][y - counter].white) {
				point p(x + counter, y - counter);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x + counter][y - counter].occupied) {
				point p(x + counter, y - counter);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}
	}

	if (obj->title == "black rook") {
		int counter = 1;
		bool flag = true;
		while (x + counter < boardWidth && flag) {
			if (board[x + counter][y].white) {
				point p(x + counter, y);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x + counter][y].occupied) {
				point p(x + counter, y);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}

		counter = 1;
		flag = true;
		while (x - counter >= 0 && flag) {
			if (board[x - counter][y].white) {
				point p(x - counter, y);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x - counter][y].occupied) {
				point p(x - counter, y);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}

		counter = 1;
		flag = true;
		while (y + counter < boardWidth && flag) {
			if (board[x][y + counter].white) {
				point p(x, y + counter);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x][y + counter].occupied) {
				point p(x, y + counter);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}

		counter = 1;
		flag = true;
		while (y - counter >= 0 && flag) {
			if (board[x][y - counter].white) {
				point p(x, y - counter);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x][y - counter].occupied) {
				point p(x, y - counter);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}
	}

	if (obj->title == "black queen") {
		int counter = 1;
		bool flag = true;
		while (counter + x < boardWidth && counter + y < boardWidth && flag) {
			if (board[counter + x][counter + y].white) {
				point p(counter + x, counter + y);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[counter + x][counter + y].occupied) {
				point p(counter + x, counter + y);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}


		counter = 1;
		flag = true;
		while (x - counter >= 0 && y + counter < boardWidth && flag) {
			if (board[x - counter][y + counter].white) {
				point p(x - counter, y + counter);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x - counter][y + counter].occupied) {
				point p(x - counter, y + counter);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}

		counter = 1;
		flag = true;
		while (x - counter >= 0 && y - counter >= 0 && flag) {
			if (board[x - counter][y - counter].white) {
				point p(x - counter, y - counter);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x - counter][y - counter].occupied) {
				point p(x - counter, y - counter);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}

		counter = 1;
		flag = true;
		while (x + counter < boardWidth && y - counter >= 0 && flag) {
			if (board[x + counter][y - counter].white) {
				point p(x + counter, y - counter);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x + counter][y - counter].occupied) {
				point p(x + counter, y - counter);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}

		counter = 1;
		flag = true;
		while (x + counter < boardWidth && flag) {
			if (board[x + counter][y].white) {
				point p(x + counter, y);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x + counter][y].occupied) {
				point p(x + counter, y);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}

		counter = 1;
		flag = true;
		while (x - counter >= 0 && flag) {
			if (board[x - counter][y].white) {
				point p(x - counter, y);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x - counter][y].occupied) {
				point p(x - counter, y);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}

		counter = 1;
		flag = true;
		while (y + counter < boardWidth && flag) {
			if (board[x][y + counter].white) {
				point p(x, y + counter);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x][y + counter].occupied) {
				point p(x, y + counter);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}

		counter = 1;
		flag = true;
		while (y - counter >= 0 && flag) {
			if (board[x][y - counter].white) {
				point p(x, y - counter);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x][y - counter].occupied) {
				point p(x, y - counter);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}
	}

	if (obj->title == "black king") {
		if (x < 7 && y < 7) {
			if (!board[x + 1][y + 1].black) {
				point p(x + 1, y + 1);
				obj->possibleMoves.push_back(p);
			}
		}
		if (x > 0 && y < 7) {
			if (!board[x - 1][y + 1].black) {
				point p(x - 1, y + 1);
				obj->possibleMoves.push_back(p);
			}
		}
		if (y < 7) {
			if (!board[x][y + 1].black) {
				point p(x, y + 1);
				obj->possibleMoves.push_back(p);
			}
		}
		if (x > 0 && y > 0) {
			if (!board[x - 1][y - 1].black) {
				point p(x - 1, y - 1);
				obj->possibleMoves.push_back(p);
			}
		}
		if (x < 7 && y > 0) {
			if (!board[x + 1][y - 1].black) {
				point p(x + 1, y - 1);
				obj->possibleMoves.push_back(p);
			}
		}
		if (y > 0) {
			if (!board[x][y - 1].black) {
				point p(x, y - 1);
				obj->possibleMoves.push_back(p);
			}
		}
		if (x < 7) {
			if (!board[x + 1][y].black) {
				point p(x + 1, y);
				obj->possibleMoves.push_back(p);
			}
		}
		if (x > 0) {
			if (!board[x - 1][y].black) {
				point p(x - 1, y);
				obj->possibleMoves.push_back(p);
			}
		}
	}

	//white pieces


	if (obj->title == "white pawn") {
		if (x < 7 && y > 0) {
			if (board[x + 1][y - 1].black) {
				point p(x + 1, y - 1);
				obj->possibleMoves.push_back(p);
			}
		}
		if (x > 0 && y > 0) {
			if (board[x - 1][y - 1].black) {
				point p(x - 1, y - 1);
				obj->possibleMoves.push_back(p);
			}
		}
		if (y > 0) {
			if (!board[x][y - 1].occupied) {
				point p(x, y - 1);
				obj->possibleMoves.push_back(p);
			}
		}
		if (y == 6) {
			if (!board[x][y - 2].occupied) {
				point p(x, y - 2);
				obj->possibleMoves.push_back(p);
			}
		}
	}

	if (obj->title == "white knight") {
		if (x < 6 && y > 0) {
			if (!board[x + 2][y - 1].white) {
				point p(x + 2, y - 1);
				obj->possibleMoves.push_back(p);
			}
		}

		if (x < 6 && y < 7) {
			if (!board[x + 2][y + 1].white) {
				point p(x + 2, y + 1);
				obj->possibleMoves.push_back(p);
			}
		}

		if (x > 1 && y > 0) {
			if (!board[x - 2][y - 1].white) {
				point p(x - 2, y - 1);
				obj->possibleMoves.push_back(p);
			}
		}

		if (x > 1 && y < 7) {
			if (!board[x - 2][y + 1].white) {
				point p(x - 2, y + 1);
				obj->possibleMoves.push_back(p);
			}
		}

		if (x < 7 && y > 1) {
			if (!board[x + 1][y - 2].white) {
				point p(x + 1, y - 2);
				obj->possibleMoves.push_back(p);
			}
		}

		if (x < 7 && y < 6) {
			if (!board[x + 1][y + 2].white) {
				point p(x + 1, y + 2);
				obj->possibleMoves.push_back(p);
			}
		}

		if (x > 0 && y > 1) {
			if (!board[x - 1][y - 2].white) {
				point p(x - 1, y - 2);
				obj->possibleMoves.push_back(p);
			}
		}

		if (x > 0 && y < 6) {
			if (!board[x - 1][y + 2].white) {
				point p(x - 1, y + 2);
				obj->possibleMoves.push_back(p);
			}
		}
	}

	if (obj->title == "white bishop") {
		int counter = 1;
		bool flag = true;
		while (counter + x < boardWidth && counter + y < boardWidth && flag) {
			if (board[counter + x][counter + y].black) {
				point p(counter + x, counter + y);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[counter + x][counter + y].occupied) {
				point p(counter + x, counter + y);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}


		counter = 1;
		flag = true;
		while (x - counter >= 0 && y + counter < boardWidth && flag) {
			if (board[x - counter][y + counter].black) {
				point p(x - counter, y + counter);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x - counter][y + counter].occupied) {
				point p(x - counter, y + counter);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}

		counter = 1;
		flag = true;
		while (x - counter >= 0 && y - counter >= 0 && flag) {
			if (board[x - counter][y - counter].black) {
				point p(x - counter, y - counter);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x - counter][y - counter].occupied) {
				point p(x - counter, y - counter);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}

		counter = 1;
		flag = true;
		while (x + counter < boardWidth && y - counter >= 0 && flag) {
			if (board[x + counter][y - counter].black) {
				point p(x + counter, y - counter);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x + counter][y - counter].occupied) {
				point p(x + counter, y - counter);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}
	}

	if (obj->title == "white rook") {
		int counter = 1;
		bool flag = true;
		while (x + counter < boardWidth && flag) {
			if (board[x + counter][y].black) {
				point p(x + counter, y);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x + counter][y].occupied) {
				point p(x + counter, y);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}

		counter = 1;
		flag = true;
		while (x - counter >= 0 && flag) {
			if (board[x - counter][y].black) {
				point p(x - counter, y);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x - counter][y].occupied) {
				point p(x - counter, y);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}

		counter = 1;
		flag = true;
		while (y + counter < boardWidth && flag) {
			if (board[x][y + counter].black) {
				point p(x, y + counter);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x][y + counter].occupied) {
				point p(x, y + counter);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}

		counter = 1;
		flag = true;
		while (y - counter >= 0 && flag) {
			if (board[x][y - counter].black) {
				point p(x, y - counter);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x][y - counter].occupied) {
				point p(x, y - counter);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}
	}

	if (obj->title == "white queen") {
		int counter = 1;
		bool flag = true;
		while (counter + x < boardWidth && counter + y < boardWidth && flag) {
			if (board[counter + x][counter + y].black) {
				point p(counter + x, counter + y);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[counter + x][counter + y].occupied) {
				point p(counter + x, counter + y);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}


		counter = 1;
		flag = true;
		while (x - counter >= 0 && y + counter < boardWidth && flag) {
			if (board[x - counter][y + counter].black) {
				point p(x - counter, y + counter);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x - counter][y + counter].occupied) {
				point p(x - counter, y + counter);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}

		counter = 1;
		flag = true;
		while (x - counter >= 0 && y - counter >= 0 && flag) {
			if (board[x - counter][y - counter].black) {
				point p(x - counter, y - counter);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x - counter][y - counter].occupied) {
				point p(x - counter, y - counter);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}

		counter = 1;
		flag = true;
		while (x + counter < boardWidth && y - counter >= 0 && flag) {
			if (board[x + counter][y - counter].black) {
				point p(x + counter, y - counter);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x + counter][y - counter].occupied) {
				point p(x + counter, y - counter);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}

		counter = 1;
		flag = true;
		while (x + counter < boardWidth && flag) {
			if (board[x + counter][y].black) {
				point p(x + counter, y);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x + counter][y].occupied) {
				point p(x + counter, y);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}

		counter = 1;
		flag = true;
		while (x - counter >= 0 && flag) {
			if (board[x - counter][y].black) {
				point p(x - counter, y);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x - counter][y].occupied) {
				point p(x - counter, y);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}

		counter = 1;
		flag = true;
		while (y + counter < boardWidth && flag) {
			if (board[x][y + counter].black) {
				point p(x, y + counter);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x][y + counter].occupied) {
				point p(x, y + counter);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}

		counter = 1;
		flag = true;
		while (y - counter >= 0 && flag) {
			if (board[x][y - counter].black) {
				point p(x, y - counter);
				obj->possibleMoves.push_back(p);
				flag = false;
			}
			if (!board[x][y - counter].occupied) {
				point p(x, y - counter);
				obj->possibleMoves.push_back(p);
			}
			else {
				flag = false;
			}
			counter++;
		}
	}

	if (obj->title == "white king") {
		if (x < 7 && y < 7) {
			if (!board[x + 1][y + 1].white) {
				point p(x + 1, y + 1);
				obj->possibleMoves.push_back(p);
			}
		}
		if (x > 0 && y < 7) {
			if (!board[x - 1][y + 1].white) {
				point p(x - 1, y + 1);
				obj->possibleMoves.push_back(p);
			}
		}
		if (y < 7) {
			if (!board[x][y + 1].white) {
				point p(x, y + 1);
				obj->possibleMoves.push_back(p);
			}
		}
		if (x > 0 && y > 0) {
			if (!board[x - 1][y - 1].white) {
				point p(x - 1, y - 1);
				obj->possibleMoves.push_back(p);
			}
		}
		if (x < 7 && y > 0) {
			if (!board[x + 1][y - 1].white) {
				point p(x + 1, y - 1);
				obj->possibleMoves.push_back(p);
			}
		}
		if (y > 0) {
			if (!board[x][y - 1].white) {
				point p(x, y - 1);
				obj->possibleMoves.push_back(p);
			}
		}
		if (x < 7) {
			if (!board[x + 1][y].white) {
				point p(x + 1, y);
				obj->possibleMoves.push_back(p);
			}
		}
		if (x > 0) {
			if (!board[x - 1][y].white) {
				point p(x - 1, y);
				obj->possibleMoves.push_back(p);
			}
		}
	}
}