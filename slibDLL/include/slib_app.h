#ifndef SLIB_APP_H
#define SLIB_APP_H

#include <array>
#include <string>
#include <cmath>

#include "SDL-Stuff/SDL.h"
#include "SDL-Stuff/SDL_mixer.h"
#include "SDL-Stuff/SDL_image.h"
#include "SDL-Stuff/SDL_ttf.h"

#include "slib_hitbox.h"



namespace slib
{
	enum Keys
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
		colon = ':',
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
		key_delete = '\x7F',
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
		endcall = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_ENDCALL)
	};

	enum MouseButtons
	{
		leftclick,
		rightclick,
		middleclick,
		forward,
		back,
		wheelup,
		wheeldown,
		wheelleft,
		wheelright

	} ;

	int Init();
	void Quit();

	class Events
	{
	public:
		Events();
		~Events();
		static void updateEvents();
		static bool shouldQuit();
		static bool mouseFocused();
		static bool keyboardFocused();
		static std::pair<int, int> mousePosition();
		static int getMouseX();
		static int getMouseY();
		static void mousePosition(int* x, int* y);
		static bool isKeyDown(Keys key);
		static bool isKeyUp(Keys key);
		static bool isKeyJustDown(Keys key);
		static bool isKeyJustUp(Keys key);
		static bool isButtonDown(MouseButtons Button);
		static bool isButtonUp(MouseButtons Button);
		static bool isButtonJustDown(MouseButtons Button);
		static bool isButtonJustUp(MouseButtons Button);
		static bool isWheelUp();
		static bool isWheelDown();
		static bool isWheelJustUp();
		static bool isWheelJustDown();
		static bool getMotion();
		static double getDeltaTime(); 
		static bool ticking();
		static void reduceAccumulatedTime();
		static void setTicks(int numberOfTicks);
		static bool isResized();

	private:
		static std::array<bool, 500> currentStates;
		static std::array<bool, 500> previousStates;
		static std::array<bool, 20> currentMouseStates;
		static std::array<bool, 20> previousMouseStates;
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
		static bool resized;

		friend class AnimatedTexture;
		friend class Rectangle;
		friend class RectangleReal;
		friend class Circle;
		friend class Scene;
	};

	class Window
	{
	public:
		Window(const char* title, int width, int height, int x, int y, int flags);
		Window(std::string title, int width, int height, int x, int y, int flags);
		Window();
		~Window();
		SDL_Window* getData() const;
		static void show();
		static void hide();
		static void changeTitle(const char* title);
		static void changeTitle(const std::string& title);
		static void changeSize(int w, int h);
		static void changePosition(int x, int y);
		static void setIcon(SDL_Surface* icon);
		static void getSize(int* w, int* h);
		operator SDL_Window* () const;
		bool isCreated() const;
		void toggleFullscreen();
		operator bool() const;
		const Window& operator=(const Window& other);
		static bool isRendererCreated();
		static SDL_Renderer* getRenderer();
		static void flip();
		static void setClearColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
		static void setClearColor(SDL_Color color);
		static void clear();
		static void setRenderTarget(SDL_Texture *txt);
		static void resetRenderTarget();
		void createWindow(const char* title, int width, int height, int x, int y, int flags);
	
	protected:
		static SDL_Window* data;
		void setRenderer();
		void destroyRenderer();
		static SDL_Renderer* renderer;
		
		friend class Event;
		friend class Texture;
		friend class Text;
		friend class Scene;
		friend class Rectangle;
		friend class RectangleReal;
		friend class Circle;
		friend class CircleReal;
		friend struct Vector3;
		friend void drawCircle(float cx, float cy, float radius, uint32_t color);
		friend void drawCircleFilled(float cx, float cy, float radius, uint32_t color);
		friend void drawCircleStepped(float  cx, float cv, float radius, float step, uint32_t color);
		friend void drawLine(Vector2 p1, Vector2 p2, uint32_t color);
	};

	typedef enum WindowFlags
	{
		centered = SDL_WINDOWPOS_CENTERED,
		posUndefined = SDL_WINDOWPOS_UNDEFINED,
		hidden = SDL_WINDOW_HIDDEN,
		shown = SDL_WINDOW_SHOWN,
		resizable = SDL_WINDOW_RESIZABLE,
		bordeless = SDL_WINDOW_BORDERLESS,
		fullscreen = SDL_WINDOW_FULLSCREEN,
	} WindowFlags;



}

#endif