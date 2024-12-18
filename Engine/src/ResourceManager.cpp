#include "ResourceManager.h"
#include "Architecture/EngineSystems.h"

ResourceManager::ResourceManager() 
{
	TTF_Init();

	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

SDL_Surface* ResourceManager::GetSurface(const std::string filepath)
{
	//Look through m_surfaces that is a 'unordered_map' and see if a file exists.
	//And if file exists, return associated surface.
	auto search = m_surfaces.find(filepath);
	// File exists in the map
	if (search!= m_surfaces.end())
	{
		// Returns the pointer to the surface
		return search->second;
	}
	else 
	{
		string fullPath = IonixEngine::EngineSystems::ProjectPath();
		fullPath += "/" + filepath;
		// Use IMG_Load to support loading BMP, PNG, JPG, etc.
		SDL_Surface* surface = IMG_Load(fullPath.c_str());

		std::cout << "Image allocated once." << std::endl;
		
		// Checks if the loading was successful (surface contains something)
		if (surface)
		{
			// Sets the key to the surface (key is the filepath)
			m_surfaces[filepath] = surface;
		}
		else
		{
			// Unable to load the image, tell them
			std::cerr << "Failed to load image: " << SDL_GetError() << std::endl;
		}
		return surface;
	}
	return nullptr;
}

Mix_Chunk* ResourceManager::GetAudio(const std::string& filepath) 
{
	auto search = m_audios.find(filepath);
	if (search != m_audios.end()) 
	{
		return search->second;
	}
	else 
	{
		std::cout << "Loading audio: " << filepath << std::endl;
		Mix_Chunk* audio = Mix_LoadWAV(filepath.c_str());
		if (audio)
		{
			m_audios[filepath] = audio;
		}
		else
		{
			std::cerr << "Failed to load audio: " << Mix_GetError() << std::endl;
		}
		return audio;
	}
}

TTF_Font* ResourceManager::GetFont(const std::string& filepath, const int fontSize)
{
	
	auto search = m_fonts.find(filepath);
	// This will fail if the filepath doesn't contain the filetype (.ttf)

	if (search != m_fonts.end())
	{
		return search->second;
	}
	else
	{
		std::cout << "Loading font: " << filepath << std::endl;
		TTF_Font* font = TTF_OpenFont(filepath.c_str(), fontSize);
		if (font)
		{
			m_fonts[filepath] = font;
		}
		else
		{
			std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
		}
		return font;
	}
}

std::vector<SDL_Surface*> ResourceManager::RipToPieces(const std::string filepath, int tileSize)
{
	SDL_Surface* mySurface = GetSurface(filepath);
	if (!mySurface) return {};

	std::vector<SDL_Surface*> surfaces;
	int rows = mySurface->h / tileSize;
	int cols = mySurface->w / tileSize;

	for (int y = 0; y < rows; ++y) {
		for (int x = 0; x < cols; ++x) {
			SDL_Rect srcRect = { x * tileSize, y * tileSize, tileSize, tileSize };
			SDL_Surface* tile = SDL_CreateRGBSurface(0, tileSize, tileSize, mySurface->format->BitsPerPixel,
				mySurface->format->Rmask, mySurface->format->Gmask,
				mySurface->format->Bmask, mySurface->format->Amask);

			SDL_BlitSurface(mySurface, &srcRect, tile, NULL);
			surfaces.push_back(tile);
		}
	}
	SDL_FreeSurface(mySurface);
	return surfaces;
}

void ResourceManager::CreateAndAddTiles(std::string filePath, int tileSize)
{
	vector<SDL_Surface*> tiles = RipToPieces(filePath, tileSize);

	// add entries to map
	for (int i = 0; i < tiles.size(); i++)
	{
		string modifiedPath = filePath + "_tile_" + to_string(i);
		m_surfaces[modifiedPath] = tiles[i];
	}
}
