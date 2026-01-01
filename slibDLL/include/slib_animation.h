#ifndef SLIB_ANIMATION_H
#define SLIB_ANIMATION_H

#include "slib_draw.h"
#include "slib_app.h"
#include "slib_hitbox.h"

namespace slib
{
	class AnimatedTexture
	{
	public:
		AnimatedTexture();
		AnimatedTexture(const char *fileName, int nbrFrames, int fps, int x, int y, int h, int w);
		AnimatedTexture(const std::string &fileName, int nbrFrames, int fps, int x, int y, int h, int w);
		void loadSpriteSheet(const char* fileName);
		void play();
		bool finishedPlaying();
		void draw(SDL_Rect *dst) const;
		void draw(SDL_FRect* dst) const;
		void drawAngle(SDL_Rect* destRect, double angle, Vector2 center) const;
		void drawAngleReal(SDL_FRect* destRect, double angle, Vector2 center) const;
		void drawAngleCenter(SDL_Rect* destRect, double angle) const;
		void drawAngleCenterReal(SDL_FRect* destRect, double angle) const;
		void setStartX(int x);
		void setStartY(int y);
		void setFrameW(int w);
		void setFrameH(int h);
		void setNumberOfFrames(int nbrFrames);
		void setFps(int fps);
		Rectangle getCurrentFrame();
		
	private:
		Texture spriteSheet;
		Rectangle currentFrame = {};
		float frameTime;
		double accumulatedTime = 0.0f;
		int nbrFrames = 0;
		int startX = 0;
		int startY = 0;
	};

}



#endif