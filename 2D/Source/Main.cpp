#include "Renderer.h"

#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{

    Renderer r;

    r.Initialize();

    SDL_Window* window = r.CreateWindow(800, 600, "Game Engine");
    

    // create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    while (true)
    {
        // clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        // show screen
        SDL_RenderPresent(renderer);
    }

    return 0;
}