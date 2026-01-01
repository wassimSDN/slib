#include "../include/slib_scene.h"

namespace slib
{
	Scene::Scene(int w, int h) 
	{
		txt = SDL_CreateTexture(Window::renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, w, h);
	}

	void Scene::fixedUpdate()
	{
		for (Node* it : nodes)
			it->fixedUpdate();
	}

	void Scene::update() 
	{
		for (Node* it : nodes)
			it->update();
	}
	void Scene::draw()
	{
		SDL_SetRenderTarget(Window::renderer, txt);
		
		for (Node* it : nodes)
			it->draw();
			
		SDL_SetRenderTarget(Window::renderer, nullptr);
		SDL_RenderCopy(Window::renderer, txt, camera, nullptr);
	}
}