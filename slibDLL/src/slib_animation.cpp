#include "../include/slib_animation.h"

namespace slib
{
	AnimatedTexture::AnimatedTexture() {}

	AnimatedTexture::AnimatedTexture(const char *fileName, int nbrFrames, int fps, int x, int y, int w, int h)
		:	spriteSheet(fileName),
			currentFrame(x, y, w, h),
			startX(x),
			startY(y),
			frameTime(1.0f / fps),
			nbrFrames(nbrFrames) {}

	AnimatedTexture::AnimatedTexture(const std::string& fileName, int nbrFrames, int fps, int x, int y, int w, int h)
		:	spriteSheet(fileName),
			currentFrame(x, y, w, h),
			startX(x),
			startY(y),
			frameTime(1.0f / (float)fps),
			nbrFrames(nbrFrames) {}

	void AnimatedTexture::loadSpriteSheet(const char* fileName) { spriteSheet.loadTexture(fileName); }

	void AnimatedTexture::play()
	{
		accumulatedTime += Events::dt;

		while (accumulatedTime >= frameTime)
		{
			accumulatedTime -= frameTime;

			currentFrame.addToX(currentFrame.get().w);
			if (currentFrame.get().x >= currentFrame.get().w * this->nbrFrames + startX)
				currentFrame.setX(startX);
		}
	}

	bool AnimatedTexture::finishedPlaying() { return currentFrame.get().x >= startX + currentFrame.get().w * nbrFrames; }

	void AnimatedTexture::draw(SDL_Rect *dst) const { spriteSheet.draw(currentFrame, dst); }

	void AnimatedTexture::draw(SDL_FRect* dst) const { spriteSheet.drawReal(currentFrame, dst); }

	void AnimatedTexture::drawAngle(SDL_Rect* destRect, double angle, Vector2 center) const { spriteSheet.drawAngle(currentFrame, destRect, angle, center); }

	void AnimatedTexture::drawAngleReal(SDL_FRect* destRect, double angle, Vector2 center) const { spriteSheet.drawAngleReal(currentFrame, destRect, angle, center); }
	
	void AnimatedTexture::drawAngleCenter(SDL_Rect* destRect, double angle) const { spriteSheet.drawAngleCenter(currentFrame, destRect, angle); }

	void AnimatedTexture::drawAngleCenterReal(SDL_FRect* destRect, double angle) const { spriteSheet.drawAngleCenterReal(currentFrame, destRect, angle); }

	void AnimatedTexture::setStartX(int x) 
	{ 
		startX = x; 
		currentFrame.setX(startX);
	}

	void AnimatedTexture::setStartY(int y) 
	{ 
		startY = y; 
		currentFrame.setY(startY);
	}

	void AnimatedTexture::setFrameW(int w) { currentFrame.setW(w); }

	void AnimatedTexture::setFrameH(int h) { currentFrame.setH(h); }

	void AnimatedTexture::setNumberOfFrames(int nbrFrames) { this->nbrFrames = nbrFrames; }

	void AnimatedTexture::setFps(int fps) { frameTime = 1.0f / (float)fps; }

	Rectangle AnimatedTexture::getCurrentFrame() { return currentFrame; }

}