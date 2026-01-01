#ifndef SLIB_NODE_H
#define SLIB_NODE_H

#include "slib_app.h"

namespace slib
{
	class Node : public Events
	{
	public:
		virtual void init() {}
		virtual void update() {}
		virtual void fixedUpdate() {}
		virtual void draw() {}

		static Node* currentScene;
	};
}

#endif