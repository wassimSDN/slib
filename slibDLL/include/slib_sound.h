#ifndef SLIB_SOUND_H
#define SLIB_SOUND_H

#include <string>

#include "SDL-Stuff/SDL_mixer.h"

namespace slib
{
    class SoundEffect
	{
	public:
		SoundEffect();
		SoundEffect(const char *fileName);
		SoundEffect(const std::string &fileName);
		SoundEffect(const unsigned char *dataFromHeader, const size_t size); //DON'T USE, kept to keep compiler shut (i'm lazy)
		void play();
		void playLoop(int loop);
		void play(int channel);
		void playLoop(int channel, int loop);
		void stop();

	private:
		Mix_Chunk* data = nullptr;
		static int nbrOfSounds;
		void createChunk(const char* fileName);
		void createSoundFromHeader(const unsigned char *dataFromHeader, const size_t size); //DON'T USE, kept to keep compiler shut (i'm lazy)
	};

	class Music
	{
	public:
		Music();
		Music(const char *fileName);
		Music(const std::string &fileName);
		//Music(const unsigned char* dataFromHeader, const size_t size); DON'T USE, NOT IMPLEMENTED
		void play();
		void playLoop(int loop);
		void pause();
		void resume();
		void toggle();

	private:
		Mix_Music* data = nullptr;
		void createMusic(const char* fileName);
	};
}

#endif