#pragma once 
#include <string>
#include <iostream>
#include "Logging/Console.h"
#include <sstream>
#include <unordered_map>
#include <SDL.h>
#include "ResourceManager.h"
#include "Architecture/Application.h"
#include "Editorinterpreter/Tile.h"

using namespace std;

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

};

namespace IonixEngine
{
	class EditorInterpreter
	{
	public:

        // The tiles associated with each layer
        std::vector<std::vector<Tile>> tiles;

        // Stores all objects and their associated data
        std::vector<Tile> objectTiles;

        // Look-up map for referencing SDL_Texture with a gid
        std::unordered_map<int, SDL_Texture*> tileMapTextures;

        void GenerateEngineTileData(const TiledData& tiledData)
        {
            SDL_Renderer& renderer = *Application::Get().GetWindow().m_Renderer;
            const int tileWidth = tiledData.tileWidth;
            const int tileHeight = tiledData.tileHeight;

            for (const auto& tileset : tiledData.tiledSets)
            {
                std::string fullPath = IonixEngine::EngineSystems::ProjectPath() + "/textures/" + tileset.filename + ".png";
                SDL_Surface* tempSurface = ResourceManager::GetInstance().GetSurface(fullPath);

                SDL_Surface* atlasSurface = SDL_ConvertSurfaceFormat(tempSurface, SDL_PIXELFORMAT_ARGB8888, 0);
                SDL_Texture* atlasTexture = SDL_CreateTextureFromSurface(&renderer, atlasSurface);

                const int atlasColumns = atlasSurface->w / tileWidth;
                const int atlasRows = atlasSurface->h / tileHeight;
                SDL_SetRenderTarget(Application::Get().GetWindow().GetSdlRenderer(), atlasTexture);

                SDL_Rect srcRect = { 0, 0, tileWidth, tileHeight };

                for (int tileID = tileset.firstgid; tileID < atlasColumns * atlasRows + tileset.firstgid; ++tileID)
                {
                    srcRect.x = ((tileID - tileset.firstgid) % atlasColumns) * tileWidth;
                    srcRect.y = ((tileID - tileset.firstgid) / atlasColumns) * tileHeight;

                    SDL_Surface* tileSurface = SDL_CreateRGBSurfaceWithFormat(
                        0, tileWidth, tileHeight, 32, SDL_PIXELFORMAT_ARGB8888);

                    SDL_BlitSurface(atlasSurface, &srcRect, tileSurface, nullptr);
                    SDL_Texture* tileTexture = SDL_CreateTextureFromSurface(&renderer, tileSurface);

                    // Add the newly generated texture to the map and associate it with the respective ID.
                    // This means we can reference tileMapTextures with a gid to access an SDL_Texture* 
                    tileMapTextures[tileID] = tileTexture;
                    SDL_FreeSurface(tileSurface);
                }

                SDL_SetRenderTarget(Application::Get().GetWindow().GetSdlRenderer(), nullptr);
            }

            // Adds key detail to each tile (gid, position, size, texture, name, ..)
            AddTileMetaData(tiledData);


            // Loop over all layers
            for (const auto& layer : tiledData.tiledLayers)
            {
                // If no objects, skip current layer for performance
                if (layer.tiledObjects.empty()) continue;

                // If there are objects on the layer (ideally only one layer should have objects)
                // Initialise a new Tile (tile) and push it to the objectTiles vector for processing later on
                for (const auto& object : layer.tiledObjects)
                {
                    Tile tile;
                    tile.name = object.name;
                    tile.tileID = object.gid;
                    tile.xPos = object.x;
                    tile.yPos = object.y;
                    tile.xSize = object.width;
                    tile.ySize = object.height;
                    tile.tileTexture = tileMapTextures[tile.tileID];

                    objectTiles.push_back(tile);
                }
            }

            // Sets the SDL Window size to match the map dimensions
            SDL_SetWindowSize(Application::Get().GetWindow().m_Window,
                tiledData.mapWidth * tileWidth,
                tiledData.mapHeight * tileHeight);
            SDL_SetWindowResizable(Application::Get().GetWindow().m_Window, SDL_FALSE);
        }

        void AddTileMetaData(const TiledData& tiledData)
        {
            // initialise variables/dimensions
            int xPos = 0;
            int yPos = 0;
            int tileWidth = tiledData.tileWidth;
            int tileHeight = tiledData.tileHeight;
            int mapWidth = tiledData.mapWidth;

            for (const auto& layer : tiledData.tiledLayers)
            {
                std::vector<Tile> tilesForLayer;
                tilesForLayer.reserve(layer.tilemapIDdata.size());

                for (size_t j = 0; j < layer.tilemapIDdata.size(); ++j)
                {
                    // caches gid
                    const int tileToDraw = layer.tilemapIDdata[j];

                    // If we are at the end of a row, start a new one
                    if (j % mapWidth == 0 && j > 0)
                    {
                        yPos += tileHeight;
                        xPos = 0;
                    }

                    // If the gid is 0 then we know there is no tile drawn; skip.
                    if (tileToDraw == 0)
                    {
                        xPos += tileWidth;
                        continue;
                    }

                    // Initialise and push new tile 
                    Tile newTile;
                    newTile.name = layer.name;
                    newTile.tileID = tileToDraw;
                    newTile.tileTexture = tileMapTextures[tileToDraw];
                    newTile.xPos = xPos;
                    newTile.yPos = yPos;
                    newTile.xSize = tileWidth;
                    newTile.ySize = tileHeight;

                    tilesForLayer.push_back(newTile);
                    xPos += tileWidth;
                }

                tiles.push_back(tilesForLayer);
                xPos = 0;
                yPos = 0;
            }
        }
	};
}