#include "Renderer.h"

#include <SDL.h>

bool Renderer::Initialize()
{
    // initialize SDL
    int result = SDL_Init(SDL_INIT_VIDEO);
    if (result < 0)
    {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void Renderer::CreateWindow(float height, float width, const char* name)
{
    // create window
    // returns pointer to window if successful or nullptr if failed
    m_window = SDL_CreateWindow(name,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        height, width,
        SDL_WINDOW_SHOWN);
    if (m_window == nullptr)
    {
        std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        //return nullptr;
    }


    // create renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);

}

void Renderer::CopyFramebuffer(const Framebuffer framebuffer)
{
    SDL_RenderCopy(m_renderer, framebuffer.m_texture, NULL, NULL);
}

void Renderer::operator=(const Framebuffer& framebuffer)
{
    SDL_RenderCopy(m_renderer, framebuffer.m_texture, NULL, NULL);
}
