#pragma once
#include <SDL.h>
//#define STB_IMAGE_IMPLEMENTATION
#include <SDL_image.h>
#include "../Window/Window.h"
#include "../Architecture/EngineSystems.h"
#include <iostream>
#include <string>
//#define Test_Graphics

using namespace std;

class SpriteComponent;

namespace IonixEngine
{
	class TextureManager; // forward declaration, avoiding circular include
	struct Camera
	{
		float x, y;

		Camera(float posX = 0.0f, float posY = 0.0f) : x(posX), y(posY)
		{

		}
	};

	struct Sprite 
	{
		SDL_Texture* sdlTexture;
		std::string texture;
		float x, y; 
		float width, height; 
		float angle; 
		float scaleX, scaleY;
		float opacity;
		float zIndex;
		SDL_Rect sourceRect;
		SDL_Rect destRect;

		Sprite() {}
		//Sprite(SDL_Renderer* renderer, std::string tex, float posX, float posY, float w, float h, float rotation, float sX, float sY, float op, int zIndex);
		// HL 13/11/24 - only pass the renderer and texture. The texture width and height can be determined from the texture, and everything else can live in the sprite component
		Sprite(SDL_Renderer* renderer, std::string tex);
	};



		class Graphics
		{
			SDL_Renderer* m_renderer;
			TextureManager* textures;
			Camera camera;
			std::vector<SpriteComponent*> sprites;
		public:
			Graphics(SDL_Renderer* renderer);

			SDL_Renderer* GetRenderer() const { return m_renderer; }
			void SetRenderer(SDL_Renderer* renderer) { m_renderer = renderer; }

			void DrawSprite(Sprite& sprite);
			void TransformSprite(Sprite& sprite, float x, float y, float angle, float scaleX, float scaleY);
			void DrawAnimation(Sprite& sprite, int frames, int framerate);
			void Slice();
			void StartRender();
			void FinishRender();
			void StartZSort();
			void FinishZSort();
			void TestGraphics();
			TextureManager* GetTextureManager();

			Camera& GetCamera() { return camera; }
			void AddEntityToSystem(SpriteComponent* sprite);
			std::vector<SpriteComponent*> GetSystemEntities() const;
			vector<Sprite*> objectList;

#ifdef Test_Graphics
			void animationWorks();
			void spriteEditorWorks();
			void depthSortingWorks();

			void TestGraphic()
			{
				SDL_Texture* test;
				float i;
				i = rand() % 255;
				float j;
				j = rand() % 200;
				float k;
				j = rand() % 100;
				float l;
				j = rand() % 50;

				//Windows Related
				SDL_RenderClear(m_renderer);
				SDL_SetRenderDrawColor(m_renderer, i, j, k, l);
				SDL_RenderFillRect(m_renderer, NULL);
				SDL_RenderDrawRect(m_renderer, NULL);
				test = IMG_LoadTexture(m_renderer,"D:/GameEngines24-25/TestProjectData/Textures/Rock.png");
				SDL_RenderCopy(m_renderer, test, NULL, NULL);
			}

#endif // Test_Graphics

		};

	}