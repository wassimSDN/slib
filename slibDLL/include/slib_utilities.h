#ifndef SLIB_UTILITIES_H
#define SLIB_UTILITIES_H

#include <cmath>

#include "SDL-Stuff/SDL.h"

#include "slib_app.h"
#include "slib_hitbox.h"


namespace slib
{
	inline long double PI = 3.1415926535897932384626433832795029;

	inline const Vector2 Vect2Up = { 0, -1 };
	inline const Vector2 Vect2Right = { 1, 0 };
	inline const Vector2 Vect2Down = { 0, 1 };
	inline const Vector2 Vect2Left = {-1, 0};

	typedef int Index;

	typedef struct Color
	{
		uint8_t r = 0;
		uint8_t g = 0;
		uint8_t b = 0;
		uint8_t a = 0;

		operator SDL_Color() const { return { this->r , this->g, this->b, this->a }; }
		operator uint32_t() const { return this->r << 24 | this->g << 16 | this->b << 8 | this->a; }

	} Color;

	inline const Color WHITE = { 255, 255, 255, 255 };
	inline const Color BLACK = { 0, 0, 0, 255 };
	inline const Color GREY = { 128, 128, 128, 255 };
	inline const Color RED = { 255, 0, 0, 255 };
	inline const Color GREEN = { 0, 255, 0, 255 };
	inline const Color BLUE = { 0, 0, 255, 255 };
	inline const Color CYAN = { 0, 255, 255, 255 };
	inline const Color PURPLE = { 255, 0, 255, 255 };
	inline const Color YELLOW = { 255, 255, 0, 255 };
	inline const Color CORN = { 100, 149, 237 };

	Vector2 bezier(float t, Vector2 p1, Vector2 p2);
	Vector2 bezier(float t, Vector2 points[], size_t size); //to be finished

	void drawCircle(float cx, float cy, float radius, uint32_t color = WHITE);
	void drawCircle(Vector2 c, float radius, uint32_t color = WHITE);
	void drawCircleFilled(float cx, float cy, float radius, uint32_t color = WHITE);
	void drawCircleFilled(Vector2 c, float radius, uint32_t color = WHITE);
	void drawCircleStepped(float  cx, float cv, float radius, float step, uint32_t color = WHITE);
	void drawCircleStepped(Vector2 c, float radius, float step, uint32_t color = WHITE);
	void drawLine(Vector2 p1, Vector2 p2, uint32_t color = RED);
	void showCursor();
	void hideCursor();
	Vector2 fromToV2(Vector2 src, Vector2 dst);
}

#endif