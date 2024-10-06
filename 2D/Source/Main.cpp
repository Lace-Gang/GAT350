#include "Renderer.h"
#include "Framebuffer.h"

#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{

    Renderer r;

    r.Initialize();

    r.CreateWindow(800, 600, "Game Engine");

    // create renderer
    //SDL_Renderer* renderer = SDL_CreateRenderer(r.m_window, -1, 0);
    
    Framebuffer framebuffer(r, 400, 300);

    bool quit = false;
    while (!quit)
    {
        //exit program
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
        }


        // clear screen
        //SDL_SetRenderDrawColor(r.m_renderer, 0, 0, 0, 0);
        //SDL_RenderClear(r.m_renderer);

        framebuffer.Clear(color_t{ 0, 0, 0, 255 });

        
        for (int i = 0; i < 100; i++)
        {
            int x = rand() % 400;
            int y = rand() % 300;
            int x2 = rand() % 400;
            int y2 = rand() % 300;
            //std::cout << x << std::endl;
            //std::cout << y << std::endl;
            //framebuffer.DrawPoint(x, y, { 255, 255, 255, 255 });

            //framebuffer.DrawLine(x, y, x2, y2, { (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255) });
        }
        //framebuffer.DrawRect(10, 10, 50, 50, { 0, 255, 0, 255 });
        framebuffer.DrawLine(40, 40, 500, 500, { (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255) });

        framebuffer.DrawTriangle(10, 10, 50, 20, 30, 60, { 255, 255, 255, 255 });
        framebuffer.DrawCircle(200, 200, 30, { 255, 255, 255, 255 });

        framebuffer.Update(r);
        r.CopyFramebuffer(framebuffer);


        // show screen
        SDL_RenderPresent(r.m_renderer);
        
    }

    return 0;
}