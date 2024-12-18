#include "Audio.h"
#include <iostream>
#include <unordered_map>
#include "../ResourceManager.h"
namespace IonixEngine
{

    Mix_Chunk* Audio::LoadWAV(const char* fileName)
    {
        return ResourceManager::GetInstance().GetAudio(ResourceManager::GetInstance().AUDIO_PATH + "/" + fileName);
    }

    //tested
    void Audio::PlayAudio(Mix_Chunk* chunk, int loops)
    {
        if (Mix_Playing(-1) == 8)
        {
            std::cout << "All channels are being used, chunk cannot be played." << std::endl;
            return;
        }
        else
        { 
            for (int x = 0; x < 7; x++)
            {
                if (Mix_Playing(x) == 0)
                {
                    Mix_PlayChannel(-1, chunk, loops);
                    return;
                }
            }
        }
    } 
    //tested
    void Audio::PauseAudio(Mix_Chunk* chunk)
    {
        for (int x = 0; x < 7; x++)
        {
            if (Mix_GetChunk(x) == chunk)
            {
                Mix_Pause(x);
            }
        }
    }
    //tested (this function has both pause and resume)
    void Audio::PauseAllAudio()
    {
        if (!paused)
        {
            Mix_Pause(-1);
            paused = true;
        }
        else if (paused)
        {
            Mix_Resume(-1);
            paused = false;
        }
    }
    //tested
    void Audio::ResumeAudio(Mix_Chunk* chunk)
    {
        for (int x = 0; x < 7; x++)
        {
            if (Mix_GetChunk(x) == chunk)
            {
                Mix_Resume(x);
            }
        }
    }
    //tested
    void Audio::ClearChannel(Mix_Chunk* chunk)
    {
        for (int x = 0; x < 7; x++)
        {
            if (Mix_GetChunk(x) == chunk)
            {
                Mix_HaltChannel(x);
            }
        }
    }
    //tested
    void Audio::ClearAllChannels()
    {
        Mix_HaltChannel(-1);
    }
    //tested
    void Audio::SetVolume(int volume, Mix_Chunk* chunk)
    {
        double newVolume = MIX_MAX_VOLUME * ((float)volume / 100);  // Scale volume from 0-100 to MIX_MAX_VOLUME range
        for (int x = 0; x < 7; x++)
        {
            if (Mix_GetChunk(x) == chunk)
            {
                Mix_Volume(x,volume);
            }
        }
    }
    //tested
    void Audio::FadeIn(int ms, Mix_Chunk* chunk, int loops)
    {
        if (Mix_Playing(-1) == 8)
        {
            std::cout << "All channels are being used, chunk cannot be played." << std::endl;
            return;
        }
        else
        {
            for (int x = 0; x < 7; x++)
            {
                if (Mix_Playing(x) == 0)
                {
                    Mix_FadeInChannel(x, chunk, loops, ms);
                    return;
                }
            }
        }
    }
    //tested
    void Audio::FadeOut(int ms, Mix_Chunk* chunk)
    {
        for (int x = 0; x < 7; x++)
        {
            if (Mix_GetChunk(x) == chunk)
            {
                Mix_FadeOutChannel(x, ms);
            }
        }
    }
    //tested
    void Audio::TimedPlay(Mix_Chunk* chunk, float interval)
    {
        double currentTime = double(SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency());
        if (currentTime - initialTime >= interval)
        {
            PlayAudio(chunk, 1);
            initialTime = double(SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency());
            std::cout << "Sound played" << std::endl;
        }
    }
    //tested
    void Audio::RandomTimedPlay(Mix_Chunk* chunk, int min, int max)
    {
        if (randomNumGenerated == false)
        {
            randomInterval = rand() % (max - min + 1) + min;
            randomNumGenerated = true;
        }

        double randomCurrentTime = double(SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency());
        
        if (randomCurrentTime - randomInitialTime >= randomInterval)
        {
            PlayAudio(chunk, 1);
            randomInitialTime = double(SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency());
            std::cout << "Sound played, new interval is: " << randomInterval << std::endl;
            randomNumGenerated = false;
        }
    }
}


