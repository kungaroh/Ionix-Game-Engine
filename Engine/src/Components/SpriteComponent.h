#pragma once 
#include "Component.h"
#include "../Architecture/EngineSystems.h"
#include "TransformComponent.h"
#include <string>
#include <graphics/Graphics.h>
#include <string>
#include <iostream>
#include "Architecture/Application.h"
using namespace std;


// example component

struct SpriteComponent : public Component
{
	string textureName;
	float w; // width
	float h; // height
	TransformComponent* transform;
	IonixEngine::Sprite newSprite;
	int animationFrames = -1; // -1 means no animation, otherwise it is the number of animation frames
	int animationRows = 1; 
	int currentAnimationRow = 1;
	float animationSpeed = 0.0f;
	SDL_Renderer* m_renderer;
	int currentFrame = 0; 
	float accumulatedTime = 0.0f;
	SDL_Rect sourceRect;
	SDL_Rect destRect;
	float deltaTime;
	int zIndex;
public:
	//renderer, text, positionX, positionY, width, height, rotation, sX, sY, opacity, zIndex
	//SpriteComponent(SDL_Renderer& m_renderer, std::string assetId = "", int positionX = 0, int positionY = 0, float width = 0, float height = 0, float rotation = 0, float sX = 0, float sY = 0, float opacity = 0, int zIndex) : Component("Sprite")
	SpriteComponent() : Component("Sprite")
	{
	}



	IonixEngine::Sprite GetSprite() { return newSprite;  }
	void SetSprite(IonixEngine::Sprite sprite) { newSprite = sprite; }

	virtual ~SpriteComponent() {}

	virtual void OnStart()
	{
		// get the a pointer to the transform from the parent object
		transform = m_owner->GetComponentOfType<TransformComponent>();
		if (textureName.empty())
		{
			return;
		}
		newSprite = IonixEngine::Sprite(m_renderer, textureName);
	}
	virtual void OnUpdate(float deltaTime)
	{
		//IonixEngine::Application::Get().GetGraphics()->DrawAnimation(newSprite, 4, 10);
		// update animation - use the code from DrawAnimation to update the sprite (newSprite)
		//Set everything into newSprite fron sprite rec & destination rect

		/*SDL_Rect sourceRect = {(newSprite.width / animationFrames) * animationSpeed, 0, newSprite.width / animationFrames, newSprite.height};

		SDL_Rect destRect = { newSprite.x, newSprite.y, (newSprite.width / animationFrames) * newSprite.scaleX, newSprite.height * newSprite.scaleY};

		SDL_SetTextureBlendMode(newSprite.sdlTexture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(newSprite.sdlTexture, newSprite.opacity);
		SDL_RenderCopyEx(IonixEngine::Application::Get().GetWindow().m_Renderer, newSprite.sdlTexture, &sourceRect/*&sprite_rect*//*, & destRect/*&destination_rect*//*, newSprite.angle, nullptr, SDL_FLIP_NONE);*/
		newSprite.x = transform->x;
		newSprite.y = transform->y;
		zIndex = transform->z;
		const IonixEngine::Camera& cam = (IonixEngine::Application::Get().layerGraphics)->GetGraphics()->GetCamera();
		
		// assumption is that the sub-sprites in an animation are square
		// an animation occupies one row of the texture but doesn't have to fill it
		// the rows are numbered from the top down, zero based.
		// assume speed is in frames per second
		accumulatedTime += deltaTime;

		if (animationFrames > 0)
		{
			int size = (newSprite.height / animationRows); // assume square

			currentFrame = ((int)(accumulatedTime * animationSpeed)) % animationFrames;

			newSprite.sourceRect.x = size * currentFrame;
			newSprite.sourceRect.y = size * currentAnimationRow;
			newSprite.sourceRect.w = size;
			newSprite.sourceRect.h = size;
		}
		else
		{
			newSprite.sourceRect.x = 0;
			newSprite.sourceRect.y = 0;
			newSprite.sourceRect.w = newSprite.width;
			newSprite.sourceRect.h = newSprite.height;

		}
		// pivot is centre of sprite - consistent with physics
		newSprite.destRect.x = static_cast<int>(newSprite.x - cam.x - w * transform->sx/2);
		newSprite.destRect.y = static_cast<int>(newSprite.y - cam.y - h * transform->sy/2);
		newSprite.destRect.w = static_cast<int>(w * transform->sx);
		newSprite.destRect.h = static_cast<int>(h * transform->sy);
	}
	
	virtual void OnRenderEx()
	{
		SDL_SetTextureBlendMode(newSprite.sdlTexture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(newSprite.sdlTexture, newSprite.opacity);
		SDL_RenderCopyEx(IonixEngine::Application::Get().GetWindow().m_Renderer, newSprite.sdlTexture, &newSprite.sourceRect, &newSprite.destRect, transform->angle, nullptr, SDL_FLIP_NONE);

		/*
		vector systemEnts = IonixEngine::Application::Get().layerGraphics->GetGraphics()->GetSystemEntities();
		//systemEnts* = 
		for (auto entity : systemEnts)
		{
			if (entity->zIndex < 1)
			{
				SDL_RenderCopyEx(IonixEngine::Application::Get().GetWindow().m_Renderer, newSprite.sdlTexture, &newSprite.sourceRect, &newSprite.destRect, transform->angle, nullptr, SDL_FLIP_HORIZONTAL);
			}
			else
			{
				SDL_RenderCopyEx(IonixEngine::Application::Get().GetWindow().m_Renderer, newSprite.sdlTexture, &newSprite.sourceRect, &newSprite.destRect, transform->angle, nullptr, SDL_FLIP_NONE);
			}
		}
		*/
		
		/*
		if ( 1)
		{
			SDL_RenderCopyEx(IonixEngine::Application::Get().GetWindow().m_Renderer, newSprite.sdlTexture, &newSprite.sourceRect, &newSprite.destRect, transform->angle, nullptr, SDL_FLIP_HORIZONTAL);

		}
		else 
		{
			SDL_RenderCopyEx(IonixEngine::Application::Get().GetWindow().m_Renderer, newSprite.sdlTexture, &newSprite.sourceRect, &newSprite.destRect, transform->angle, nullptr, SDL_FLIP_NONE);
		}
		*/

	}
	virtual void OnRender()
	{
		IonixEngine::Application::Get().layerGraphics->GetGraphics()->AddEntityToSystem(this);
	}

	void SetTexture(string texture) { textureName = texture; }
	void SetWidth(float nw) { w = nw; }
	void SetHeight(float nh) { h = nh;  }
	void SetAnimationFrames(int nFrames) { animationFrames = nFrames; }
	void SetAnimationRows(int nRows) { animationRows = nRows; }
	void SetCurrentAnimationRow(int nRow) { currentAnimationRow = nRow; }

	const string GetTexture() const { return textureName; }
	const float GetWidth() const { return w; }
	const float GetHeight()const { return h; }
	int GetZIndex() const { return zIndex; }
	void SetAnimationSpeed(float newSpeed) { animationSpeed = newSpeed; }
	void UpdateTexture(string newTextureName) { textureName = newTextureName; OnStart(); }
};