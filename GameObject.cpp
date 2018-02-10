#include "GameObject.h"
#include "TextureManager.h"
TextureManager TexManager;

GameObject::GameObject(std::string title, SDL_Renderer* ren, int xpos, int ypos) {
	renderer = ren;
	if (title == "black pawn") {
		objTexture = TexManager.LoadTexture("Assets/Black Pawn.png", ren);
	}
	if (title == "black knight") {
		objTexture = TexManager.LoadTexture("Assets/Black Knight.png", ren);
	}
	if (title == "black bishop") {
		objTexture = TexManager.LoadTexture("Assets/Black Bishop.png", ren);
	}
	if (title == "black rook") {
		objTexture = TexManager.LoadTexture("Assets/Black Rook.png", ren);
	}
	if (title == "black queen") {
		objTexture = TexManager.LoadTexture("Assets/Black Queen.png", ren);
	}
	if (title == "black king") {
		objTexture = TexManager.LoadTexture("Assets/Black King.png", ren);
	}
	if (title == "white pawn") {
		objTexture = TexManager.LoadTexture("Assets/White Pawn.png", ren);
	}
	if (title == "white knight") {
		objTexture = TexManager.LoadTexture("Assets/White Knight.png", ren);
	}
	if (title == "white bishop") {
		objTexture = TexManager.LoadTexture("Assets/White Bishop.png", ren);
	}
	if (title == "white rook") {
		objTexture = TexManager.LoadTexture("Assets/White Rook.png", ren);
	}
	if (title == "white queen") {
		objTexture = TexManager.LoadTexture("Assets/White Queen.png", ren);
	}
	if (title == "white king") {
		objTexture = TexManager.LoadTexture("Assets/White King.png", ren);
	}

	this->title = title;
	this->position.xpos = xpos;
	this->position.ypos = ypos;
}


GameObject::~GameObject() {}

void GameObject::Update() {
	destRect.x = position.xpos * TileWidth;
	destRect.y = position.ypos * TileHeight;
	destRect.w = TileWidth;
	destRect.h = TileHeight;
}

void GameObject::Render() {
	SDL_RenderCopy(renderer, objTexture, NULL, &destRect);
}


int GameObject::getXPos() {
	return position.xpos;
}

int GameObject::getYPos() {
	return position.ypos;
}

void GameObject::setPos(int x, int y) {
	position.xpos = x;
	position.ypos = y;
}