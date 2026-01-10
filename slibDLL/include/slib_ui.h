#pragma once

#include "slib_draw.h"
#include "slib_app.h"

namespace slib 
{
	enum BUTTON_STATE
	{
		BUTTON_STATE_NONE,
		BUTTON_STATE_HOVERED,
		BUTTON_STATE_CLICKED,
		BUTTON_STATE_COUNT
	};


	class Button : public Events
	{
	public:
		Button(const char* stateNoneFileName, const char* stateHoveredFileName, const char* stateClickedFileName, RectangleReal pos);
		void update();
		void draw();
	private:
		Text label;
		Texture image[BUTTON_STATE_COUNT];

	};

	class Toggle
	{

	};

	class Options
	{

	};

	class DropDown
	{

	};
}