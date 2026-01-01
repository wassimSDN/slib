#include "../include/slib_draw.h"


namespace slib
{
    Surface::Surface() {}

	Surface::Surface(const char* fileName) { createSurfaceFromImage(fileName); }

	Surface::Surface(const std::string& fileName)
		: Surface(fileName.c_str()) { }

	Surface::Surface(const uint32_t color) { createSurfaceFromColor(color); }

	Surface::Surface(const unsigned char *data, size_t size) 
	{
		if (this->data)
			SDL_FreeSurface(this->data);

		createSurfaceFromHeader(data, size); 
	}

	Surface::~Surface()
	{
		if (data)
			SDL_FreeSurface(data);
	}

	Surface& Surface::operator=(const char* fileName)
	{
		createSurfaceFromImage(fileName);
		return *this;
	}

	Surface& Surface::operator=(const Surface& other) { return *this; }

	SDL_Surface* Surface::getData() const { return data; }

	Surface::operator bool() const { return data; }

	Surface::operator SDL_Surface* () const { return data; }

	bool Surface::loadImage(const char* fileName) { createSurfaceFromImage(fileName); return data; }

	bool Surface::loadImage(const std::string& fileName) { createSurfaceFromImage(fileName.c_str()); return data; }

	bool Surface::isCreated() const { return data; }

	bool Surface::isLoaded() const { return loaded;  }

	int Surface::getWidth() const
	{
		if (data)
			return data->w;

		return -1;
	}

	int Surface::getHeight() const
	{
		if (data)
			return data->h;

		return -1;
	}

	void Surface::getDimensions(int& w, int& h) const
	{
		if (data)
		{
			w = data->w;
			h = data->h;

			return;
		}

		w = -1;
		h = -1;
	}

	void Surface::createSurfaceFromImage(const char* fileName)
	{
		if (data)
			SDL_FreeSurface(data);

		SDL_Surface* temp = IMG_Load(fileName);
		if (temp)
		{
			data = temp;
			loaded = true;
		}
		else
			createSurfaceFromHeader(missingTextureData, missingTextureSize);
	}

	void Surface::createSurfaceFromColor(uint32_t color)
	{
		if (data)
			SDL_FreeSurface(data);

		SDL_Surface* temp = SDL_CreateRGBSurfaceWithFormat(0, 1, 1, 32, SDL_PIXELFORMAT_RGBA8888);
		if (temp)
		{
			*(uint32_t*)(temp->pixels) = color;
			data = temp;
			loaded = true;
		}
	}

	void Surface::createSurfaceFromHeader(const unsigned char *dataFromHeader, const size_t size)
	{
		SDL_RWops *tempRW = SDL_RWFromConstMem(dataFromHeader, (int)size);
		if (tempRW)
		{
			SDL_Surface* temp = IMG_Load_RW(tempRW, 1);
			if (temp)
				data = temp;

			SDL_FreeRW(tempRW);
		}
	}

