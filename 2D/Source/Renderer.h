#pragma once

#include <iostream>
#include<SDL.h>

class Renderer
{
public:
	bool Initialize();

	SDL_Window* CreateWindow(float height, float width, const char* name);

private:

};