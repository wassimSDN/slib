/*#include "slib.h"

namespace slib
{

	int Init() { return SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER) |
						Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); }

	void Quit() { SDL_Quit(); Mix_CloseAudio(); }

	Events::Events() { quit = Init(); }

	Events::~Events() { Quit(); }

	bool Events::shouldQuit() { return quit; }

	bool Events::mouseFocused() { return mouse; }

	bool Events::keyboardFocused() { return keyboard; }

	void Events::mousePosition(int* x, int* y)
	{
		if (x)
			*x = mouseX;
		if (y)
			*y = mouseY;
	}

	std::pair<int, int> Events::mousePosition() { return { mouseX, mouseY }; }

	bool Events::isKeyDown(int key) { return currentStates[SDL_GetScancodeFromKey(key)]; }

	bool Events::isKeyUp(int key) { return !currentStates[SDL_GetScancodeFromKey(key)]; }

	bool Events::isKeyJustDown(int key) { return currentStates[SDL_GetScancodeFromKey(key)] && 
												!previousStates[SDL_GetScancodeFromKey(key)]; }

	bool Events::isKeyJustUp(int key) { return !currentStates[SDL_GetScancodeFromKey(key)] && 
												previousStates[SDL_GetScancodeFromKey(key)]; }

	double Events::getDeltaTime() { return dt; }

	bool Events::ticking() { return accumulatedTime >= timeStep; }

	void Events::reduceAccumulatedTime() { accumulatedTime -= timeStep; }

	void Events::setTicks(int numberOfTicks) 
	{ 
		if(numberOfTicks > 0)
			timeStep = 1.0f / numberOfTicks;  
	}

	void Events::updateEvents()
	{
		currentTime = SDL_GetPerformanceCounter() / freq;
		dt = (currentTime - lastTime);
		lastTime = currentTime;
		accumulatedTime += dt;

		previousStates = currentStates;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT: quit = true; break;

			case SDL_KEYDOWN:
				currentStates[SDL_GetScancodeFromKey(e.key.keysym.sym)] = true;
				break;

			case SDL_KEYUP:
				currentStates[SDL_GetScancodeFromKey(e.key.keysym.sym)] = false;
				break;

			case SDL_MOUSEMOTION:
				motion = true;
				mouseX = e.motion.x;
				mouseY = e.motion.y;
				break;

			case SDL_WINDOWEVENT:
				switch (e.window.event)
				{
				case SDL_WINDOWEVENT_ENTER: mouse = true; break;
				case SDL_WINDOWEVENT_LEAVE: mouse = false; break;
				case SDL_WINDOWEVENT_FOCUS_GAINED: keyboard = true; break;
				case SDL_WINDOWEVENT_FOCUS_LOST: keyboard = false; break;
				case SDL_WINDOWEVENT_CLOSE: quit = true; break;
				}
			}
		}
	}

	SDL_Event Events::e = {};
	bool Events::quit = false;
	bool Events::keyboard = false;
	bool Events::motion = false;
	bool Events::mouse = false;
	int Events::mouseX = -1;
	int Events::mouseY = -1;
	long double Events::freq = SDL_GetPerformanceFrequency();
	double Events::dt = 0;
	double Events::currentTime = 0;
	double Events::lastTime = SDL_GetPerformanceCounter() / freq;
	double Events::timeStep = 0;
	double Events::accumulatedTime = 0;

	std::array<bool, 256> Events::currentStates = {};
	std::array<bool, 256> Events::previousStates = {};


	//Crappy Window class, i can't write comments so figure it out yourself
	Window::Window() {}

	Window::Window(const char* title, int width, int height, int x, int y, int flags) { createWindow(title, width, height, x, y, flags); }

	Window::Window(std::string title, int width, int height, int x, int y, int flags)
		: Window(title.c_str(), width, height, x, y, flags) {
	}

	Window::~Window() 
	{  
		if (data)
		{
			SDL_DestroyWindow(data);
			destroyRenderer();
		}
	}

	SDL_Window* Window::getData() const { return data; }

	void  Window::show() { SDL_ShowWindow(data); }

	void Window::hide() { SDL_HideWindow(data); }

	void Window::changeTitle(const char* title) { SDL_SetWindowTitle(data, title); }

	void Window::changeTitle(const std::string& title) { SDL_SetWindowTitle(data, title.c_str()); }

	void Window::changeSize(int w, int h) { SDL_SetWindowSize(data, w, h); }

	void Window::changePosition(int x, int y) { SDL_SetWindowPosition(data, x, y); }

	void Window::setIcon(SDL_Surface* icon) { SDL_SetWindowIcon(data, icon); }

	void Window::getSize(int* w, int* h) { SDL_GetWindowSize(data, w, h); }

	bool Window::isCreated() const { return data; }

	Window::operator SDL_Window* () const { return data; }

	Window::operator bool() const { return data; }

	const Window& Window::operator=(const Window& other)
	{
		if (data)
			SDL_DestroyWindow(data);

		data = other.data;

		return *this;
	}

	void Window::createWindow(const char* title, int width, int height, int x, int y, int flags)
	{
		if (data)
			SDL_DestroyWindow(data);

		SDL_Window* temp = SDL_CreateWindow(title, x, y, width, height, flags);
		if (temp)
		{
			data = temp;
			setRenderer();
		}
	}

	void Window::setRenderer() { renderer = SDL_CreateRenderer(data, -1, SDL_RENDERER_ACCELERATED); }

	void Window::destroyRenderer() { SDL_DestroyRenderer(renderer); }

	SDL_Renderer* Window::renderer = nullptr;

	bool Window::isRendererCreated() { return renderer; }

	SDL_Renderer* Window::getRenderer() { return renderer; }

	void Window::flip() { SDL_RenderPresent(renderer); }

	void Window::setClearColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a) { SDL_SetRenderDrawColor(renderer, r, g, b, a); }

	void  Window::clear() { SDL_RenderClear(renderer); }

	//Crappy Surface class, i can't write comments so figure it out yourself
	Surface::Surface() {}

	Surface::Surface(const char* fileName) { createSurfaceFromImage(fileName); }

	Surface::Surface(const std::string& fileName)
		: Surface(fileName.c_str()) { }

	Surface::Surface(const uint32_t color) { createSurfaceFromColor(color); }

	Surface::Surface(const unsigned char *dataFromHeader, const size_t size) { createSurfaceFromHeader(dataFromHeader, size); }

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

	int Surface::getWidth() const
	{
		if (data)
			return data->w;

		return 0;
	}

	int Surface::getHeight() const
	{
		if (data)
			return data->h;

		return 0;
	}

	void Surface::getDimensions(int& w, int& h) const
	{
		if (data)
		{
			w = data->w;
			h = data->h;

			return;
		}

		w = 0;
		h = 0;
	}

	void Surface::createSurfaceFromImage(const char* fileName)
	{
		if (data)
			SDL_FreeSurface(data);

		SDL_Surface* temp = IMG_Load(fileName);
		if (temp)
			data = temp;
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
		}
	}

	void Surface::createSurfaceFromHeader(const unsigned char *dataFromHeader, const size_t size)
	{
		if (data)
			SDL_FreeSurface(data);

		SDL_RWops *tempRW = SDL_RWFromConstMem(dataFromHeader, size);
		if (tempRW)
		{
			SDL_Surface* temp = IMG_Load_RW(tempRW, 0);
			if (temp)
				data = temp;

			SDL_FreeRW(tempRW);
		}
	}



	//Crappy Texture class, i can't write comments so figure it out yourself 
	Texture::Texture() {}

	Texture::Texture(const char* fileName) { createTextureFromSurface(Surface(fileName)); }

	Texture::Texture(const std::string& fileName) { createTextureFromSurface(Surface(fileName)); }

	Texture::Texture(SDL_Surface* surface) { createTextureFromSurface(surface); }

	Texture::~Texture() { SDL_DestroyTexture(data); }

	bool Texture::loadTexture(const char* fileName) { createTextureFromSurface(Surface(fileName)); return data; }

	bool Texture::loadTexture(const std::string& fileName) { createTextureFromSurface(Surface(fileName)); return data; }

	bool Texture::createTexture(SDL_Surface* surface) { createTextureFromSurface(surface); return data; }

	bool Texture::isCreated() const { return data; }

	void Texture::draw() { SDL_RenderCopy(getRenderer(), data, nullptr, nullptr); }

	void Texture::draw(SDL_Rect* sourceRect, SDL_Rect* destRect) { SDL_RenderCopy(getRenderer(), data, sourceRect, destRect); }

	void Texture::drawReal(SDL_Rect* sourceRect, SDL_FRect* destRect) { SDL_RenderCopyF(getRenderer(), data, sourceRect, destRect); }

	void Texture::drawAngleCenter(SDL_Rect* sourceRect, SDL_Rect* destRect, int angle) { SDL_RenderCopyEx(getRenderer(), data, sourceRect, destRect, angle, nullptr, SDL_FLIP_NONE); }

	void Texture::createTextureFromSurface(SDL_Surface* surface)
	{
		if (data)
			SDL_DestroyTexture(data);
		data = SDL_CreateTextureFromSurface(getRenderer(), surface);
	}

	Texture::operator bool() const { return data; }

	Texture::operator SDL_Texture* () const { return data; }

	//Crappy Hitbox class, i can't write comments so figure it out yourself 
	Rectangle::Rectangle() {}

	Rectangle::Rectangle(int x, int y, int w, int h)
		: data{ x, y, w, h } {
	}

	SDL_Rect Rectangle::get() const { return data; }

	void Rectangle::setX(int x) { data.x = x; }

	void Rectangle::setY(int y) { data.y = y; }

	void Rectangle::setW(int w) { data.w = w; }

	void Rectangle::setH(int h) { data.h = h; }

	void Rectangle::addToX(int n) { data.x += n; }

	void Rectangle::addToY(int n) { data.y += n; }

	void Rectangle::addToW(int n) { data.w += n; }

	void Rectangle::addToH(int n) { data.h += n; }

	void Rectangle::setPos(int x, int y) { setX(x); setY(y); }

	void Rectangle::setDimensions(int w, int h) { setW(w); setH(h); }

	Rectangle::operator SDL_Rect* () const { return (SDL_Rect*)(&data); }

	Rectangle::operator SDL_Rect () { return data; }

	bool Rectangle::checkCollision(const SDL_Rect& other) const { return SDL_HasIntersection(&data, &other); }

	bool Rectangle::mouseOn(int x, int y)
	{

		return x > data.x && x < data.x + data.w &&
			y > data.y && y < data.y + data.h;
	}

	bool Rectangle::mouseOn(Vector2 mousePos)
	{
		return mousePos.x > data.x && mousePos.x < data.x + data.w &&
			mousePos.y > data.y && mousePos.y < data.y + data.h;
	}

	////sssss
	RectangleReal::RectangleReal() {}

	RectangleReal::RectangleReal(float x, float y, float w, float h)
		: data{ x, y, w, h } {
	}

	SDL_FRect RectangleReal::get() const { return data; }

	void RectangleReal::setX(float x) { data.x = x; }

	void RectangleReal::setY(float y) { data.y = y; }

	void RectangleReal::setW(float w) { data.w = w; }

	void RectangleReal::setH(float h) { data.h = h; }

	void RectangleReal::addToX(float n) { data.x += n; }

	void RectangleReal::addToY(float n) { data.y += n; }

	void RectangleReal::setPos(float x, float y) { setX(x); setY(y); }

	void RectangleReal::setDimensions(float w, float h) { setW(w); setH(h); }

	RectangleReal::operator SDL_FRect* () const { return (SDL_FRect*)(&data); }

	RectangleReal::operator SDL_FRect () { return data; }

	bool RectangleReal::checkCollision(const SDL_FRect& other) const { return SDL_HasIntersectionF(&data, &other); }

	bool RectangleReal::mouseOn(float x, float y)
	{
	   return x > data.x && x < data.x + data.w &&
			y > data.y && y < data.y + data.h;
	}

	bool RectangleReal::mouseOn(Vector2 mousePos)
	{
		return mousePos.x > data.x && mousePos.x < data.x + data.w &&
			mousePos.y > data.y && mousePos.y < data.y + data.h;
	}




	//Crappy Sound Effect class, i can't write comments so figure it out yourself 
	SoundEffect::SoundEffect() {}

	SoundEffect::SoundEffect(const char* fileName)
	{
		nbrOfSounds++;
		if (nbrOfSounds > Mix_AllocateChannels(0))
			Mix_AllocateChannels(nbrOfSounds);

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

	void SoundEffect::stop() {}

	void SoundEffect::createChunk(const char* fileName) { data = Mix_LoadWAV(fileName); }

	void SoundEffect::createSoundFromHeader(const unsigned char* dataFromHeader, const size_t size)
	{
		if (data)
			Mix_FreeChunk(data);

		SDL_RWops* tempRW = SDL_RWFromConstMem(dataFromHeader, size);
		if (tempRW)
		{
			Mix_Chunk* temp = Mix_LoadWAV_RW(tempRW, 0);
			if (temp)
				data = temp;

			SDL_FreeRW(tempRW);
		}
	}

	int SoundEffect::nbrOfSounds = 0;


	Vector2::Vector2() {}

	Vector2::Vector2(int x, int y)
		: x(x), y(y) {}

	Vector2 operator*(int scalar, const Vector2& v) { return Vector2(v.x * scalar, v.y * scalar); }

	Vector2 operator*(const Vector2& v, const float scalar){ return Vector2(v.x * scalar, v.y * scalar); }

	Vector2 operator+(const Vector2& first, const Vector2& second){ return Vector2(first.x + second.x, first.y + second.y); }

	Vector2 operator-(const Vector2& first, const Vector2& second){ return Vector2(first.x - second.x, first.y - second.y); }

	Vector2 operator+=(Vector2& first, const Vector2& second)
	{
		first = first + second;

		return first;
	}

	int operator*(const Vector2& first, const Vector2& second){ return first.x * second.x + first.y * second.y; }


}


*/