#pragma once
#include "Game.h"

class TextureManager {

public:
	SDL_Texture * LoadTexture(const char* texture, SDL_Renderer* renderer);

};
