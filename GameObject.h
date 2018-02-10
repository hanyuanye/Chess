#pragma once
#include <vector>
#include <string>
#include <SDL.h>

const float timeStep = 1 / 60;

struct point {
	int xpos;
	int ypos;
	point(int x, int y) : xpos(x),ypos(y) {}
	point() : xpos(0), ypos(0) {}
};

class GameObject {

public:
	GameObject(std::string title, SDL_Renderer* ren, int xpos, int ypos);
	~GameObject();

	void Update();
	void Render();
	int getXPos();
	int getYPos();
	void setPos(int x, int y);
	std::vector <point> possibleMoves;
	std::string title;
	
private:

	SDL_Texture * objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

	point position;

};