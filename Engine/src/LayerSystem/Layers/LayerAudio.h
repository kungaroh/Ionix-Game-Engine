#pragma once
#include "LayerSystem/Layer.h"
#include "EventSystem/Event.h"
#include "Audio/Audio.h"
#include <string>
#include <unordered_map>

namespace IonixEngine
{
	class LayerAudio : public Layer
	{
	public:
		LayerAudio(int id) : Layer(id)
		{
		}

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnLoaded() override;
		void OnUpdate(float deltaTime);
		virtual void OnEvent(IonixEvent& e) override;
		Mix_Chunk* LoadWAV(const char* musicFile);
		void PlayAudio(Mix_Chunk* chunk, int loops);
		void PauseAudio(Mix_Chunk* chunk);
		void PauseAllAudio();
		void ResumeAudio(Mix_Chunk* chunk);
		void ClearChannel(Mix_Chunk* chunk); // added
		void ClearAllChannels();
		void SetVolume(int vol, Mix_Chunk* chunk);
		void FadeIn(int ms, Mix_Chunk* chunk, int loops);
		void FadeOut(int ms, Mix_Chunk* chunk);
		void TimedPlay(Mix_Chunk* chunk, float interval);
		void RandomTimedPlay(Mix_Chunk* chunk, int min, int max);

		uint32_t PlayAudio(const char* fileName, int loops); // play sound from file, return sound handle
		void PauseAudio(uint32_t handle);
		void ResumeAudio(uint32_t handle);
		void ClearChannel(uint32_t handle);
		void SetVolume(int vol, uint32_t handle);
		void FadeIn(int ms, uint32_t handle, int loops);
		void FadeOut(int ms, uint32_t handle);
		void TimedPlay(uint32_t handle, float interval);
		void RandomTimedPlay(uint32_t handle, int min, int max);

	private:
		uint32_t soundHandle = 0;
		unordered_map<uint32_t, Mix_Chunk*> handleMap;
		Audio* m_audio;
		bool OnWindowClosedEvent(Event_WindowClosed& e);
	};
}