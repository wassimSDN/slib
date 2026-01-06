#include <vector>
#include <ctime>
#include <iostream>

#include "sorting.h"



namespace SortingVisualizer
{
	std::array<float, nbrElements> array;
	float w = WIDTH / (float)nbrElements;
	float h = HEIGHT / (float)nbrElements;

	void init()
	{
		for (int i = 0; i < array.size(); i++)
		{
			array[i] = h * i + h;
		}

		srand(time(nullptr));
	}

	void displayArray()
	{
		for (int i = 0; i < array.size(); i++)
		{
			slib::RectangleReal rect = { w * (float)i, (float)HEIGHT - array[i], w, array[i]};
			rect.draw();
		}
	}

	void randomize()
	{
		for (int i = 0; i < array.size(); i++)
		{
			int other = std::rand() % (array.size());
			std::swap(array[i], array[other]);
		}
	}
	void bubbleSort()
	{
		static int i = 0;
		static int j = 0;

		for (i; i < array.size(); ++i)
		{
			for (j = 0; j + 1 < array.size() - i; ++j)
			{
				if (array[j] > array[j + 1])
				{
					std::swap(array[j], array[j + 1]);
				}
			}
			return;
		}
	}

	void insertionSort()
	{
		static int i = 1;
		static int j = 0;

		for (i; i < array.size(); i++)
		{
			int key = array[i];
			j = i - 1;

			while (j >= 0 && array[j] > key)
			{
				array[j + 1] = array[j];
				--j;
			}

			i++;
			array[j + 1] = key;
			return;
		}
	}
}