	void Surface::createEmptySurface(int w, int h, int format)
	{
		if (data)
			SDL_FreeSurface(data);

		SDL_Surface* temp = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_RGBA8888);
		if (temp)
			data = temp;
	}


	//Crappy Texture class, i can't write comments so figure it out yourself 
	Texture::Texture() {}

	Texture::Texture(const char* fileName) { createTextureFromSurface(Surface(fileName)); }

	Texture::Texture(const std::string& fileName) { createTextureFromSurface(Surface(fileName)); }

	Texture::Texture(SDL_Surface* surface) { createTextureFromSurface(surface); }
	
	Texture::Texture(uint32_t color) { createTextureFromSurface(Surface(color)); }

	Texture::~Texture() { SDL_DestroyTexture(data); }

	bool Texture::loadTexture(const char* fileName) { createTextureFromSurface(Surface(fileName)); return data; }

	bool Texture::loadTexture(const std::string& fileName) { createTextureFromSurface(Surface(fileName)); return data; }

	bool Texture::createTexture(SDL_Surface* surface) { createTextureFromSurface(surface); return data; }

	bool Texture::createTextureAsTarget(int w, int h) { data = SDL_CreateTexture(Window::renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h); return data; }

	bool Texture::isCreated() const { return data; }

	void Texture::draw() const { SDL_RenderCopy(Window::renderer, data, nullptr, nullptr); }

	void Texture::draw(SDL_Rect* sourceRect, SDL_Rect* destRect) const { SDL_RenderCopy(Window::renderer, data, sourceRect, destRect); }

	void Texture::drawReal(SDL_Rect* sourceRect, SDL_FRect* destRect) const { SDL_RenderCopyF(Window::renderer, data, sourceRect, destRect); }

	void Texture::drawAngle(SDL_Rect* sourceRect, SDL_Rect* destRect, double angle, Vector2 center) const
	{
		SDL_Point p = { static_cast<int>(std::round(center.x)), static_cast<int>(std::round(center.y)) };
		SDL_RenderCopyEx(Window::renderer, data, sourceRect, destRect, angle, &p, SDL_FLIP_NONE);
	}

	void Texture::drawAngleReal(SDL_Rect* sourceRect, SDL_FRect* destRect, double angle, Vector2 center) const
	{
		SDL_FPoint p = { center.x, center.y };
		SDL_RenderCopyExF(Window::renderer, data, sourceRect, destRect, angle, &p, SDL_FLIP_NONE);
	}

	void Texture::drawAngleCenter(SDL_Rect* sourceRect, SDL_Rect* destRect, double angle) const { SDL_RenderCopyEx(Window::renderer, data, sourceRect, destRect, angle, nullptr, SDL_FLIP_NONE); }

	void Texture::drawAngleCenterReal(SDL_Rect* sourceRect, SDL_FRect* destRect, double angle) const { SDL_RenderCopyExF(Window::renderer, data, sourceRect, destRect, angle, nullptr, SDL_FLIP_NONE); }

	void Texture::createTextureFromSurface(SDL_Surface* surface)
	{
		if (data)
			SDL_DestroyTexture(data);

		SDL_Texture *temp = SDL_CreateTextureFromSurface(Window::renderer, surface);
		if (temp)
			data = temp;
	}

	Texture::operator bool() const { return data; }

	Texture::operator SDL_Texture* () const { return data; }

