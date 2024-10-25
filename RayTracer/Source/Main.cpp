#include "Renderer.h"
#include "Framebuffer.h"
#include "PostProcess.h"
#include "Camera.h"

#include "Image.h"
#include "Model.h"
#include "Actor.h"
#include "Transform.h"

#include "Input.h"

#include "ETime.h"
#include "MathUtils.h"
#include "Random.h"
//#include "Test.h"

#include <SDL.h>
#include <iostream>
#include <memory>

int main(int argc, char* argv[])
{
    Time time;

    Input input;
    input.Initialize();

    Renderer r;

    Camera camera(800, 600); //change later to r.m_width and r.m_height
    camera.SetView(glm::vec3{ 0, 0, -50 }, glm::vec3{ 0 });
    camera.setProjection(90.0f, 800.0f / 600, 0.1f, 200.0f);
    Transform cameraTransform{ {0, 0, -20 } };

    

    r.Initialize();

    r.CreateWindow(800, 600, "Game Engine");

    // create renderer
    //SDL_Renderer* renderer = SDL_CreateRenderer(r.m_window, -1, 0);
    
    Framebuffer framebuffer(r, 800, 600);
    SetBlendMode(BlendMode::Normal);

    
    vertices_t vertices = { { -5, 5, 0 }, { 5, 5, 0 }, {-5, -5, 0 } };
    Model modelT(vertices, { 0, 255, 0, 255 });

    std::shared_ptr<Model> model = std::make_shared<Model>();
    model->Load("teapot.obj");
    model->SetColor({ 0, 255, 0, 255 });

    //model->SetColor({ 0, 255, 50, 255 });

    Transform transformT{ {0, 0, 0}, glm::vec3{0, 0, 0}, glm::vec3{ 2 } }; //{} and () are interchangable for calling a constructor
    
    std::vector<std::unique_ptr<Actor>> actors;

    for (int i = 0; i < 4; i++)
    {

        Transform transform{ {randomf(-10.0f, 10.0f), random(-10.0f, 10.0f), random(-10.0f, 10.0f)}, glm::vec3{0, 0, 0}, glm::vec3{1}}; //{} and () are interchangable for calling a constructor
    
        std::unique_ptr<Actor> actor = std::make_unique<Actor>(transform, model);
        actor->SetColor({ 0, 150, 255, 255 });
        actors.push_back(std::move(actor));

    }





    bool quit = false;
    while (!quit) //main loop
    {
        //UPDATE
        time.Tick();
        input.Update();

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


        //RENDER

        // clear screen
        //SDL_SetRenderDrawColor(r.m_renderer, 0, 0, 0, 0);
        //SDL_RenderClear(r.m_renderer);

        framebuffer.Clear(color_t{ 0, 0, 0, 255 });

       // int ticks = SDL_GetTicks(); 
       // float time = ticks * 0.001f;
           
        
        //get mouse input
        int mx, my;
        SDL_GetMouseState(&mx, &my);

#pragma region framebuffer_test   
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

#pragma endregion

        //for (int i = 0; i < 5; i++)
        //{
        //    Image image;
        //    //image.Load("diamond.png");
        //    //image.Load("transparentChuuya.png");
        //    image.Load("chuuya.png");
        //    framebuffer.DrawImage(rand() % 700, rand() % 700, image);
        //
        //}

#pragma region images
        //Image image;
        //image.Load("scenic.jpg");
        //
        //Image imageAlpha;
        //imageAlpha.Load("colors.png");
        //PostProcess::Alpha(imageAlpha.m_buffer, 168);
        //
        //Image imagePerson;
        //imagePerson.Load("chuuya.png");
        //
        //SetBlendMode(BlendMode::Normal);
        //framebuffer.DrawImage(10, 10, image);
        //framebuffer.DrawImage(100, 100, imagePerson);
        //SetBlendMode(BlendMode::Multiply);
        //framebuffer.DrawImage(mx - 300, my - 200, imageAlpha);
#pragma endregion

        


        //glm::mat4 modelMatrix = glm::mat4(1.0f);
        //glm::mat4 translate = glm::translate(modelMatrix, glm::vec3(40.0f, 40.0f, 0.0f));
        //glm::mat4 scale = glm::scale(modelMatrix, glm::vec3(5)); //vec3(2) is the same as vec3(2, 2, 2)
        //glm::mat4 rotate = glm::rotate(modelMatrix, glm::radians(time * 90), glm::vec3{1, 1, 1});
        //modelMatrix = translate * scale * rotate;
        //modelMatrix was the transform

        glm::vec3 direction{ 0 };
        if (input.GetKeyDown(SDL_SCANCODE_RIGHT)) direction.x = 1;
        if (input.GetKeyDown(SDL_SCANCODE_LEFT)) direction.x = -1;
        if (input.GetKeyDown(SDL_SCANCODE_UP)) direction.y = -1;
        if (input.GetKeyDown(SDL_SCANCODE_DOWN)) direction.y = 1;
        if (input.GetKeyDown(SDL_SCANCODE_W)) direction.z = 1;
        if (input.GetKeyDown(SDL_SCANCODE_S)) direction.z = -1;

        cameraTransform.rotation.y = input.GetMousePositionDelta().x * 0.5f;
        //cameraTransform.rotation.x = input.GetMousePositionDelta().y * 0.5f;

        glm::vec3 offset = cameraTransform.GetMatrix()* glm::vec4{ direction, 0 };


        cameraTransform.position += offset * 70.0f * time.GetDeltaTime();
        camera.SetView(cameraTransform.position, cameraTransform.position + cameraTransform.GetForward());


        //transform.rotation.z += 90 * time.GetDeltaTime();
        //modelT.Draw(framebuffer, transformT.GetMatrix(), camera);



        

        //model->Draw(framebuffer, transform.GetMatrix(), camera);
        for (auto& actor : actors)
        {
            actor->Draw(framebuffer, camera);

        }



#pragma region post_process


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
        //PostProcess::Monochrome(framebuffer.m_buffer);


        //PostProcess::Halfboss(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::LSD(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);

#pragma endregion

        //DISPLAY

        framebuffer.Update(r);

        r.CopyFramebuffer(framebuffer);
        //r = framebuffer;


            // show screen
        SDL_RenderPresent(r.m_renderer);
        
    }

    return 0;
}