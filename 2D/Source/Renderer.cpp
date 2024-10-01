#include "Renderer.h"

#include <SDL.h>

bool Renderer::Initialize()
{
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

SDL_Window* Renderer::CreateWindow(float height, float width, const char* name)
{
    // create window
    // returns pointer to window if successful or nullptr if failed
    SDL_Window* window = SDL_CreateWindow(name,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        height, width,
        SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return nullptr;
    }
    return window;
}
