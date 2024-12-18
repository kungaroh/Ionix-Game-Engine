#pragma once
#include <vector>
#include "Editorinterpreter/Tile.h"
#include "SDL.h"
#include "Architecture/Application.h"
#include "TileCutter.h"
#include "Components/SpriteComponent.h"
#include <Components/PhysicsComponent.h>
#include "ResourceManager.h"


std::unordered_map<std::string, int> zLayerPositions;


class TileMapObjects
{
public:
	std::vector<Tile> physTiles;	

	void ProcessLayer(const std::vector<Tile>& tiles, SDL_Texture* compositeTexture)
	{
		zLayerPositions.insert(std::make_pair("LayerDecoration", 0));
		zLayerPositions.insert(std::make_pair("LayerStatic", 1));
		zLayerPositions.insert(std::make_pair("LayerBackground", 2));

		// Loops through all of the respective positional/gid data of the layer data that's passed in
		for (int i = 0; i < tiles.size(); i++)
		{		
			if (tiles.size() < 1)
				continue;
			if (tiles[i].name == "LayerBackground" ||	// (sky / clouds)
				tiles[i].name == "LayerDecoration" ||	// (fence posts, signs) - no collision
				tiles[i].name == "LayerStatic")			// (platforms)
			{
				SDL_Rect srcRect = { 0, 0, tiles[i].xSize, tiles[i].ySize };
				SDL_Rect destRect = { tiles[i].xPos, tiles[i].yPos, tiles[i].xSize, tiles[i].ySize };

				if (tiles[i].name == "LayerStatic")
				{
					if (tiles[i].tileID == 0) continue; // Without this, we would, eventually, put a collider on every tile. 
					physTiles.push_back(tiles[i]);
				}
				
				SDL_RenderCopy(IonixEngine::Application::Get().GetWindow().m_Renderer, tiles[i].tileTexture, &srcRect, &destRect);
			}
		}
	}

	// So we're not just rendering using SDL - we actually put our texture on an object so it exists in that system
	void CreateLayerObject(const std::string& layerName, SDL_Texture* texture)
	{
		Object* newObject = IonixEngine::Application::Get().layerObject->NewObject(layerName.c_str());

		SDL_SetRenderTarget(IonixEngine::Application::Get().GetWindow().m_Renderer, nullptr);

		std::string fullPath = IonixEngine::EngineSystems::ProjectPath() + "/textures/" + layerName + ".png";

		SpriteComponent* sprite = new SpriteComponent();
		sprite->SetTexture(layerName + ".png");
		int textureSizeX, textureSizeY;
		SDL_QueryTexture(texture, nullptr, nullptr, &textureSizeX, &textureSizeY);
		sprite->SetWidth(textureSizeX);
		sprite->SetHeight(textureSizeY);

		newObject->AddComponent(sprite);
		newObject->SetGameObjectName(layerName.c_str());
		newObject->SetObjectPosition(textureSizeX / 2, textureSizeY / 2);
		
		int zIndex = zLayerPositions[layerName];
		newObject->SetObjectZLayer(zIndex);

		IonixEngine::Application::Get().layerObject->GetScene()->AddObject(newObject);

		if (layerName == "LayerStatic" )
			AddCollisionToTiles();
	}

	void AddCollisionToTiles()
	{
		// Loops through physTiles (populated in ProcessLayer) and adds collision with accurate offsets 
		PhysicsComponent* phys = nullptr;
		for (const auto& tile : physTiles)
		{
			Object* newPhysObject = new Object();

			phys = new PhysicsComponent(tile.xSize, tile.ySize, 0.0, 1.0, 1.0, false, false, true, false);
			newPhysObject->SetObjectPosition(tile.xPos + (tile.xSize / 2), tile.yPos + (tile.ySize / 2));
			newPhysObject->AddComponent(phys);
			IonixEngine::Application::Get().layerObject->GetScene()->AddObject(newPhysObject);
		}
	}
};