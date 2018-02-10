#pragma once
#include "GameObject.h"
#include "PieceManager.h"
#include <vector>
class Player
{
public:
	Player(bool isWhite);
	~Player();
	bool inCheck();
	bool inCheckMate();
	bool inStaleMate();
	void Update(PieceManager* pieceManager);

	std::vector <GameObject*> playerGameObjectList;
	std::vector <GameObject*> opponentGameObjectList;

	point king;
	int kingIndex;
	
	bool isWhite;
private:
	PieceManager* manager;

};

