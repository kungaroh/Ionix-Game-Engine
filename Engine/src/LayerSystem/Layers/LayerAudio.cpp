#pragma once
#include "EventSystem/Event.h"
#include "../src/Architecture/Application.h"
#include "LayerAudio.h"
#include "LayerSystem/Layers/LayerAudio.h"

namespace IonixEngine
{
	void LayerAudio::OnAttach() 
	{ 
		m_audio = new Audio();
	}

	void LayerAudio::OnDetach() { }

	void LayerAudio::OnUpdate(float deltaTime) 
	{
		
	}

	void LayerAudio::OnLoaded()
	{

	}

    void LayerAudio::OnEvent(IonixEvent& e)
    {
		EventDispatcher dispatcher(e);
		
		dispatcher.Dispatch<Event_WindowClosed>(std::bind(&LayerAudio::OnWindowClosedEvent, this, std::placeholders::_1));
    }

	bool LayerAudio::OnWindowClosedEvent(Event_WindowClosed& e)
	{
		Console::info("IonixEvent: Window close");
		Application::Get().m_Running = false;
		return true;
	}


	Mix_Chunk* LayerAudio::LoadWAV(const char* musicFile) {
		return m_audio->LoadWAV(musicFile);
	}
	
	void LayerAudio::PlayAudio(Mix_Chunk* chunk, int loops) {
		m_audio->PlayAudio(chunk, loops);
	}

	void LayerAudio::PauseAudio(Mix_Chunk* chunk) {
		m_audio->PauseAudio(chunk);
	}	
	
	void LayerAudio::PauseAllAudio() {
		m_audio->PauseAllAudio();
	}

	void LayerAudio::ResumeAudio(Mix_Chunk* chunk) {
		m_audio->ResumeAudio(chunk);
	}

	void LayerAudio::ClearChannel(Mix_Chunk* chunk) {
		m_audio->ClearChannel(chunk);
	}

	void LayerAudio::ClearAllChannels(){
		m_audio->ClearAllChannels();
	}

	void LayerAudio::SetVolume(int vol, Mix_Chunk* chunk) {
		m_audio->SetVolume(vol, chunk);
	}

	void LayerAudio::FadeIn(int ms, Mix_Chunk* chunk, int loops) {
		m_audio->FadeIn(ms, chunk, loops);
	}

	void LayerAudio::FadeOut(int ms, Mix_Chunk* chunk) {
		m_audio->FadeOut(ms, chunk);
	}

	void LayerAudio::TimedPlay(Mix_Chunk* chunk, float interval) {
		m_audio->TimedPlay(chunk, interval);
	}

	void LayerAudio::RandomTimedPlay(Mix_Chunk* chunk, int min, int max) {
		m_audio->RandomTimedPlay(chunk, min, max);
	}

	uint32_t LayerAudio::PlayAudio(const char* fileName, int loops)
	{
		uint32_t thisHandle = soundHandle++;
		// play the sound
		Mix_Chunk* chunk = LoadWAV(fileName);

		handleMap[thisHandle] = chunk;
		m_audio->PlayAudio(chunk, loops);
		return thisHandle;
	}

	void LayerAudio::PauseAudio(uint32_t handle)
	{
		// check handle is valid
		if (handleMap.find(handle) == handleMap.end())
		{
			// no such handle
			std::cout << "Handle not found" << std::endl;
			return;
		}
		m_audio->PauseAudio(handleMap[handle]);
	}
	void LayerAudio::ResumeAudio(uint32_t handle)
	{
		if (handleMap.find(handle) == handleMap.end())
		{
			// no such handle
			std::cout << "Handle not found" << std::endl;
			return;
		}
		m_audio->ResumeAudio(handleMap[handle]);
	}

	void LayerAudio::ClearChannel(uint32_t handle)
	{
		if (handleMap.find(handle) == handleMap.end())
		{
			// no such handle
			std::cout << "Handle not found" << std::endl;
			return;
		}
		m_audio->ClearChannel(handleMap[handle]);
	}

	void LayerAudio::SetVolume(int vol, uint32_t handle)
	{
		if (handleMap.find(handle) == handleMap.end())
		{
			// no such handle
			std::cout << "Handle not found" << std::endl;
			return;
		}
		m_audio->SetVolume(vol, handleMap[handle]);
	}

	void LayerAudio::FadeIn(int ms, uint32_t handle, int loops)
	{
		if (handleMap.find(handle) == handleMap.end())
		{
			// no such handle
			std::cout << "Handle not found" << std::endl;
			return;
		}
		m_audio->FadeIn(ms, handleMap[handle], loops);
	}

	void LayerAudio::FadeOut(int ms, uint32_t handle)
	{
		if (handleMap.find(handle) == handleMap.end())
		{
			// no such handle
			std::cout << "Handle not found" << std::endl;
			return;
		}
		m_audio->FadeOut(ms, handleMap[handle]);
	}

	void LayerAudio::TimedPlay(uint32_t handle, float interval)
	{
		if (handleMap.find(handle) == handleMap.end())
		{
			// no such handle
			std::cout << "Handle not found" << std::endl;
			return;
		}
		m_audio->TimedPlay(handleMap[handle], interval);
	}

	void LayerAudio::RandomTimedPlay(uint32_t handle, int min, int max)
	{
		if (handleMap.find(handle) == handleMap.end())
		{
			// no such handle
			std::cout << "Handle not found" << std::endl;
			return;
		}
		m_audio->RandomTimedPlay(handleMap[handle], min, max);
	}
}