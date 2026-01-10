#include <vector>

#include <slib.h>

using slib::WindowFlags;

int main()
{
	slib::Events e;
	e.setTicks(10);
	slib::Window window("Circle Thingy", 1920 / std::sqrt(2), 1080 / std::sqrt(2), WindowFlags::centered, WindowFlags::centered, WindowFlags::resizable);

	std::vector<slib::CircleReal> p;

	

	slib:: Text debug = { "", 50 };
	double textUpdate = 0;
	float constraint = 10;

	slib::hideCursor();
	std::string add = "";
	std::string fps = "";
	double frameTimeWait = 0;

	while (!e.shouldQuit())
	{
		e.updateEvents();

		

		while (e.ticking())
		{


			e.reduceAccumulatedTime();
		}

		frameTimeWait += e.getDeltaTime();
		while (frameTimeWait >= 1.0)
		{
			fps = "fps: " + std::to_string(1.0 / e.getDeltaTime());
			frameTimeWait -= 1.0;
		}

		if (e.isWheelUp())
		{
			constraint++;
			for (auto& it : p)
				it.setRadius(constraint);
			add = "\nscrolling up";
		}
		else if (e.isWheelDown() && constraint > 1)
		{
			constraint--;
			for (auto& it : p)
				it.setRadius(constraint);
			add = "\nscrolling down";
		}






		debug.setText(fps + '\n' + std::to_string(p.size()) + add);

		window.setClearColor({ 41, 41, 51, 255 });
		window.clear();

		if (e.isButtonDown(slib::MouseButtons::leftclick))
		{	
			if (p.size() > 2)
			{
				slib::Vector2 vec = p[p.size() - 2].getCenterPos() - p[p.size() - 1].getCenterPos();
				vec = vec.normalise() * p[p.size() - 1].getRadius() * 1.2f;
				p.push_back({ p[p.size() - 1].getCenterX() - vec.x, p[p.size() - 1].getCenterY() - vec.y, constraint });
			}
			else
			{
				p.push_back({ -constraint, -constraint, constraint });
			}
		}

		if (e.isButtonDown(slib::MouseButtons::rightclick) && p.size() > 1){
			p.pop_back();
		}
		
		for (int i = 1; i < p.size(); i++)
		{
			slib::Vector2 vec = p[i].getCenterPos() - p[i - 1].getCenterPos();
			vec = vec.normalise() * p[i - 1].getRadius() * 1.2f;
			p[i].setCenterX(p[i - 1].getCenterX() + vec.x);
			p[i].setCenterY(p[i - 1].getCenterY() + vec.y);

		}

		if (e.isKeyDown(slib::Keys::space))
		{
			if (p.size() > 2)
			{
				slib::Vector2 vec = fromToV2(p[0].getCenterPos(), p[p.size() - 1].getCenterPos());
				p[0].add(vec.normalise());
			}
		}
		else
		{
			if (p.size() > 0)
			{
				p[0].setCenterX(e.getMouseX());
				p[0].setCenterY(e.getMouseY());
			}
		}



		for (auto& it : p)
		{
			slib::RectangleReal r = { it.getCenterX() - it.getRadius(), it.getCenterY() - it.getRadius(), it.getRadius() * 2.0f, 2.0f *  it.getRadius()};
			r.drawFilled();
			//it.draw(slib::WHITE);
		}

		debug.draw({ 50, 50 });

		window.flip();

		SDL_Delay(1);
	}
}