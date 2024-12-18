#pragma once
#include <SDL.h>
#include "../SDL/SDL2_mixer-2.8.0/include/SDL_mixer.h"
#include <chrono>
#include <unordered_map>

namespace IonixEngine
{
    
    class Audio
    {

    public:
        Audio() 
        {
            channelStates.insert(std::pair<int, bool>(1, false));
            srand(time(NULL));
        }

        Mix_Chunk* LoadWAV(const char* fileName); 
        void PlayAudio(Mix_Chunk* chunk, int loops);
        void PauseAudio(Mix_Chunk* chunk);
        void PauseAllAudio(); //added
        void ResumeAudio(Mix_Chunk* chunk);
        void ClearChannel(Mix_Chunk* chunk);
        void ClearAllChannels();
        void SetVolume(int volume, Mix_Chunk* chunk);
        void FadeIn(int ms, Mix_Chunk* chunk, int loops); 
        void FadeOut(int ms, Mix_Chunk* chunk);
        void TimedPlay(Mix_Chunk* chunk, float interval);
        void RandomTimedPlay(Mix_Chunk* chunk, int min, int max);

    private:
        const char* musicFile = "D://GameEngines24-25//TestProjectData//Audio//Music.WAV";
        double initialTime = double(SDL_GetPerformanceCounter()/SDL_GetPerformanceFrequency());
        double randomInitialTime = double(SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency());
        int randomInterval;
        bool randomNumGenerated = false;
        bool checking = true;
        std::unordered_map<int, bool> channelStates;
        bool paused;
    };
}