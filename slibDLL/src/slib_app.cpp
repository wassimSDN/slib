#include "../include/slib_app.h"

namespace slib
{
	int Init() { return SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER) |
						Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) |
						TTF_Init(); }

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

	int Events::getMouseX() { return mouseX; }

	int Events::getMouseY() { return mouseY; }

	bool Events::isKeyDown(Keys key) { return currentStates[SDL_GetScancodeFromKey(key)]; }

	bool Events::isKeyUp(Keys key) { return !currentStates[SDL_GetScancodeFromKey(key)]; }

	bool Events::isKeyJustDown(Keys key) { return currentStates[SDL_GetScancodeFromKey(key)] && 
												!previousStates[SDL_GetScancodeFromKey(key)]; }

	bool Events::isKeyJustUp(Keys key) { return !currentStates[SDL_GetScancodeFromKey(key)] && 
												previousStates[SDL_GetScancodeFromKey(key)]; }

	bool Events::isButtonDown(MouseButtons button) { return currentMouseStates[button]; }

	bool Events::isButtonUp(MouseButtons button) { return !currentMouseStates[button]; }

	bool Events::isButtonJustDown(MouseButtons button) { return currentMouseStates[button] &&
													  !previousMouseStates[button];   }

	bool Events::isButtonJustUp(MouseButtons button) { return !currentMouseStates[button] &&
											   		  previousMouseStates[button]; }

	bool Events::isWheelDown() { return currentMouseStates[wheeldown]; }

	bool Events::isWheelUp() { return currentMouseStates[wheelup]; }

	bool Events::getMotion() { return motion; }

	double Events::getDeltaTime() { return dt; }

	bool Events::ticking() { return accumulatedTime >= timeStep; }

	void Events::reduceAccumulatedTime() { accumulatedTime -= timeStep; }

	bool Events::isResized() { return resized; }

	void Events::setTicks(int numberOfTicks) 
	{ 
		if (numberOfTicks > 0)
		{
			timeStep = 1.0f / numberOfTicks;
			return;
		}
	
		timeStep = 1.0f / 20; 
	}

	void Events::updateEvents()
	{
		currentTime = SDL_GetPerformanceCounter() / freq ;
		dt = (currentTime - lastTime);
		lastTime = currentTime;
		accumulatedTime += dt;

		previousStates = currentStates;
		previousMouseStates = currentMouseStates;

		currentMouseStates[wheeldown] = false;
		currentMouseStates[wheelup] = false;
		currentMouseStates[wheelleft] = false;
		currentMouseStates[wheelright] = false;
		motion = false;
		resized = false;

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

			case SDL_MOUSEBUTTONDOWN:
				switch (e.button.button)
				{
				case SDL_BUTTON_MIDDLE:
					currentMouseStates[middleclick] = true;
					break;
				case SDL_BUTTON_LEFT:
					currentMouseStates[leftclick] = true;
					break;
				case SDL_BUTTON_RIGHT:
					currentMouseStates[rightclick] = true;
					break;
				case SDL_BUTTON_X1:
					currentMouseStates[back] = true;
					break;
				case SDL_BUTTON_X2:
					currentMouseStates[forward] = true;
					break;
				}
				break;

			case SDL_MOUSEBUTTONUP:
				switch (e.button.button)
				{
				case SDL_BUTTON_MIDDLE:
					currentMouseStates[middleclick] = false;
					break;
				case SDL_BUTTON_LEFT:
					currentMouseStates[leftclick] = false;
					break;
				case SDL_BUTTON_RIGHT:
					currentMouseStates[rightclick] = false;
					break;
				case SDL_BUTTON_X1:
					currentMouseStates[back] = false;
					break;
				case SDL_BUTTON_X2:
					currentMouseStates[forward] = false;
					break;
				}
				break;

			case SDL_MOUSEWHEEL:
			{
				currentMouseStates[wheeldown] = e.wheel.y < 0 ;
				currentMouseStates[wheelup] = e.wheel.y > 0;
				currentMouseStates[wheelleft] = e.wheel.x < 0;
				currentMouseStates[wheelright] = e.wheel.x > 0;
			}
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
				case SDL_WINDOWEVENT_SIZE_CHANGED: resized = true; break;
				}
				break;
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
	long double Events::freq = (long double)SDL_GetPerformanceFrequency();
	double Events::dt = 0;
	double Events::currentTime = 0;
	double Events::lastTime = SDL_GetPerformanceCounter() / freq;
	double Events::timeStep = 0;
	double Events::accumulatedTime = 0;
	bool Events::resized = false;

	std::array<bool, 500> Events::currentStates = {};
	std::array<bool, 500> Events::previousStates = {};

	std::array<bool, 20> Events::currentMouseStates = {};
	std::array<bool, 20> Events::previousMouseStates = {};

	//Crappy Window class, i can't write comments so figure it out yourself
	Window::Window() {}

	Window::Window(const char* title, int width, int height, int x, int y, int flags) { createWindow(title, width, height, x, y, flags); }

	Window::Window(std::string title, int width, int height, int x, int y, int flags)
		: Window(title.c_str(), width, height, x, y, flags) {}

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


	bool Window::isRendererCreated() { return renderer; }

	SDL_Renderer* Window::getRenderer() { return renderer; }

	void Window::flip() { SDL_RenderPresent(renderer); }

	void Window::setClearColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a) { SDL_SetRenderDrawColor(renderer, r, g, b, a); }

	void Window::setClearColor(SDL_Color color) { SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); }

	void  Window::clear() { SDL_RenderClear(renderer); }

	void Window::setRenderTarget(SDL_Texture *txt)
	{
		SDL_SetRenderTarget(renderer, txt);
	}
	void Window::resetRenderTarget()
	{
		SDL_SetRenderTarget(renderer, nullptr);
	}

	//SDL_Window* Window::data = nullptr;
	SDL_Renderer* Window::renderer = nullptr;
}