#include "Player.h"



Player::Player(bool isWhite) {
	this->isWhite = isWhite;
}


Player::~Player()
{
}

bool Player::inCheck()
{
	for (unsigned int i = 0; i < opponentGameObjectList.size(); i++) {
		for (unsigned int j = 0; j < opponentGameObjectList[i]->possibleMoves.size(); j++) {
			if (opponentGameObjectList[i]->possibleMoves[j].xpos == king.xpos &&
				opponentGameObjectList[i]->possibleMoves[j].ypos == king.ypos) {
				return true;
			}
		}
	}
	return false;
}

bool Player::inCheckMate()
{
	return false;
}

bool Player::inStaleMate()
{
	for (unsigned int i = 0; i < playerGameObjectList.size(); i++) {
		if (!playerGameObjectList[i]->possibleMoves.empty()) {
			return false;
		}
	}
	return true;
}

void Player::Update(PieceManager* pieceManager)
{
	this->manager = pieceManager;
	if (isWhite) {
		for (unsigned int i = 0; i < this->manager->whitePieceCount; i++) {
			playerGameObjectList.push_back(this->manager->gameObjectList[i]);
			if (this->manager->gameObjectList[i]->title == "white king") {
				point p;
				p.xpos = this->manager->gameObjectList[i]->getXPos();
				p.ypos = this->manager->gameObjectList[i]->getYPos();
				king = p;
				kingIndex = i;
			}
		}
		for (unsigned int i = this->manager->whitePieceCount; i < this->manager->totalPieceCount; i++) {
			opponentGameObjectList.push_back(this->manager->gameObjectList[i]);
		}
	}
	else {
		for (unsigned int i = this->manager->whitePieceCount; i < this->manager->totalPieceCount; i++) {
			playerGameObjectList.push_back(this->manager->gameObjectList[i]);
		}
		for (unsigned int i = 0; i < this->manager->whitePieceCount; i++) {
			opponentGameObjectList.push_back(this->manager->gameObjectList[i]);
			if (this->manager->gameObjectList[i]->title == "black king") {
				point p;
				p.xpos = this->manager->gameObjectList[i]->getXPos();
				p.ypos = this->manager->gameObjectList[i]->getYPos();
				king = p;
				kingIndex = i;
			}
		}
	}
}