//crappy TExt class that's gonna take forever to complete properly 


	Text::Text() { fillCharacterTextures(nullptr); }

	Text::Text(const char* fileName, int fontSize) { fillCharacterTextures(fileName, fontSize); }

	Text::Text(const std::string& fileName, int fontSize)
		: Text(fileName.c_str(), fontSize) {}

	Text::~Text() 
	{ 
		for (auto txt : characterTextures)
			if (txt)
				SDL_DestroyTexture(txt);	
	}

	void Text::setText(const char* text) 
	{
		data = text; 
		int tempH;
		int tempW;
		w = 0;
		int tempMaxW = 0;
		SDL_QueryTexture(characterTextures[0], nullptr, nullptr, nullptr, &tempH);
		h = tempH;
		for (auto it : data)
		{
			if (it == '\n')
			{
				h += tempH;
				if (w < tempMaxW)
					w = tempMaxW;
				tempMaxW = 0;
				continue;
			}
			uint8_t index = it - 32;
			SDL_QueryTexture(characterTextures[index], nullptr, nullptr, &tempW, nullptr);
			tempMaxW += tempW;
		}

		if (w < tempMaxW)
			w = tempMaxW;
	}

	void Text::setText(const std::string& text) { setText(text.c_str()); }

	int Text::getW() const { return w; } 

	int Text::getH() const { return h; }

	void Text::draw(Vector2 dst) 
	{	
		pen.x = dst.x;
		pen.y = dst.y;

		for (auto it : data)
		{
			if (it == '\n')
			{
				pen.y += pen.h;
				pen.x = dst.x;	
				continue;
			}

			uint8_t index = it - 32;
			int w;
			SDL_QueryTexture(characterTextures[index], nullptr, nullptr, &w, nullptr);
			pen.w = (float)w;
			SDL_RenderCopyF(Window::renderer, characterTextures[index], nullptr, &pen);
			pen.x += pen.w;
		}
	}

	void Text::changeColor(SDL_Color c)
	{
		for(auto it : characterTextures)
		{
			SDL_SetTextureColorMod(it, c.r, c.g, c.b);
			SDL_SetTextureAlphaMod(it, c.a);
		}
	}

	void Text::createText(const char* fileName, int fontSize) { fillCharacterTextures(fileName, fontSize); }

	void Text::createText(const std::string& fileName, int fontSize) { fillCharacterTextures(fileName.c_str(), fontSize); }

	void Text::fillCharacterTextures(const char* fileName, int fontSize)
	{
		TTF_Font* font = TTF_OpenFont(fileName, fontSize);
		if (!font)
			font = createFontFromHeader(fontSize);

		for (uint8_t i = 32; i < 127; i++)
		{
			SDL_Surface* surC = TTF_RenderGlyph_Blended(font, i, slib::WHITE);
			if (surC)
			{
				SDL_Texture* temp = SDL_CreateTextureFromSurface(Window::renderer, surC);
				if (temp)
					characterTextures[i - 32] = temp;
			}
			SDL_FreeSurface(surC);
		}
		
		int h;
		SDL_QueryTexture(characterTextures[0], nullptr, nullptr, nullptr, &h);
		pen.h = (float)h;
	}


	TTF_Font* Text::createFontFromHeader(int fontSize)
	{
		SDL_RWops* rw = SDL_RWFromConstMem(slib::missingFont, (int)slib::missingFontSize);
		if (!rw)
			return nullptr;
		
		TTF_Font *font = TTF_OpenFontRW(rw, true, fontSize);
		if (!font)
			return nullptr;

		return font;
	}


	Text2::Text2() {}

	Text2::Text2(const char *fileName) { createAtlas(fileName); }

	Text2::Text2(const std::string& fileName) { createAtlas(fileName.c_str()); }

	Text2::~Text2() {}

	void Text2::setText(const char *text) { data = text; }

	void Text2::setText(const std::string &text) { data = text; }

	void Text2::drawAtlas(SDL_Rect *src, SDL_Rect *dst) const { atlas.draw(src, dst); }

	void Text2::draw(SDL_Rect *dst) const
	{
		SDL_Rect pos = *dst;
		SDL_Rect src = { 0, 0, 200, 200 };

		for (auto it : data)
		{
			if (it == '\n')
			{
				pos.y += pos.h;
				pos.x = dst->x;
				continue;
			}

			uint8_t index = it - 32;

			src.x = index * src.w;
			atlas.draw(&src, dst);
			
			pos.x += pos.w;
		}
	}


	void Text2::createAtlas(const char* fileName)
	{
		if (atlas)
			SDL_DestroyTexture(atlas);

		TTF_Font* font = TTF_OpenFont(fileName, 50);
		if (!font)
			font = createFontFromHeader();

		const char  *model = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
		SDL_Surface *temp = TTF_RenderText_Blended(font, model, slib::WHITE);
		TTF_CloseFont(font);

		if (temp)
		{
			atlas.createTexture(temp);
			SDL_FreeSurface(temp);
		}
	}

	TTF_Font* Text2::createFontFromHeader(int fontSize)
	{
		SDL_RWops* rw = SDL_RWFromConstMem(slib::missingFont, (int)slib::missingFontSize);
		if (!rw)
			return nullptr;

		TTF_Font* font = TTF_OpenFontRW(rw, true, fontSize);
		if (!font)
			return nullptr;

		return font;
	}

}