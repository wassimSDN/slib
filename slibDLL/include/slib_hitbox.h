#ifndef SLIB_HITBOX_H
#define SLIB_HITBOX_H

#include "SDL-Stuff/SDL.h"

namespace slib
{
	typedef struct Vector2
	{
		Vector2(float x, float y);
		Vector2() = default;

		Vector2 normalise();
		float length();
		
		float x = 0;
		float y = 0;

	} Vector2;

	Vector2 operator*(const float scalar, const Vector2& v);
	Vector2 operator*(const Vector2& v, const float scalar);
	Vector2 operator+(const Vector2& first, const Vector2& second);
	Vector2 operator-(const Vector2& first, const Vector2& second);
	Vector2 operator+=(Vector2& first, const Vector2& second);
	float operator*(const Vector2& first, const Vector2& second);

	typedef struct Vector3
	{
		Vector3(float x, float y, float z);
		Vector3() = default;

		Vector3 normalise();
		float length();
		Vector2 project();
		Vector2 projectAuto();
		
		float x = 0;
		float y = 0;
		float z = 0;
	}Vector3;

	Vector3 operator*(const float scalar, const Vector3& v);
	Vector3 operator*(const Vector3& v, const float scalar);
	Vector3 operator+(const Vector3& first, const Vector3& second);
	Vector3 operator-(const Vector3& first, const Vector3& second);
	Vector3 operator+=(Vector3& first, const Vector3& second);
	float operator*(const Vector3& first, const Vector3& second);


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
		void add(Vector2 v);
		void setPos(int x, int y);
		void setDimensions(int w, int h);
		SDL_Rect get() const;
		bool checkCollision(const SDL_Rect& other) const;
		bool mouseOn(int x, int y);
		bool mouseOn(Vector2 mousePos);
		bool mouseOn();
		void draw(uint32_t color = 0xff0000ff) const;
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
		void addToW(float n);
		void addToH(float n);
		void add(Vector2 v);
		void setPos(float x, float y);
		void setDimensions(float w, float h);
		SDL_FRect get() const;
		bool checkCollision(const SDL_FRect &other) const;
		bool checkCollisionWithCircle(const SDL_Rect &circleRect) const;
		bool mouseOn(float x, float y);
		bool mouseOn(Vector2 mousePos);
		bool mouseOn();
		void draw(uint32_t color = 0xff0000ff) const;
		void drawFilled(uint32_t color = 0xff0000ff) const;
		operator SDL_FRect* () const;
		operator SDL_FRect();

	private:
		SDL_FRect data = { 0, 0, 0, 0 };
	};

	class Circle
	{
	public:
		Circle();
		Circle(int cX, int cY, int radius);
		void setCenterX(int cX);
		void setCenterY(int cY);
		void setRadius(int radius);
		void addToCenterX(int n);
		void addToCenterY(int n);
		void addToRadius(int n);
		int getCenterX() const;
		int getCenterY() const;
		int getRadius() const;
		SDL_Rect getRect();
		bool checkCollision(const Circle& other) const;
		bool checkCollisionWithRect(const SDL_Rect& rect) const;
		bool mouseOn(int x, int y);
		bool mouseOn(Vector2 mousePos);
		void add(Vector2 v);
		void draw(uint32_t color = 0xff0000ff) const;
		operator SDL_Rect* () const;
		operator SDL_Rect();

	private:
		SDL_Rect data = { 0, 0, 0, 0 };
	};

	class CircleReal
	{
	public:
		CircleReal();
		CircleReal(float cX, float cY, float radius);
		void setCenterX(float cX);
		void setCenterY(float cY);
		void setRadius(float radius);
		void addToCenterX(float n);
		void addToCenterY(float n);
		void addToRadius(float n);
		float getCenterX() const;
		float getCenterY() const;
		Vector2 getCenterPos() const;
		float getRadius() const;
		SDL_FRect getRect();
		bool checkCollision(const CircleReal& other) const;
		bool checkCollisionWithRect(const SDL_FRect& FRect) const;
		bool mouseOn(float x, float y);
		bool mouseOn(Vector2 mousePos);
		void add(Vector2 v);
		void draw(uint32_t color = 0xff0000ff) const;
		operator SDL_FRect* () const;
		operator SDL_FRect();

	private:
		SDL_FRect data = { 0, 0, 0, 0 };
	};
}

#endif