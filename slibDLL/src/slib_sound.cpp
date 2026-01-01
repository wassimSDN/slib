#include "../include/slib_sound.h"

namespace slib
{
	SoundEffect::SoundEffect() {}

	SoundEffect::SoundEffect(const char* fileName)
	{
		//nbrOfSounds++;
		//if (nbrOfSounds > Mix_AllocateChannels(0))
		//	Mix_AllocateChannels(nbrOfSounds);

		createChunk(fileName);
	}

	SoundEffect::SoundEffect(const std::string& fileName)
		: SoundEffect(fileName.c_str()) {
	}

	SoundEffect::SoundEffect(const unsigned char* dataFromHeader, const size_t size) { createSoundFromHeader(dataFromHeader, size); }

	void SoundEffect::play() { Mix_PlayChannel(-1, data, 0); }

	void SoundEffect::play(int channel) { Mix_PlayChannel(channel, data, 0); }

	void SoundEffect::playLoop(int loop) { Mix_PlayChannel(-1, data, loop); }

	void SoundEffect::playLoop(int channel, int loop) { Mix_PlayChannel(channel, data, loop); }

	void SoundEffect::stop() { Mix_HaltChannel(1); }

	void SoundEffect::createChunk(const char* fileName) 
	{
		if (data)
			Mix_FreeChunk(data);

	   Mix_Chunk *temp = Mix_LoadWAV(fileName); 
	   if (temp)
		   data = temp;
	}

	void SoundEffect::createSoundFromHeader(const unsigned char* dataFromHeader, const size_t size)
	{
		if (data)
			Mix_FreeChunk(data);

		SDL_RWops* tempRW = SDL_RWFromConstMem(dataFromHeader, (int)size);
		if (tempRW)
		{
			Mix_Chunk* temp = Mix_LoadWAV_RW(tempRW, 1);
			if (temp)
				data = temp;
		}
	}

	int SoundEffect::nbrOfSounds = 0;


	Music::Music() {}

	Music::Music(const char* fileName) { createMusic(fileName); }

	Music::Music(const std::string& fileName)
		: Music(fileName.c_str()) {}

	void Music::play() { Mix_PlayMusic(data, -1); }

	void Music::pause() { Mix_PauseMusic(); }

	void Music::resume() { Mix_ResumeMusic(); }

	void Music::toggle() { return Mix_PausedMusic() ? resume() : pause(); }

	void Music::createMusic(const char* fileName)
	{
		if (data)
			Mix_FreeMusic(data);

		Mix_Music* temp = Mix_LoadMUS(fileName);
		if (temp)
			data = temp;
	}
}