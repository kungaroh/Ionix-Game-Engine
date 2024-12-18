#pragma once
#include "EventSystem/Event.h"
#include "../src/Architecture/Application.h"
#include "LayerEditor.h"
#include "LayerSystem/Layers/LayerEditor.h"
#include "LayerSystem/Layers/LayerObject.h"
#include "Editorinterpreter/Tile.h"
#include "Components/SpriteComponent.h"
#include "Editorinterpreter/TileCutter.h"
#include "Editorinterpreter/TileMapObjects.h"
#include "Editorinterpreter/EditorInterpreter.h"

static string ToLower(string s)
{
	string retVal = s;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			retVal[i] = s[i] + 'a' - 'A';
	}
	return retVal;
}

namespace IonixEngine
{
	void LayerObject::OnAttach() 
	{
		m_objects = new Scene();
	}

	void LayerObject::OnDetach() 
	{ 
		// On Detach
	}

	void LayerObject::OnLoaded()
	{

	}

	void LayerObject::OnUpdate(float deltaTime) 
	{ 
		m_objects->OnUpdate(deltaTime);
	}

	void LayerObject::OnRender() 
	{
		m_objects->OnRender();
	}

	void LayerObject::SetCurScene(Scene curScene) 
	{ 
		// Set Current Scene
	}


	// Probably move to TileMapObjects.h, ideally
	void LayerObject::CreateTilemapLayerObject(TiledData tiledData, EditorInterpreter& ei)
	{		
		TileCutter tCutter;
		TileMapObjects tMapObjects;

		// Stores how many tile maps are being used in the current game
		int tileDataSize = IonixEngine::Application::Get().layerScripting->GetScripting()->GetTiledData().tiledLayers.size();
		
		// Accesses each of these tile maps
		for (int i = 0; i < tileDataSize; i++)
		{
			if (tiledData.tiledLayers[i].name == "ObjectLayer") 
				continue;

			// Creates an SDL_Texture* 
			// Accesses TileCutter::CreateTexture(TiledData), which initialises the
			// SDL_Texture* with the same dimensions as the .png we are accessing.
			SDL_Texture* compositeTexture = tCutter.CreateTexture(tiledData);
			if (compositeTexture == nullptr)
				continue;

			// Make this new SDL_Texure be he thing we are rendering to
			SDL_SetRenderTarget(Application::Get().GetWindow().m_Renderer, compositeTexture);
			SDL_SetTextureBlendMode(compositeTexture, SDL_BLENDMODE_NONE);

			// Important - without this, all layers will be rendered to a single .png
			// Clears the renderer ready for the next layyer to be processed
			SDL_SetRenderDrawColor(Application::Get().GetWindow().m_Renderer, 0, 0, 0, 0);
			SDL_RenderClear(Application::Get().GetWindow().m_Renderer);

			// Steps into each layer's positional data (gid table, if you like).
			// We pass our newly defined (above) SDL_Texture* so we can create the texture using
			// our lookup map in EditorInterpreter (<int, SDL_Texture*> tiledTextures) 
			// NOTE: This does not handle any object data, such as coins or balls (in our case)
			tMapObjects.ProcessLayer(ei.tiles[i], compositeTexture);

			// Save the texture as a .png as we are going to load this momentarily and render it using the
			// object system
			tCutter.SaveTextureAsPNG(Application::Get().GetWindow().m_Renderer, compositeTexture, tiledData.tiledLayers[i].name);
			
			// Creates an object for each layer (does not handle objects - this is handled by LayerObject::CreateTiledObjects
			tMapObjects.CreateLayerObject(tiledData.tiledLayers[i].name, compositeTexture);

			// Cleanup
			SDL_DestroyTexture(compositeTexture);
		}
	}

