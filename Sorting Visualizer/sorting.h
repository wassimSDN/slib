#pragma once

#include <slib.h>

#define nbrElements 100
#define WIDTH 700.0f
#define HEIGHT 500.0f

namespace SortingVisualizer
{
	void init();
	void displayArray();
	void randomize();
	void bubbleSort();
	void mergeSort();
	void quickSort();
	void insertionSort();
	void selectionSort();

	enum SORT_TYPE
	{
		SORT_TYPE_NONE,
		SORT_TYPE_BUBBLE,
		SORT_TYPE_INSERTION
	};
}

