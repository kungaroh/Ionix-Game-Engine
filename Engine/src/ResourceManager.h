#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <string>
#include <iostream>
#include <unordered_map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <filesystem>
#include<vector>
#include "Architecture/EngineSystems.h"

// Is this needed?
//Third Party Library 
//#include<SDL2-2.30.6/SDL.h>

class ResourceManager {
		private:
			ResourceManager();
			~ResourceManager() {};

			std::unordered_map<std::string, SDL_Surface*> m_surfaces;
			std::unordered_map<std::string, Mix_Chunk*> m_audios;
			std::unordered_map<std::string, TTF_Font*> m_fonts;
			std::unordered_map<std::string, TTF_Font*> m_riptopieces;

		public:
			static ResourceManager& GetInstance() 
			{
				static ResourceManager instance;
				return instance;
			}

			SDL_Surface* ResourceManager::GetSurface(const std::string filepath);
			Mix_Chunk* ResourceManager::GetAudio(const std::string& filepath);
			TTF_Font* ResourceManager::GetFont(const std::string& filepath, const int fontSize);
			std::vector<SDL_Surface*> ResourceManager::RipToPieces(const std::string filepath, int tileSize=32);

			const std::filesystem::path filepath = std::filesystem::current_path();
			const std::string t = filepath.string();
			
			
			std::string AUDIO_PATH = IonixEngine::EngineSystems::ProjectPath() + "/Audio/";
			std::string TEXTURE_PATH = IonixEngine::EngineSystems::ProjectPath() + "/Textures/";
			std::string FONT_PATH = IonixEngine::EngineSystems::ProjectPath() + "/Fonts/";
			std::string EDITOR_PATH = IonixEngine::EngineSystems::ProjectPath() + "/Editor/";
			
			

			void SetPath( std::string basePath)
			{
				AUDIO_PATH = basePath + "/Audio/";
				TEXTURE_PATH = basePath + "/Textures/";
				FONT_PATH = basePath + "/Fonts/";
			}
			void CreateAndAddTiles(string filePath, int tileSize=32);
;			//USE THESE FOR THE CLIENT IN THE BIN, HARDCODED DIRECTORY, MEANING THAT IT WILL NOT WORK WHEN RUNNING IN IDE.
			
			//const std::string AUDIO_PATH = std::filesystem::current_path().string().replace(std::filesystem::current_path().string().find("bin"), 31, "TestProjectData\Audio");
			//const std::string TEXTURE_PATH = std::filesystem::current_path().string().replace(std::filesystem::current_path().string().find("bin"), 31, "TestProjectData\Textures");
			//const std::string FONT_PATH = std::filesystem::current_path().string().replace(std::filesystem::current_path().string().find("bin"), 31, "TestProjectData\Fonts");


};

#endif