#include "Graphics.h"
#include "TextureManager.h"
#include <algorithm>
#include "../ResourceManager.h"
#include "../Architecture/Application.h"
#include <string>
#include <Components/SpriteComponent.h>

namespace IonixEngine
{
	SDL_Texture* test = nullptr;
	Camera camera;
	SDL_Surface* surface = nullptr;
	SDL_Event event;
	SDL_Rect clips[4];
	SDL_Rect pSpriteClips[3];
	SDL_Rect* pSprite;
	SDL_Rect pBase;
	SDL_RendererFlip sFlip = SDL_FLIP_NONE;


	Sprite::Sprite(SDL_Renderer* renderer, std::string tex) : texture(tex)
	{
		SDL_Surface* surface = ResourceManager::GetInstance().GetSurface("textures/"+tex);
		width = surface->w;
		height = surface->h;
		sdlTexture = SDL_CreateTextureFromSurface(Application::Get().GetWindow().GetSdlRenderer(), surface);
		opacity = 255.0f; // maybe this should be in SpriteComponent? hl 13/11/24
		//			sdlTexture = IMG_LoadTexture(renderer, fileName.c_str());
	}


	class Button
	{
	private:
		//The attributes of the button
		SDL_Rect box;

		//The part of the button sprite sheet that will be shown
		SDL_Rect* clip;

	public:
		//Initialize the variables
		Button(int x, int y, int w, int h);

		//Handles events and set the button's sprite region
		void handle_events();

		//Shows the button on the screen
		void show();
	};

	Graphics::Graphics(SDL_Renderer* renderer)
	{
		m_renderer = renderer;
		int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
		IMG_Init(imgFlags); // initialize the IMG library for reading texture images

	}

