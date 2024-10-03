#pragma once

#include "Framebuffer.h"

#include <iostream>
#include<SDL.h>

class Renderer
{
public:
	bool Initialize();

	void CreateWindow(float height, float width, const char* name);

	void CopyFramebuffer(const Framebuffer framebuffer);

	void operator = (const class Framebuffer& framebuffer);

	//friend class Framebuffer;
public:
	

	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };
};