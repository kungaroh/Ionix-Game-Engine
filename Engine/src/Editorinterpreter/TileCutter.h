#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Architecture/EngineSystems.h"
#include <Scripting/Scripting.h>
#include "Architecture/Application.h"

class TileCutter
{
public:
    std::string SaveTextureAsPNG(SDL_Renderer* renderer, SDL_Texture* texture, const std::string& fileName)
    {
        // Grabs data such as width/height and pixel format from the texture we wish to save to.png
        int w, h;
        Uint32 textureFormat;
        SDL_QueryTexture(texture, &textureFormat, NULL, &w, &h);

        SDL_Texture* targetTexture = SDL_CreateTexture(renderer, textureFormat, SDL_TEXTUREACCESS_TARGET, w, h);
        SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, w, h, SDL_BITSPERPIXEL(textureFormat), textureFormat);

        SDL_SetRenderTarget(renderer, targetTexture);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderReadPixels(renderer, NULL, surface->format->format, surface->pixels, surface->pitch);
        SDL_SetRenderTarget(renderer, NULL);

        std::string fullPath = IonixEngine::EngineSystems::ProjectPath() + "/textures/" + fileName + ".png";
        bool success = (IMG_SavePNG(surface, fullPath.c_str()) == 0);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(targetTexture);

        return success ? fullPath : "";
    }

	// tiledData = exported lua data - allows us to get access to key dimensions
    SDL_Texture* CreateTexture(const IonixEngine::TiledData& tiledData)
    {
        const int textureSizeX = tiledData.mapWidth * tiledData.tileWidth;
        const int textureSizeY = tiledData.mapHeight * tiledData.tileHeight;

        // Created with consistent format
        SDL_Texture* texture = SDL_CreateTexture(
            IonixEngine::Application::Get().GetWindow().m_Renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_TARGET,
            textureSizeX,
            textureSizeY
        );

        return texture;
    }
};