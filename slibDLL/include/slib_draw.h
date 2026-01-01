#ifndef SLIB_DRAW_H
#define SLIB_DRAW_H

#include <string>

#include "slib_app.h"
#include "slib_default_ressources.h"
#include "slib_utilities.h"


namespace slib
{
	class Surface
	{
	public:
		Surface();
		Surface(const char* fileName);
		Surface(const std::string& fileName);
		Surface(const uint32_t color);
		Surface(const unsigned char *data, const size_t size);
		Surface& operator=(const char* fileName);
		~Surface();
		Surface& operator=(const Surface& other); //DO NOT USE, NOT IMPLEMENTED
		SDL_Surface* getData() const;
		bool loadImage(const char* fileName);
		bool loadImage(const std::string& fileName);
		bool isCreated() const;
		bool isLoaded() const;
		int getWidth() const;
		int getHeight() const;
		void getDimensions(int& w, int& h) const;
		operator SDL_Surface* () const;
		operator bool() const;

	private:
		SDL_Surface* data = nullptr;
		bool loaded = false;
		void createSurfaceFromImage(const char* fileName);
		void createSurfaceFromColor(uint32_t color);
		void createSurfaceFromHeader(const unsigned char *dataFromHeader, const size_t size);
		void createEmptySurface(int w, int h, int format); //DO NOT USE, NOT IMPLEMENTED 
	};

	class Texture // : private Window //replaced with friend for memory optimisation (i was stupid)
	{
	public:
		Texture();
		Texture(const char* fileName);
		Texture(const std::string& fileName);
		Texture(SDL_Surface* surface);
		Texture(uint32_t color);
		~Texture();
		bool loadTexture(const char* fileName);
		bool loadTexture(const std::string& fileName);
		bool createTexture(SDL_Surface* surface);
		bool createTextureAsTarget(int w, int h);
		bool isCreated() const;
		void draw() const;
		void draw(SDL_Rect* sourceRect, SDL_Rect* destRect) const;
		void drawReal(SDL_Rect* sourceRect, SDL_FRect* destRect) const;
		void drawAngle(SDL_Rect* sourceRect, SDL_Rect* destRect, double angle, Vector2 center) const;
		void drawAngleReal(SDL_Rect* sourceRect, SDL_FRect* destRect, double angle, Vector2 center) const;
		void drawAngleCenter(SDL_Rect* sourceRect, SDL_Rect* destRect, double angle) const;	
		void drawAngleCenterReal(SDL_Rect* sourceRect, SDL_FRect* destRect, double angle) const;
		operator SDL_Texture* () const;
		operator bool() const;

	private:
		SDL_Texture* data = nullptr;
		void createTextureFromSurface(SDL_Surface* surface);
		//void createEmptyTexture(); //DO NOT USE, NOT IMPLEMENTED
	};

	class Text
	{
	public:
		Text();
		Text(const char* fileName, int fontSize = 24);
		Text(const std::string& fileName, int fontSize = 24);
		~Text();
		void setText(const char *text);
		void setText(const std::string &text);
		void draw(Vector2 dst);
		void changeColor(SDL_Color c);
		void createText(const char* fileName, int fontSize = 24);
		void createText(const std::string& fileName, int fontSize = 24);
		int getW() const;
		int getH() const;
		//void drawAtlas(SDL_Rect* src, SDL_Rect* dst) const;

	private:
		std::string data = "";
		std::array<SDL_Texture*, 95> characterTextures = {};
		SDL_FRect pen = { 0, 0, 0, 0 };
		int w;
		int h;
		void fillCharacterTextures(const char *fileName, int fontSize = 24);
		static TTF_Font *createFontFromHeader(int fontSize = 24);
	};

	class Text2 //DONT USE NOT FINSIHED
	{
	public:
		Text2();
		Text2(const char* fileName);
		Text2(const std::string& fileName);
		~Text2();
		void setText(const char* text);
		void setText(const std::string& text);
		void draw(SDL_Rect* dst) const;
		void drawAtlas(SDL_Rect* src, SDL_Rect* dst) const;

	private:
		std::string data = "";
		Texture atlas;
		void createAtlas(const char *fileName);
		static TTF_Font* createFontFromHeader(int fontSize = 24);
	};
} 

#endif