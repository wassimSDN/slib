#ifndef SLIB_H
#define SLIB_H

#define SDL_MAIN_HANDLED

#include "slib_app.h"
#include "slib_hitbox.h"
#include "slib_draw.h"
#include "slib_sound.h"
#include "slib_animation.h"
#include "slib_utilities.h"
#include "slib_node.h"
#include "slib_scene.h"


#endif

////////////////HOW TO DO SCENES












/*
///////// I HAVE TO FIGURE OUT HOW TO MAKE MENUS (scenes?)
namespace slib
{
	int Init();
	void Quit();

	struct Vector2;
	class Events
	{
	public:
		Events();
		~Events();
		void updateEvents();
		bool shouldQuit();
		bool mouseFocused();
		bool keyboardFocused();
		Vector2 mousePosition();
		void mousePosition(int* x, int* y);
		bool isKeyDown(int key);
		bool isKeyUp(int key);
		bool isKeyJustDown(int key);
		bool isKeyJustUp(int key);
		double getDeltaTime(); 
		bool ticking();
		void reduceAccumulatedTime();
		static void setTicks(int numberOfTicks);

	private:
		static std::array<bool, 256> currentStates;
		static std::array<bool, 256> previousStates;
		static SDL_Event e;
		static bool quit;
		static bool mouse;
		static bool keyboard;
		static bool motion;
		static int mouseX;
		static int mouseY;
		static long double freq;
		static double dt;
		static double currentTime;
		static double lastTime;
		static double timeStep;
		static double accumulatedTime;
	};

	class Window
	{
	public:
		Window(const char* title, int width, int height, int x, int y, int flags);
		Window(std::string title, int width, int height, int x, int y, int flags);
		Window();
		~Window();
		SDL_Window* getData() const;
		void show();
		void hide();
		void changeTitle(const char* title);
		void changeTitle(const std::string& title);
		void changeSize(int w, int h);
		void changePosition(int x, int y);
		void setIcon(SDL_Surface* icon);
		void getSize(int* w, int* h);
		operator SDL_Window* () const;
		bool isCreated() const;
		operator bool() const;
		const Window& operator=(const Window& other);
		bool isRendererCreated();
		static SDL_Renderer* getRenderer();
		void flip();
		void setClearColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
		void clear();

	public:
		SDL_Window* data = nullptr;
		static SDL_Renderer* renderer;
		void createWindow(const char* title, int width, int height, int x, int y, int flags);
		void setRenderer();
		void destroyRenderer();
	};

	class Surface
	{
	public:
		Surface();
		Surface(const char* fileName);
		Surface(const std::string& fileName);
		Surface(const uint32_t color);
		Surface(const unsigned char *dataFromHeader, const size_t size);
		Surface& operator=(const char* fileName);
		~Surface();
		Surface& operator=(const Surface& other); //DO NOT USE, NOT IMPLEMENTED
		SDL_Surface* getData() const;
		bool loadImage(const char* fileName);
		bool loadImage(const std::string& fileName);
		bool isCreated() const;
		int getWidth() const;
		int getHeight() const;
		void getDimensions(int& w, int& h) const;
		operator SDL_Surface* () const;
		operator bool() const;

	private:
		SDL_Surface* data = nullptr;
		void createSurfaceFromImage(const char* fileName);
		void createSurfaceFromColor(uint32_t color);
		void createSurfaceFromHeader(const unsigned char *dataFromHeader, const size_t size);
		//void createEmptySurface(); //DO NOT USE, NOT IMPLEMENTED 
	};

	class Texture : private Window
	{
	public:
		Texture();
		Texture(const char* fileName);
		Texture(const std::string& fileName);
		Texture(SDL_Surface* surface);
		~Texture();
		bool loadTexture(const char* fileName);
		bool loadTexture(const std::string& fileName);
		bool createTexture(SDL_Surface* surface);
		bool isCreated() const;
		void draw();
		void draw(SDL_Rect* sourceRect, SDL_Rect* destRect);
		void drawAngleCenter(SDL_Rect* sourceRect, SDL_Rect* destRect, int angle);
		void drawReal(SDL_Rect* sourceRect, SDL_FRect* destRect);
		operator SDL_Texture* () const;
		operator bool() const;

	private:
		SDL_Texture* data = nullptr;
		void createTextureFromSurface(SDL_Surface* surface);
		//void createEmptyTexture(); //DO NOT USE, NOT IMPLEMENTED
	};

	class Rectangle
	{
	public:
		Rectangle();
		Rectangle(int x, int y, int w, int h);
		void setX(int x);
		void setY(int y);
		void setW(int w);
		void setH(int h);
		void addToX(int n);
		void addToY(int n);
		void addToW(int n);
		void addToH(int n);
		void setPos(int x, int y);
		void setDimensions(int w, int h);
		SDL_Rect get() const;
		bool checkCollision(const SDL_Rect& other) const;
		bool mouseOn(int x, int y);
		bool mouseOn(Vector2 mousePos);
		operator SDL_Rect* () const;
		operator SDL_Rect ();

	private:
		SDL_Rect data = { 0, 0, 0, 0 };
	};

	class RectangleReal
	{
	public:
		RectangleReal();
		RectangleReal(float x, float y, float w, float h);
		void setX(float x);
		void setY(float y);
		void setW(float w);
		void setH(float h);
		void addToX(float n);
		void addToY(float n);
		void setPos(float x, float y);
		void setDimensions(float w, float h);
		SDL_FRect get() const;
		bool checkCollision(const SDL_FRect& other) const;
		bool mouseOn(float x, float y);
		bool mouseOn(Vector2 mousePos);
		operator SDL_FRect* () const;
		operator SDL_FRect();

	private:
		SDL_FRect data = { 0, 0, 0, 0 };
	};

	class SoundEffect
	{
	public:
		SoundEffect();
		SoundEffect(const char* fileName);
		SoundEffect(const std::string& fileName);
		SoundEffect(const unsigned char* dataFromHeader, const size_t size);
		void play();
		void playLoop(int loop);
		void play(int channel);
		void playLoop(int channel, int loop);
		void stop();

	private:
		Mix_Chunk* data = nullptr;
		static int nbrOfSounds;
		void createChunk(const char* fileName);
		void createSoundFromHeader(const unsigned char* dataFromHeader, const size_t size);
	};

	typedef struct Vector2
	{
		Vector2(int x, int y);
		Vector2();

		float x = 0;
		float y = 0;

	} Vector2;

	Vector2 operator*(const int scalar, const Vector2& v);
	Vector2 operator*(const Vector2 &v, const float scalar);
	Vector2 operator+(const Vector2 &first, const Vector2 &second);
	Vector2 operator-(const Vector2 &first, const Vector2 &second);
	Vector2 operator+=(Vector2 &first, const Vector2 &second);
	int operator*(const Vector2 &first, const Vector2& second);






	typedef enum Keys
	{
		unknown = 0,
		key_return = '\r',
		escape = '\x1b',
		backspace = '\b',
		tab = '\t',
		space = ' ',
		exclaim = '!',
		quotedbl = '"',
		hash = '#',
		percent = '%',
		dollar = '$',
		ampersand = '&',
		quote = '\'',
		leftparen = '(',
		rightparen = ')',
		asterisk = '*',
		plus = '+',
		comma = ',',
		minus = '-',
		period = '.',
		slash = '/',
		key_0 = '0',
		key_1 = '1',
		key_2 = '2',
		key_3 = '3',
		key_4 = '4',
		key_5 = '5',
		key_6 = '6',
		key_7 = '7',
		key_8 = '8',
		key_9 = '9',
		COLON = ':',
		semicolon = ';',
		less = '<',
		equals = '=',
		greater = '>',
		question = '?',
		at = '@',
		leftbracket = '[',
		backslash = '\\',
		rightbracket = ']',
		caret = '^',
		underscore = '_',
		backquote = '`',
		a = 'a',
		b = 'b',
		c = 'c',
		d = 'd',
		e = 'e',
		f = 'f',
		g = 'g',
		h = 'h',
		i = 'i',
		j = 'j',
		k = 'k',
		l = 'l',
		m = 'm',
		n = 'n',
		o = 'o',
		p = 'p',
		q = 'q',
		r = 'r',
		s = 's',
		t = 't',
		u = 'u',
		v = 'v',
		w = 'w',
		x = 'x',
		y = 'y',
		z = 'z',

		capslock = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CAPSLOCK),

		f1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F1),
		f2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F2),
		f3 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F3),
		f4 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F4),
		f5 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F5),
		f6 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F6),
		f7 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F7),
		f8 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F8),
		f9 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F9),
		f10 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F10),
		f11 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F11),
		f12 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F12),

		printscreen = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRINTSCREEN),
		scrolllock = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SCROLLLOCK),
		pause = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAUSE),
		insert = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INSERT),
		home = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HOME),
		pageup = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEUP),
		key_delete= '\x7F',
		end = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_END),
		pagedown = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEDOWN),
		right = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RIGHT),
		left = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LEFT),
		down = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DOWN),
		up = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UP),

		numlockclear = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_NUMLOCKCLEAR),
		pad_divide = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DIVIDE),
		pad_multiply = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MULTIPLY),
		pad_minus = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MINUS),
		pad_plus = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUS),
		pad_enter = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_ENTER),
		pad_1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_1),
		pad_2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_2),
		pad_3 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_3),
		pad_4 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_4),
		pad_5 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_5),
		pad_6 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_6),
		pad_7 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_7),
		pad_8 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_8),
		pad_9 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_9),
		pad_0 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_0),
		pad_period = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERIOD),

		application = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APPLICATION),
		power = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_POWER),
		pad_equals = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALS),
		f13 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F13),
		f14 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F14),
		f15 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F15),
		f16 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F16),
		f17 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F17),
		f18 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F18),
		f19 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F19),
		f20 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F20),
		f21 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F21),
		f22 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F22),
		f23 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F23),
		f24 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F24),
		execute = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXECUTE),
		menu = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MENU),
		select = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SELECT),
		stop = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_STOP),
		again = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AGAIN),
		undo = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UNDO),
		cut = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CUT),
		copy = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COPY),
		paste = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PASTE),
		find = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_FIND),
		mute = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MUTE),
		volumeup = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEUP),
		volumedown = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEDOWN),
		pad_comma = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COMMA),
		kp_equalsas400 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALSAS400),

		alterase = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_ALTERASE),
		sysreq = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SYSREQ),
		cancel = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CANCEL),
		clear = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEAR),
		prior = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRIOR),
		slk_separator = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SEPARATOR),
		out = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OUT),
		oper = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OPER),
		clearagain = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEARAGAIN),
		crsel = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CRSEL),
		exsel = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXSEL),

		pad_00 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_00),
		pad_000 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_000),
		thousandsseparator = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_THOUSANDSSEPARATOR),
		decimalseparator = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DECIMALSEPARATOR),
		currencyunit = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYUNIT),
		currencysubunit = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYSUBUNIT),
		pad_leftparen = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTPAREN),
		pad_rightparen = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTPAREN),
		pad_leftbrace = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTBRACE),
		pad_rightbrace = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTBRACE),
		pad_tab = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_TAB),
		pad_backspace = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BACKSPACE),
		pad_a = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_A),
		pad_b = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_B),
		pad_c = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_C),
		pad_d = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_D),
		pad_e = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_E),
		pad_f = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_F),
		pad_xor = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_XOR),
		pad_power = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_POWER),
		pad_percent = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERCENT),
		pad_less = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LESS),
		pad_greater = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_GREATER),
		pad_ampersand = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AMPERSAND),
		pad_dblampersand = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLAMPERSAND),
		pad_verticalbar = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_VERTICALBAR),
		pad_dblverticalbar = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLVERTICALBAR),
		pad_colon = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COLON),
		pad_hash = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HASH),
		pad_space = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_SPACE),
		pad_at = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AT),
		pad_exclam = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EXCLAM),
		pad_memstore = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSTORE),
		pad_memrecall = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMRECALL),
		pad_memclear = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMCLEAR),
		pad_memadd = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMADD),
		pad_memsubtract = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSUBTRACT),
		pad_memmultiply = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMMULTIPLY),
		pad_memdivide = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMDIVIDE),
		pad_plusminus = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUSMINUS),
		pad_clear = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEAR),
		pad_clearentry = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEARENTRY),
		pad_binary = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BINARY),
		pad_octal = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_OCTAL),
		pad_decimal = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DECIMAL),
		pad_hexadecimal = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HEXADECIMAL),

		lctrl = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LCTRL),
		lshift = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LSHIFT),
		lalt = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LALT),
		lgui = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LGUI),
		rctrl = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RCTRL),
		rshift = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RSHIFT),
		ralt = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RALT),
		rgui = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RGUI),

		mode = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MODE),

		audionext = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIONEXT),
		audioprev = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPREV),
		audiostop = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOSTOP),
		audioplay = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPLAY),
		audiomute = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOMUTE),
		mediaselect = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIASELECT),
		www = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_WWW),
		mail = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MAIL),
		calculator = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CALCULATOR),
		computer = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COMPUTER),
		ac_search = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_SEARCH),
		ac_home = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_HOME),
		ac_back = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BACK),
		ac_forward = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_FORWARD),
		ac_stop = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_STOP),
		ac_refresh = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_REFRESH),
		ac_bookmarks = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BOOKMARKS),

		brightnessdown = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSDOWN),
		brightnessup = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSUP),
		displayswitch = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DISPLAYSWITCH),
		kbdillumtoggle = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMTOGGLE),
		kbdillumdown = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMDOWN),
		kbdillumup = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMUP),
		eject = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EJECT),
		sleep = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SLEEP),
		app1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APP1),
		app2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APP2),

		audiorewind = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOREWIND),
		audiofastforward = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOFASTFORWARD),

		softleft = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SOFTLEFT),
		softright = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SOFTRIGHT),
		call = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CALL),
		endcall = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_ENDCALL),
	}Keys;
}



//class Renderer
//{

//public:
//	static void setRenderer(SDL_Window* window);
//	static void destroyRenderer();
//	static bool isCreated();
//	static SDL_Renderer* getRenderer();
//	static void flipBuffer();
//	static void setClearColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
//	static void clearRenderer();

//private:
//	static SDL_Renderer* data;
//};

////NVM BRO, THIS IS CRAP

//void Renderer::setRenderer(SDL_Window* window) { data = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); }

//void Renderer::destroyRenderer() { SDL_DestroyRenderer(data); }

//SDL_Renderer* Renderer::data = nullptr;

//bool Renderer::isCreated() { return data; }

//SDL_Renderer* Renderer::getRenderer() { return data; }

//void Renderer::flipBuffer() { SDL_RenderPresent(data); }

//void Renderer::setClearColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a) { SDL_SetRenderDrawColor(data, r, g, b, a); }

//void  Renderer::clearRenderer() { SDL_RenderClear(data); }
*/