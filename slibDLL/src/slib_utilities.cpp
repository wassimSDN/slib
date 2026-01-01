#include "../include/slib_utilities.h"

namespace slib
{
	Vector2 bezier(float t, Vector2 p1, Vector2 p2) { return (1.0f - t) * p1 + t * p2; }

	Vector2 bezier(float t, Vector2 points[], size_t size)
	{
		//i'm too stupid to make this but here we go
		//for loop? recusion??

		//i failed goddamn
		// got an idea to use std::vector or some kind of dynamic container
		// but that's too slow for something like this, it should be fast
		// because it will probably be called each frame to fill an array 
		// or something	
	}


	void drawCircle(float cx, float cy, float radius, uint32_t color)
	{
		Color old;
		SDL_GetRenderDrawColor(Window::renderer, &old.r, &old.g, &old.b, &old.a);
		const int r = color >> 24 & 0xff;
		const int g = color >> 16 & 0xff;
		const int b = color >> 8  & 0xff;
		const int a = color       & 0xff;
		Window::setClearColor(r, g, b, a);

		float x = 0;
		float y = -radius;

		for (; x <= -y; x++)
		{
			SDL_RenderDrawPointF(Window::renderer, cx + x, cy + y);
			SDL_RenderDrawPointF(Window::renderer, cx + x, cy - y);
			SDL_RenderDrawPointF(Window::renderer, cx - x, cy + y);
			SDL_RenderDrawPointF(Window::renderer, cx - x, cy - y);

			SDL_RenderDrawPointF(Window::renderer, cx + y, cy + x);
			SDL_RenderDrawPointF(Window::renderer, cx + y, cy - x);
			SDL_RenderDrawPointF(Window::renderer, cx - y, cy + x);
			SDL_RenderDrawPointF(Window::renderer, cx - y, cy - x);

			float my = y + 1.0f;
			if (x * x + my * my > radius * radius)
				y++;
		}

		Window::setClearColor(old);
	}

	void drawCircle(Vector2 c, float radius, uint32_t color) { drawCircle(c.x, c.y, radius, color); }

	void drawCircleFilled(float cx, float cy, float radius, uint32_t color) //to be optimised, got idea, apply after barber
	{
		Color old;
		SDL_GetRenderDrawColor(Window::renderer, &old.r, &old.g, &old.b, &old.a);
		const int r = color >> 24 & 0xff;
		const int g = color >> 16 & 0xff;
		const int b = color >> 8 & 0xff;
		const int a = color & 0xff;
		Window::setClearColor(r, g, b, a);

		float y = cy;
		for (float x = cx; x <= cx + radius; x++)
		{
			for (y = cy; (x - cx) * (x - cx) + (y - cy) * (y - cy) <= radius * radius; y++);
						
			float xm = 2 * cx - x;
			float ym = 2 * cy - y;

			SDL_RenderDrawLineF(Window::renderer, x, y, x, ym);
			SDL_RenderDrawLineF(Window::renderer, xm, y, xm, ym); // a bit faster?
		}

		Window::setClearColor(old);
	}

	void drawCircleFilled(Vector2 c, float radius, uint32_t color) { drawCircleFilled(c.x, c.y, radius, color); }
	
	void drawCircleStepped(float cx, float cy, float radius, float step, uint32_t color)
	{
		Color old;
		SDL_GetRenderDrawColor(Window::renderer, &old.r, &old.g, &old.b, &old.a);
		const int r = color >> 24 & 0xff;
		const int g = color >> 16 & 0xff;
		const int b = color >> 8 & 0xff;
		const int a = color & 0xff;
		Window::setClearColor(r, g, b, a);

		float x = 0;
		float y = -radius;

		for (; x < -y; x += step)
		{
			SDL_RenderDrawPointF(Window::renderer, cx + x, cy + y);
			SDL_RenderDrawPointF(Window::renderer, cx + x, cy - y);
			SDL_RenderDrawPointF(Window::renderer, cx - x, cy + y);
			SDL_RenderDrawPointF(Window::renderer, cx - x, cy - y);

			SDL_RenderDrawPointF(Window::renderer, cx + y, cy + x);
			SDL_RenderDrawPointF(Window::renderer, cx + y, cy - x);
			SDL_RenderDrawPointF(Window::renderer, cx - y, cy + x);
			SDL_RenderDrawPointF(Window::renderer, cx - y, cy - x);

			float my = y + 0.5f;
			if (x * x + my * my >= radius * radius)
				y += step;
		}

		Window::setClearColor(old);
	}

	void drawCircleStepped(Vector2 c, float radius, float step, uint32_t color) { drawCircleStepped(c.x, c.y, radius, step, color); }



}