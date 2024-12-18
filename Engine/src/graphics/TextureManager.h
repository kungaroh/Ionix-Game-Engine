#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Graphics.h"
#include <unordered_map>
#include <string>

using namespace std;
namespace IonixEngine
{
	class TextureManager
	{
		Graphics* graphics;
	public:
		TextureManager(Graphics* parent) : graphics(parent) {}
		SDL_Texture* GetSDLTexture(string fileName);

	};
}