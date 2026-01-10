#include <iostream>

#include <slib.h>

using namespace slib;

#define WIDTH 1000
#define HEIGHT 800

int WinMain()
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
	float angle = 0.0f;
	float d = 1000.f;

	bool rx = false;
	bool ry = false;
	bool rz = false;

	for (int i = 0; i < 8; i++)
	{
		Vector2 p = points3d[i].projectAuto();
		points2d[i] = { p.x, p.y };
	}

	const int fontSize = 40;
	Text titleText = { "", fontSize };
	Text angleText = { "", fontSize };
	Text trueText  = { "", fontSize };
	Text falseText = { "", fontSize };

	trueText.setText("on");
	trueText.changeColor(GREEN);
	falseText.setText("off");
	falseText.changeColor(RED);

	Vector2 textPos;
	float origin = 20;
	float xoffset = WIDTH / 2;
	float yoffset = HEIGHT / 2;
	
	window.show();
	while (true)
	{
		e.updateEvents();
		if (e.shouldQuit() || e.isKeyJustDown(Keys::escape))
			break;
		while (e.ticking())
		{
			for (int i = 0; i < 8; i++)
			{
				Vector3 vel = { 0, 0, 0 };

				if (e.isKeyDown(Keys::e))
					vel.z = 10;
				if (e.isKeyDown(Keys::q))
					vel.z = -10;

				if (e.isKeyDown(Keys::d))
					vel.x = 10;
				if (e.isKeyDown(Keys::a))
					vel.x = -10;

				if (e.isKeyDown(Keys::w))
					vel.y = -10;
				if (e.isKeyDown(Keys::s))
					vel.y = 10;

				points3d[i] += vel.normalise() * 10;

				float cos = std::cosf(angle);
				float sin = std::sinf(angle);

				float x = points3d[i].x;
				float y = points3d[i].y;
				float z = points3d[i].z;

				if (rz || e.isKeyDown(Keys::c))
					points3d[i] = { x * cos + - y *  sin, x * sin + y * cos, z};
				if(rx || e.isKeyDown(Keys::z))
					points3d[i] = { x, y * cos - z * sin, y * sin + z * cos};
				if(ry || e.isKeyDown(Keys::x))
					points3d[i] = { x * cos - z * sin, y, x * sin + z * cos };

				Vector2 p = points3d[i].projectAuto();
				points2d[i] = { p.x, p.y };
			}

			e.reduceAccumulatedTime();
		}

		if (e.isButtonDown(leftclick))
			angle += 0.05f * e.getDeltaTime();
		if (e.isButtonDown(rightclick))
			angle -= 0.05f * e.getDeltaTime();
		if (e.isKeyJustDown(space))
			angle = -angle;
		if (e.isKeyJustDown(Keys::r))
		{
			rx = !rx;
			ry = rz = false;
		}
		if (e.isKeyJustDown(Keys::t))
		{
			ry = !ry;
			rx = rz = false;
		}
		if (e.isKeyJustDown(Keys::y))
		{
			rz = !rz;
			rx = ry = false;
		}
		if (e.isKeyJustDown(Keys::b))
		{
			angle = 0.0f;
			rx = ry = rz = false;
			points3d[0] = { 200, 200, 200 };
			points3d[1] = { -200, 200, 200 };
			points3d[2] = { 200, -200, 200 };
			points3d[3] = { -200, -200, 200 };
			points3d[4] = { 200, 200, -200 };
			points3d[5] = { -200, 200, -200 };
			points3d[6] = { 200, -200, -200 };
			points3d[7] = { -200, -200, -200 };
			
		}



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
		
		textPos = { origin, origin };

		titleText.setText("angle: ");
		titleText.draw(textPos);
		textPos.x = origin + titleText.getW();

		angleText.setText(std::to_string(angle));
		if (angle == 0)
			angleText.changeColor(GREY);
		else
			angle > 0 ? angleText.changeColor(CYAN) : angleText.changeColor(PURPLE);
		angleText.draw(textPos);
		textPos.x = origin;
		textPos.y += titleText.getH();


		titleText.setText("X rotation: ");
		titleText.draw(textPos);
		textPos.x = origin + titleText.getW();
		rx ? trueText.draw(textPos) : falseText.draw(textPos);
		textPos.x = origin;
		textPos.y += titleText.getH();
		
		titleText.setText("Y rotation: ");
		titleText.draw(textPos);
		textPos.x = origin + titleText.getW();
		ry ? trueText.draw(textPos) : falseText.draw(textPos);
		textPos.x = origin;
		textPos.y += titleText.getH();

		titleText.setText("Z rotation: ");
		titleText.draw(textPos);
		textPos.x = origin + titleText.getW();
		rz ? trueText.draw(textPos) : falseText.draw(textPos);
		
		window.flip();

		SDL_Delay(2);
	}
}