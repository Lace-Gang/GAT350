#include "Renderer.h"
#include "Framebuffer.h"
#include "MathUtils.h"
#include "Image.h"
#include "PostProcess.h"

#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{

    Renderer r;

    r.Initialize();

    r.CreateWindow(800, 600, "Game Engine");

    // create renderer
    //SDL_Renderer* renderer = SDL_CreateRenderer(r.m_window, -1, 0);
    
    Framebuffer framebuffer(r, 800, 600);

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
        //framebuffer.DrawLine(40, 40, 500, 500, { (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255) });

        //framebuffer.DrawTriangle(10, 10, 50, 20, 30, 60, { 255, 255, 255, 255 });
        //framebuffer.DrawCircle(200, 200, 30, { 255, 255, 255, 255 });

            //get mouse input
        //int mx, my;
        //SDL_GetMouseState(&mx, &my);
        //
        //framebuffer.DrawLinearCurve(100, 100, mx, my, { 255, 255, 0, 255 });
        //framebuffer.DrawQuadraticCurve(100, 200, 200, 100, mx, my, { 0, 255, 255, 255 });
        //framebuffer.DrawCubicCurve(100, 200, 100, 100, mx, my, 200, 200, { 255, 0, 0, 255 });
        //
        //int ticks = SDL_GetTicks();
        //float time = ticks * 0.001f;
        //float t = std::abs(std::sin(time));
        //int x, y;
        //CubicPoint(100, 200, 100, 100, mx, my, 200, 200, t, x, y);
        //framebuffer.DrawRect(y-5, x-5, 10, 10, { 0, 255, 0, 255 });

        //for (int i = 0; i < 5; i++)
        //{
        //    Image image;
        //    //image.Load("diamond.png");
        //    //image.Load("transparentChuuya.png");
        //    image.Load("chuuya.png");
        //    framebuffer.DrawImage(rand() % 700, rand() % 700, image);
        //
        //}

        Image image;
        image.Load("scenic.jpg");
        framebuffer.DrawImage(10, 10, image);


        //PostProcess::Invert(framebuffer.m_buffer);
        //PostProcess::Monochrome(framebuffer.m_buffer);
        //PostProcess::Brightness(framebuffer.m_buffer, 120);
        //PostProcess::ColorBalance(framebuffer.m_buffer, 90, 30, 40);
        //PostProcess::Noise(framebuffer.m_buffer, 60);
        //PostProcess::Threshold(framebuffer.m_buffer, 60);
        //PostProcess::Posterize(framebuffer.m_buffer, 10);

        //PostProcess::BoxBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::GaussianBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Sharpen(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Edge(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height, 150);
        //PostProcess::Emboss(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);

        //PostProcess::Halfboss(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::LSD(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);

        framebuffer.Update(r);

        r.CopyFramebuffer(framebuffer);
        //r = framebuffer;


            // show screen
        SDL_RenderPresent(r.m_renderer);
        
    }

    return 0;
}