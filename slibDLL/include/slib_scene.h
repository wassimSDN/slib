#ifndef SLIB_SCENE_H
#define SLIB_SCENE_H

#include <vector>

#include "slib_app.h"
#include "slib_hitbox.h"
#include "slib_node.h"

namespace slib
{
	class Scene
	{
	public:
		Scene() {}
		Scene(int w, int h);
		virtual void update();
		virtual void fixedUpdate();
		virtual void draw();
		int w = 0;
		int h = 0;
		slib::Rectangle camera = { 0, 0, 0, 0 };
		SDL_Texture* txt = nullptr;
		std::vector<Node*> nodes;
	};

}


#endif