#include <slib.h>

using namespace slib;

#include "sorting.h"

using namespace SortingVisualizer;

int main()
{
	Events e;
	e.setTicks(10);
	Window window("Snake Game", WIDTH, HEIGHT, WindowFlags::centered, WindowFlags::centered, WindowFlags::hidden);

	init();
	bool sort = false;
	SORT_TYPE type = SORT_TYPE_BUBBLE;


	window.show();
	while (true)
	{
		e.updateEvents();
		if (e.shouldQuit())
			break;
		while (e.ticking())
		{
			e.reduceAccumulatedTime();
		}

		if (e.isKeyJustDown(space))
		{
			randomize();
			sort = true;
		}

		if (sort)
		{
			switch (type)
			{
			case SORT_TYPE_BUBBLE:
				bubbleSort();
				break;
			case SORT_TYPE_INSERTION:
				insertionSort();
				break;
			}
		}

		window.setClearColor(CORN);
		window.clear();
		
		displayArray();

		window.flip();

		SDL_Delay(16);
	}
}