	void Graphics::DrawSprite(Sprite& sprite)
	{
		// draw a sprite:

		// for this need an SDL_Texture (should get this from texture manager) and 
		// then use SDL_RenderCopyEx to draw to the screen

		TextureManager* textureManager = GetTextureManager();
		//SDL_Texture* texture = textureManager->GetSDLTexture(textureName);
		//SDL_Texture* texture = IMG_LoadTexture(m_renderer, "D://GameEngines24-25/TestProjectData/Textures/test_texture.png");
		//Find a different image


		SDL_Rect sprite_rect;
		sprite_rect.x = 0;
		sprite_rect.y = 0;
		sprite_rect.w = sprite.width;
		sprite_rect.h = sprite.height;

		SDL_Rect destination_rect;
		destination_rect.x = sprite.x;
		destination_rect.y = sprite.y;
		destination_rect.w = sprite.width * sprite.scaleX;
		destination_rect.h = sprite.height * sprite.scaleY;

		SDL_SetTextureBlendMode(sprite.sdlTexture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(sprite.sdlTexture, sprite.opacity);
		
		SDL_RenderCopyEx(m_renderer, sprite.sdlTexture, &sprite_rect, &destination_rect, sprite.angle, NULL, SDL_FLIP_NONE);
	}
	void Graphics::TransformSprite(Sprite& sprite, float x, float y, float angle, float scaleX, float scaleY)
	{
		// draw a sprite:

		// for this need an SDL_Texture (should get this from texture manager) and 
		// then use SDL_RenderCopyEx to draw to the screen

		//TextureManager* textureManager = GetTextureManager();
		// SDL_Texture* texture = textureManager->GetSDLTexture(textureName);

		
		angle = angle + sprite.angle;
		SDL_Rect sprite_rect;
		sprite_rect.x = 0;
		sprite_rect.y = 0;
		sprite_rect.w = sprite.width;
		sprite_rect.h = sprite.height;

		SDL_Rect destination_rect;
		destination_rect.x = sprite.x + x;
		destination_rect.y = sprite.y + y;


		if (scaleX != 0)
		{
			destination_rect.w = sprite.width * sprite.scaleX * scaleX;
		}
		else if (scaleX == 0)
		{
			destination_rect.w = sprite.width * sprite.scaleX;
		}

		if (scaleY != 0)
		{
			destination_rect.h = sprite.height * sprite.scaleY * scaleY;
		}
		else if (scaleY == 0)
		{
			destination_rect.h = sprite.height * sprite.scaleY;
		}

		SDL_SetTextureBlendMode(sprite.sdlTexture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(sprite.sdlTexture, sprite.opacity);

		SDL_RenderCopyEx(m_renderer, sprite.sdlTexture, &sprite_rect, &destination_rect, angle, NULL, SDL_FLIP_NONE);
	}

	void Graphics::DrawAnimation(Sprite& sprite, int frames, int framerate)
	{
		//Uint32 ticks = SDL_GetTicks();
		//Uint32 spriteframe = (ticks / (1000 / framerate) % frames);

		//SDL_Rect sprite_rect;
		//sprite_rect.x = (sprite.width / frames) * spriteframe;
		//sprite_rect.y = 0;
		//sprite_rect.w = sprite.width / frames;
		//sprite_rect.h = sprite.height;

		//SDL_Rect destination_rect;
		//destination_rect.x = sprite.x;
		//destination_rect.y = sprite.y;
		//destination_rect.w = (sprite.width / frames )* sprite.scaleX;
		//destination_rect.h = sprite.height * sprite.scaleY;

		//SDL_SetTextureBlendMode(sprite.sdlTexture, SDL_BLENDMODE_BLEND);
		//SDL_SetTextureAlphaMod(sprite.sdlTexture, sprite.opacity);

		//SDL_RenderCopyEx(m_renderer, sprite.sdlTexture, &sprite_rect, &destination_rect, sprite.angle, NULL, SDL_FLIP_NONE);
	}

	SDL_Surface* crop_surface(SDL_Surface* sprite_sheet, int x, int y, int width, int height)
	{
		SDL_Surface* surface = SDL_CreateRGBSurface(sprite_sheet->flags, width, height, sprite_sheet->format->BitsPerPixel, sprite_sheet->format->Rmask, sprite_sheet->format->Gmask, sprite_sheet->format->Bmask, sprite_sheet->format->Amask);
		SDL_Rect rect = { x, y, width, height };
		SDL_BlitSurface(sprite_sheet, &rect, surface, 0);
		return surface;
	}

	void Graphics:: Slice()
	{
		test = IMG_LoadTexture(m_renderer, "D://GameEngines24-25/TestProjectData/Textures/test_texture.png");
		
		if (test == nullptr)
		{
			cout << "Unable to load player Sprite sheet.";
		}

		//facing down sprite
		pSpriteClips[0].x = 14;
		pSpriteClips[0].y = 12;
		pSpriteClips[0].w = 145;
		pSpriteClips[0].h = 320;
		//more code...

		//player sprite
		pBase.x = 0;
		pBase.y = 0;
		pBase.w = pSpriteClips[0].w;
		pBase.h = pSpriteClips[0].h;

		SDL_RenderClear(m_renderer); //clears screen
		SDL_RenderCopyEx(m_renderer, test, pSprite, &pBase, 0.0, NULL, sFlip);
		SDL_RenderPresent(m_renderer); //puts image on screen
		
		/*SDL_Surface*Im = IMG_Load("D://GameEngines24-25/TestProjectData/Textures/test_texture.png");
		int Width = Im->w;
		int Height = Im->h;
		const int Row = 500;
		const int Col = 500;
		SDL_Texture* text = SDL_CreateTextureFromSurface(m_renderer, Im);
		SDL_FreeSurface(Im);
		SDL_Texture* clip[Row][Col];
		for (int i = 0; i < Row; i++)
		{
			for (int j = 0; j < Col; j++)
			{
				clip[i][j] = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Width / Row, Height / Col);
				SDL_SetTextureBlendMode(clip[i][j], SDL_BLENDMODE_BLEND);
				SDL_Rect rect = { i * Width / Row,j * Height /Col, Width / Row, Height / Col };
				SDL_SetRenderTarget(m_renderer, clip[i][j]);
				SDL_RenderCopy(m_renderer, text, &rect, NULL);
			}
		}
		SDL_SetRenderTarget(m_renderer, NULL);
		int x = Row;
		int y = Col;
		SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(m_renderer);
			for (int i = 0; i < Row; i++)
			{
				for (int j = 0; j < Col; j++)
				{
					SDL_Rect rect = { x + i * Width / Row,y + j * Height / Col, Width / Row, Height / Col };
					SDL_RenderCopy(m_renderer, clip[i][j], NULL, &rect);
				}
			}
			SDL_RenderPresent(m_renderer);*/
	}





	void Graphics::AddEntityToSystem(SpriteComponent* sprite)
	{ //sprites is vector to add to
		sprites.push_back(sprite);
	
	}

	std::vector<SpriteComponent*> Graphics::GetSystemEntities() const
	{
		//std::cout <<  << std::endl;
		return sprites;
	}



	void Graphics::StartZSort()
	{
		/*Debugging*/ 
		//std::cout << "Number of objects in list: " << objectList.size() << std::endl;
		
		sprites.clear();


		//Graphics::AddEntityToSystem(sprite);

		//std::cout << GetSystemEntities() << std::endl;
	}

	
	void Graphics::FinishZSort()
	{//sort the objectList
		// sort objectList by depth
		
		struct RenderableEntity
		{ //this groups the sprite and transform component together as we want to sort them together
			TransformComponent transformComponent;
			SpriteComponent* spriteComponent;
		};
		std::vector<RenderableEntity> renderableEntities; //new vector list
		//std::cout << "reached for loop" << std::endl;
		for (auto entity : GetSystemEntities()) //for each entity in systemEntities
		{
			RenderableEntity renderableEntity; 
			renderableEntity.spriteComponent = entity; 
			renderableEntities.emplace_back(renderableEntity);
			//std::cout << "added entity to vector" << std::endl;
		}
	
		sort
		(
			renderableEntities.begin(),
			renderableEntities.end(),
			[](const RenderableEntity& a, const RenderableEntity& b)
			{
				return a.spriteComponent->GetZIndex() > b.spriteComponent->GetZIndex();
			}
		);
		
		//display the sorted entities
		for (auto entity : renderableEntities)
		{
			entity.spriteComponent->OnRenderEx(); //OnRender() is the exact same as OnRenderEx();
		}
		

	}


	void Graphics::StartRender()
	{

		SDL_RenderClear(m_renderer);

		//TestGraphics();
		//Slice();
		/*SDL_RenderClear(IonixEngine::Application::Get().GetWindow().m_Renderer);
		SDL_SetRenderDrawColor(IonixEngine::Application::Get().GetWindow().m_Renderer, rand() % 255, rand() % 200, rand() % 100, rand() % 50);
		SDL_RenderFillRect(IonixEngine::Application::Get().GetWindow().m_Renderer, NULL);
		SDL_RenderDrawRect(IonixEngine::Application::Get().GetWindow().m_Renderer, NULL);
		SDL_RenderCopy(IonixEngine::Application::Get().GetWindow().m_Renderer, test, NULL, NULL);
		test = IMG_LoadTexture(IonixEngine::Application::Get().GetWindow().m_Renderer, "D:/GameEngines24-25/TestProjectData/Textures/Rock.png");
		SDL_RenderCopy(IonixEngine::Application::Get().GetWindow().m_Renderer, test, NULL, NULL);*/
		

	}

	void Graphics::TestGraphics()
	{
		//Sprite mySprite2(m_renderer, "test_texture.png", 100, 100, 500, 500, 0, 1, 1, 255);
		Sprite mySprite(m_renderer, "sdl2-spritesheet-actual2.png");// , 100, 100, 300, 128, 0, 7, 7, 255, 0); H
		// 
	    //TransformSprite(mySprite, -50, 0, 0, 0, 0);

		/*
		vector<Sprite*> objectList;
		
		for (auto sprite : objectList)
		{
			Sprite spriteEntity;
			objectList.push_back(sprite);
			spriteEntity.emplace_back(spriteEntity);
			/*
			struct RenderableEntity
			{ 
				TransformComponent transformComponent;
				SpriteComponent spriteComponent;
			};
			std::vector<RenderableEntity> renderableEntities;
			
			RenderableEntity renderableEntity;
			renderableEntity.spriteComponent = sprite.GetComponent<SpriteComponent>();
			renderableEntity.transformComponent = sprite.GetComponent<TransformComponent>();
			renderableEntities.emplace_back(renderableEntity);
			
		}
		sort
		(
			objectList.begin(),
			objectList.end(),
			[](const sprite& a, const sprite& b)
			{
				return a.spriteComponent.zIndex < b.spriteComponent.zIndex;
			}
			);
		*/
		SpriteComponent* sComponent = new SpriteComponent();

	
		sComponent->SetSprite(mySprite);
		sComponent->SetAnimationFrames(5);
		sComponent->SetAnimationRows(2);
		sComponent->SetCurrentAnimationRow(2);
		sComponent->SetAnimationSpeed(3.0f);
		sComponent->OnUpdate(1.0f);
		sComponent->OnRender();
		sComponent->OnUpdate(1.0f);
	}

	void Graphics::FinishRender()
	{
		SDL_RenderPresent(m_renderer);
	}

	TextureManager* Graphics::GetTextureManager()
	{
		return textures;
	}


	

#ifdef Test_Graphics
	void Graphics::animationWorks()
	{
		SpriteComponent* SC = new SpriteComponent();
		Sprite myS(m_renderer, "sdl2-spritesheet-actual2.png", 100, 100, 300, 128, 0, 7, 7, 255);
		vector<Entities> entities;
		
//		vector<string> entities;
		//
		Sprite mySprite(m_renderer, "sdl2-spritesheet-actual2.png", 100, 100, 300, 128, 0, 7, 7, 255, 0);
	    //TransformSprite(mySprite, -50, 0, 0, 0, 0);
		//entities.push_back(mySprite);
	
		//SC->SetSprite(myS);
		//SC->SetAnimationFrames(5);
		//SC->SetAnimationRows(2);
		//SC->SetCurrentAnimationRow(2);
		//SC->SetAnimationSpeed(3.0f);
		//SC->OnUpdate(1.0f);
		//SC->OnRender();

	}

	

	void Graphics::depthSortingWorks()
	{
		/*
		//Create vector with both sprite and transform component of all entities
		struct RenderableEntity
		{ //this groups the sprite and transform component together as we want to sort them together
			TransformComponent transformComponent;
			SpriteComponent spriteComponent;
		};
		std::vector<RenderableEntity> renderableEntities;
		for (auto entity : ())
		{
			RenderableEntity renderableEntity;
			renderableEntity.spriteComponent = entity.spriteComponent();
			renderableEntity.transformComponent = entity.TransformComponent();
			renderableEntities.emplace_back(renderableEntity);
		}

		//Sort the vector by z-index
		sort
		(
			renderableEntities.begin(), 
			renderableEntities.end(), 
			[](const RenderableEntity& a, const RenderableEntity& b)
			{
				return a.spriteComponent.zIndex < b.spriteComponent.zIndex;
			}
		);
		*/
	}

	void Graphics::spriteEditorWorks()
	{

	}

#endif //Test_Graphics


}