	void LayerObject::AddScriptsToObjects(TiledData data) {
		for (const auto& layer : data.tiledLayers) {
			if (layer.tiledObjects.empty()) continue;

			for (const auto& tile : layer.tiledObjects) {
				Object* newObj = Application::Get().layerObject->NewObject(tile.name);

				float width = tile.width;
				float height = tile.height;
				float pwidth = width;
				float pheight = height;
				float restitution = 0.5f;
				float friction = 0.1f;
				float density = 1.0f;
				bool isStatic = false;
				bool isTrigger = false;
				bool isKinematic = false;
				bool lockRotation = false;
				bool requiresPhysics = true;
				bool customPng = true;
				vector<ScriptComponent*> scriptsToAdd;

				for (const auto& [key, value] : tile.properties) {  // Use tile.properties directly

					string k = ToLower(key);

					if (k == "togglephysicsoff")
						requiresPhysics = (value != "true");
					else if (k == "restitution")
						restitution = std::stof(value);
					else if (k == "friction")
						friction = std::stof(value);
					else if (k == "density")
						density = std::stof(value);
					else if (k == "isstatic")
						isStatic = (value == "true");
					else if (k == "istrigger")
						isTrigger = (value == "true");
					else if (k == "iskinematic")
						isKinematic = (value == "true");
					else if (k.find("scriptcomponent") != string::npos)
						scriptsToAdd.push_back(new ScriptComponent(value));

					else if (k == "spritecomponent") {
						std::string fullPath = IonixEngine::EngineSystems::ProjectPath() + "/textures/" + tile.name + ".png";
						//SDL_Surface* tempSurface = ResourceManager::GetInstance().GetSurface(ResourceManager::GetInstance().EDITOR_PATH + value + ".png");
						auto* newSpr = new SpriteComponent();
						newSpr->SetTexture(value + ".png");
						newSpr->SetHeight(tile.height);
						newSpr->SetWidth(tile.width);
						newObj->AddComponent(newSpr);
						customPng = false;
					}
					else if (k == "tag")
						newObj->SetTag(value);

					else if (k == "lockrotation")
						lockRotation = (value == "true");
					else if (k == "colliderwidth")
						pwidth = std::stof(value);
					else if (k == "colliderheight")
						pheight = std::stof(value);
				}

				if (customPng)
				{
					std::string fullPath = IonixEngine::EngineSystems::ProjectPath() + "/textures/" + tile.name + ".png";
					auto* newSpr = new SpriteComponent();
					newSpr->SetTexture(std::string(tile.name) + ".png");
					newSpr->SetHeight(tile.height);
					newSpr->SetWidth(tile.width);
					newObj->AddComponent(newSpr);
					customPng = true;
				}

				if (requiresPhysics) {
					PhysicsComponent* phys = new PhysicsComponent(pwidth, pheight, restitution,
						friction, density, isStatic, isTrigger, isKinematic, lockRotation);
					newObj->AddComponent(phys);
				}

				for(auto s : scriptsToAdd)
				{
					newObj->AddComponent(s);
				}

				newObj->SetObjectPosition(tile.x, tile.y);

				// Place objects on same layer as s
				newObj->SetObjectZLayer(zLayerPositions[layer.name]);

				Application::Get().layerObject->GetScene()->AddObject(newObj);
			}
		}
	}

	// Last method to be called. This is the method which leverages object data.
	// Previously, object data had not been proccess.
	// this is now handled in EditorInterpreter::GenerateEngineTileData

	// This method leverages this processed data
	void LayerObject::CreateTiledObjects(TiledData tiledData, EditorInterpreter& ei)
	{
		// Loops over the object data
		for (int i = 0; i < ei.objectTiles.size(); i++)
		{
			//Object* object = NewObject(ei.objectTiles[i].name.c_str());
			//object->SetObjectPosition(ei.objectTiles[i].xPos, ei.objectTiles[i].yPos);
				
			TileCutter tc;

			SDL_Texture* texture = ei.tileMapTextures[ei.objectTiles[i].tileID];
				
			SDL_SetRenderTarget(Application::Get().GetWindow().m_Renderer, texture);
			SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);

			// Important - without this, all layers will be rendered to a single .png
			// Clears the renderer ready for the next layyer to be processed
			SDL_SetRenderDrawColor(Application::Get().GetWindow().m_Renderer, 0, 0, 0, 0);
			SDL_RenderClear(Application::Get().GetWindow().m_Renderer);

			// object system
			tc.SaveTextureAsPNG(Application::Get().GetWindow().m_Renderer, texture, ei.objectTiles[i].name);
				
			SDL_SetRenderTarget(Application::Get().GetWindow().m_Renderer, nullptr);			
		}

		AddScriptsToObjects(tiledData);
	}


	Object* LayerObject::NewObject(const char* name) // returns UID of newly created object
	{
		Object* obj = new Object();
		obj->SetGameObjectName(name);
		//m_objects->AddObject(obj);	 	
		return obj;

	}

	Object* LayerObject::GetObject(uint32_t i) 
{
		return m_objects->GetObject(i);
	}

	Object* LayerObject::GetObject(const char* i)
	{
		return m_objects->GetObjectByUID(m_objects->GetUIDByName(i));
	}

	Scene* LayerObject::GetScene()
	{
		return m_objects;
	}


    void LayerObject::OnEvent(IonixEvent& e)
    {
		EventDispatcher dispatcher(e);
		
		dispatcher.Dispatch<Event_WindowClosed>(std::bind(&LayerObject::OnWindowClosedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<Event_OnTileMapDataLoaded>(std::bind(&LayerObject::OnTileMapDataLoaded, this, std::placeholders::_1));
    }

	bool LayerObject::OnWindowClosedEvent(Event_WindowClosed& e)
	{
		Console::info("IonixEvent: Window close");
		Application::Get().m_Running = false;
		return true;
	}

	bool LayerObject::OnTileMapDataLoaded(Event_OnTileMapDataLoaded& e)
	{	
		EditorInterpreter* ei = new EditorInterpreter();
		ei->GenerateEngineTileData(e.GetTileMapData());

		LayerObject::CreateTilemapLayerObject(e.GetTileMapData(), *ei);

		LayerObject::CreateTiledObjects(e.GetTileMapData(), *ei);

		Console::info("Lua Map Data Loaded");
		return false;
	}
}

