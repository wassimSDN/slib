#include "../include/slib_hitbox.h"
#include "../include/slib_utilities.h"



namespace slib
{
	Rectangle::Rectangle() {}

	Rectangle::Rectangle(int x, int y, int w, int h)
		: data{ x, y, w, h } {}

	SDL_Rect Rectangle::get() const { return data; }

	void Rectangle::setX(int x) { data.x = x; }

	void Rectangle::setY(int y) { data.y = y; }

	void Rectangle::setW(int w) { data.w = w; }

	void Rectangle::setH(int h) { data.h = h; }

	void Rectangle::addToX(int n) { data.x += n; }

	void Rectangle::addToY(int n) { data.y += n; }

	void Rectangle::addToW(int n) { data.w += n; }

	void Rectangle::addToH(int n) { data.h += n; }

	void Rectangle::add(Vector2 v) { data.x += (int)v.x; data.y += (int)v.y; }

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

	bool Rectangle::mouseOn()
	{
		return Events::mouseX > data.x && Events::mouseX < data.x + data.w &&
			   Events::mouseY > data.y && Events::mouseY < data.y + data.h;
	}

	void Rectangle::draw(uint32_t color) const
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
		SDL_GetRenderDrawColor(Window::renderer, &r, &g, &b, &a);

		SDL_Color c = { color >> 24 & 0xff, color >> 16 & 0xff, color >> 8 & 0xff , color & 0xff };
		Window::setClearColor(c);
		SDL_RenderDrawRect(Window::renderer, &data);
		Window::setClearColor({ r, g, b, a });
	}


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

	void RectangleReal::addToW(float n) { data.w += n; }

	void RectangleReal::addToH(float n) { data.h += n; }

	void RectangleReal::add(Vector2 v) { data.x += v.x; data.y += v.y; }

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

	bool RectangleReal::mouseOn()
	{
		return Events::mouseX > data.x && Events::mouseX < data.x + data.w &&
			Events::mouseY > data.y && Events::mouseY < data.y + data.h;
	}

	void RectangleReal::draw(uint32_t color) const
	{ 
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
		SDL_GetRenderDrawColor(Window::renderer, &r, &g, &b, &a);

		SDL_Color c = { color >> 24 & 0xff, color >> 16 & 0xff, color >> 8 & 0xff , color & 0xff };
		Window::setClearColor(c);
		SDL_RenderDrawRectF(Window::renderer, &data);

		Window::setClearColor({ r, g, b, a });
	}

	void RectangleReal::drawFilled(uint32_t color) const
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
		SDL_GetRenderDrawColor(Window::renderer, &r, &g, &b, &a);

		SDL_Color c = { color >> 24 & 0xff, color >> 16 & 0xff, color >> 8 & 0xff , color & 0xff };
		Window::setClearColor(c);
		SDL_RenderFillRectF(Window::renderer, &data);

		Window::setClearColor({ r, g, b, a });
	}

	Circle::Circle() {}

	Circle::Circle(int cX, int cY, int radius) { data = { cX - radius, cY - radius, radius * 2, radius * 2}; }

	void Circle::setCenterX(int cX) { data.x = cX  - data.w / 2; }

	void Circle::setCenterY(int cY) { data.y = cY - data.h / 2; }

	void Circle::setRadius(int radius) { data.w = data.h = radius; }

	void Circle::addToCenterX(int n) { data.x += n; }

	void Circle::addToCenterY(int n) { data.y += n; }

	void Circle::addToRadius(int n) 
	{ 
		data.w = data.h += n;
		data.x -= n / 2; 
		data.y -= n / 2; 
	}

	int Circle::getCenterX() const { return data.x + data.w / 2; }

	int Circle::getCenterY() const { return data.y + data.h / 2; }

	int Circle::getRadius() const { return data.w / 2; }

	SDL_Rect Circle::getRect() { return data; }

	bool Circle::checkCollision(const Circle &other) const
	{
		const int dx = getCenterX() - other.getCenterX();
		const int dy = getCenterY() - other.getCenterY();
		const int distanceSquared = dx * dx + dy * dy;
		const int radiusSum = getRadius() + other.getRadius();

		return distanceSquared <= radiusSum * radiusSum;
	}
			
	bool Circle::checkCollisionWithRect(const SDL_Rect& rect) const
	{
		int closestX = getCenterX();
		int closestY = getCenterY();

	 

		if (getCenterX() <= rect.x)
			closestX = rect.x;
		else if (getCenterX() >= rect.x + rect.w)
			closestX = rect.x + rect.w;

		if (getCenterY() <= rect.y)
			closestY = rect.y;
		else if (getCenterY() >= rect.y + rect.h)
			closestY = rect.y + rect.h;

		int distanceX = closestX - getCenterX();
		int distanceY = closestY - getCenterY();

		return distanceX * distanceX + distanceY * distanceY < getRadius() * getRadius();
	}

	void Circle::add(Vector2 v) { data.x += v.x; data.y += v.y; }

	void Circle::draw(uint32_t color) const { drawCircle(getCenterX(), getCenterY(), data.w / 2, color); }

	Circle::operator SDL_Rect* () const { return (SDL_Rect*)(&data); }


	CircleReal::CircleReal() {}

	CircleReal::CircleReal(float cX, float cY, float radius) { data = { cX - radius, cY - radius, radius * 2, radius * 2 }; }

	void CircleReal::setCenterX(float cX) { data.x = cX - data.w / 2; }

	void CircleReal::setCenterY(float cY) { data.y = cY - data.h / 2; }

	void CircleReal::setRadius(float radius) { data.w = data.h = radius; }

	void CircleReal::addToCenterX(float n) { data.x += n; }

	void CircleReal::addToCenterY(float n) { data.y += n; }

	void CircleReal::addToRadius(float n)
	{
		data.w = data.h += n;
		data.x -= n / 2;
		data.y -= n / 2;
	}

	float CircleReal::getCenterX() const { return data.x + data.w / 2; }
	      
	float CircleReal::getCenterY() const { return data.y + data.h / 2; }

	float CircleReal::getRadius() const { return data.w / 2; }

	SDL_FRect CircleReal::getRect() { return data; }

	bool CircleReal::checkCollision(const CircleReal& other) const
	{
		const float dx = getCenterX() - other.getCenterX();
		const float dy = getCenterY() - other.getCenterY();
		const float distanceSquared = dx * dx + dy * dy;
		const float radiusSum = getRadius() + other.getRadius();

		return distanceSquared <= radiusSum * radiusSum;
	}

	bool CircleReal::checkCollisionWithRect(const SDL_FRect& rect) const
	{
		float closestX = getCenterX();
		float closestY = getCenterY();


		if (getCenterX() <= rect.x)
			closestX = rect.x;
		else if (getCenterX() >= rect.x + rect.w)
			closestX = rect.x + rect.w;

		if (getCenterY() <= rect.y)
			closestY = rect.y;
		else if (getCenterY() >= rect.y + rect.h)
			closestY = rect.y + rect.h;

		float distanceX = closestX - getCenterX();
		float distanceY = closestY - getCenterY();

		return distanceX * distanceX + distanceY * distanceY < getRadius() * getRadius();
	}
	
	void CircleReal::add(Vector2 v) { data.x += v.x; data.y += v.y; }


	void CircleReal::draw(uint32_t color) const { drawCircle(getCenterX(), getCenterY(), data.h / 2.0f, color); }

	CircleReal::operator SDL_FRect* () const { return (SDL_FRect*)(&data); }

	Vector2::Vector2(float x, float y)
		: x(x), y(y) {}

	Vector2 Vector2::normalise()
	{
		float length = std::sqrtf(x * x + y * y);
		x /= length;
		y /= length;

		return *this;
	}

	Vector2 operator*(const float scalar, const Vector2& v) { return Vector2(v.x * scalar, v.y * scalar); }

	Vector2 operator*(const Vector2& v, const float scalar){ return Vector2(v.x * scalar, v.y * scalar); }

	Vector2 operator+(const Vector2& first, const Vector2& second){ return Vector2(first.x + second.x, first.y + second.y); }

	Vector2 operator-(const Vector2& first, const Vector2& second){ return Vector2(first.x - second.x, first.y - second.y); }

	Vector2 operator+=(Vector2& first, const Vector2& second)
	{
		first = first + second;

		return first;
	}

	float operator*(const Vector2& first, const Vector2& second){ return first.x * second.x + first.y * second.y; }


	Vector3::Vector3(float x, float y, float z)
		: x(x), y(y), z(z) {}

	Vector3 Vector3::normalise()
	{
		float length = std::sqrtf(x * x + y * y + z * z);
		x /= length;
		y /= length;
		z /= length;

		return *this;
	}

	Vector2 Vector3::project()
	{
		return { x / z, y / z };
	}

	Vector2 Vector3::projectAuto()
	{
		int w, h;
		Window::getSize(&w, &h);
		float xoffset = (float)w / 2.0f;
		float yoffset = (float)h / 2.0f;

		float d = 1000.0f;
		float zproj = z + d;

		return { x * (d / zproj) + xoffset, y * (d /  zproj) + yoffset};
	}

	Vector3 operator*(const float scalar, const Vector3& v) { return Vector3(v.x * scalar, v.y * scalar, v.z * scalar); }

	Vector3 operator*(const Vector3& v, const float scalar) { return Vector3(v.x * scalar, v.y * scalar, v.z * scalar); }

	Vector3 operator+(const Vector3& first, const Vector3& second) { return Vector3(first.x + second.x, first.y + second.y, first.z + second.z); }

	Vector3 operator-(const Vector3& first, const Vector3& second) { return Vector3(first.x - second.x, first.y - second.y, first.z - second.z); }

	Vector3 operator+=(Vector3& first, const Vector3& second)
	{
		first = first + second;

		return first;
	}


}