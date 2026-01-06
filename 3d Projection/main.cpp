#include <iostream>

#include <slib.h>

using namespace slib;

#define WIDTH 640
#define HEIGHT 400

int main()
{
	Events e;
	e.setTicks(100);
	Window window("3d cube", WIDTH, HEIGHT, WindowFlags::centered, WindowFlags::centered, WindowFlags::hidden | resizable);

	Vector3 points3d[] =
	{
		{200, 200, 200},
		{-200, 200,200},
		{200, -200, 200},
		{-200, -200, 200},
		{200, 200, -200},
		{-200, 200, -200},
		{200, -200, -200},
		{-200, -200, -200}
	};

	SDL_FPoint points2d[8];
	float angle = 0.1;
	Texture txt;
	float d = 1000.f;

	bool rx = false;
	bool ry = false;
	bool rz = false;

	for (int i = 0; i < 8; i++)
	{
		Vector2 p = points3d[i].projectAuto();
		points2d[i] = { p.x, p.y };
	}

	Text t = "";

	
	window.show();
	while (true)
	{
		e.updateEvents();
		if (e.shouldQuit())
			break;
		while (e.ticking())
		{
			for (int i = 0; i < 8; i++)
			{
				float cos = std::cosf(angle);
				float sin = std::sinf(angle);

				float x = points3d[i].x;
				float y = points3d[i].y;
				float z = points3d[i].z;

				if (rz)
					points3d[i] = { x * cos + - y *  sin, x * sin + y * cos, z};
				if(rx)
					points3d[i] = { x, y * cos - z * sin, y * sin + z * cos};
				if(ry)
					points3d[i] = { x * cos - z * sin, y, x * sin + z * cos };



				Vector2 p = points3d[i].projectAuto();
				points2d[i] = { p.x, p.y };;
			}

			e.reduceAccumulatedTime();
		}

		if (e.isButtonJustDown(leftclick))
			angle += 0.005;
		if (e.isButtonJustDown(rightclick))
			angle -= 0.005;
		if (e.isKeyJustDown(space))
			angle = -angle;
		if (e.isKeyJustDown(q))
			rx = !rx;
		if (e.isKeyJustDown(w))
			ry = !ry;
		if (e.isKeyJustDown(Keys::e))
			rz = !rz;

		t.setText("Angle: " + std::to_string(angle) + '\n' +
				  "X rotation: " + (rx ? "true" : "false") + '\n' +
				  "Y rotation: " + (ry ? "true" : "false") + '\n' +
			      "Z rotation: " + (rz ? "true" : "false") + '\n');


		window.setClearColor(BLACK);
		window.clear();

		window.setClearColor(CORN);

		SDL_RenderDrawLineF(window.getRenderer(), points2d[0].x, points2d[0].y, points2d[1].x, points2d[1].y);
		SDL_RenderDrawLineF(window.getRenderer(), points2d[1].x, points2d[1].y, points2d[3].x, points2d[3].y);
		SDL_RenderDrawLineF(window.getRenderer(), points2d[0].x, points2d[0].y, points2d[4].x, points2d[4].y);
		SDL_RenderDrawLineF(window.getRenderer(), points2d[0].x, points2d[0].y, points2d[2].x, points2d[2].y);
		SDL_RenderDrawLineF(window.getRenderer(), points2d[5].x, points2d[5].y, points2d[1].x, points2d[1].y);
		SDL_RenderDrawLineF(window.getRenderer(), points2d[2].x, points2d[2].y, points2d[6].x, points2d[6].y);
		SDL_RenderDrawLineF(window.getRenderer(), points2d[2].x, points2d[2].y, points2d[3].x, points2d[3].y);
		SDL_RenderDrawLineF(window.getRenderer(), points2d[3].x, points2d[3].y, points2d[7].x, points2d[7].y);
		SDL_RenderDrawLineF(window.getRenderer(), points2d[6].x, points2d[6].y, points2d[7].x, points2d[7].y);
		SDL_RenderDrawLineF(window.getRenderer(), points2d[7].x, points2d[7].y, points2d[5].x, points2d[5].y);
		SDL_RenderDrawLineF(window.getRenderer(), points2d[4].x, points2d[4].y, points2d[6].x, points2d[6].y);
		SDL_RenderDrawLineF(window.getRenderer(), points2d[4].x, points2d[4].y, points2d[5].x, points2d[5].y);
		
		t.draw({ 20, 20 });

		window.flip();

		SDL_Delay(16);
	}
}