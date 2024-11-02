#include "Renderer.h"
#include "Framebuffer.h"
#include "PostProcess.h"
#include "Camera.h"
#include "Scene.h"

#include "Tracer.h"

#include "Image.h"
#include "Model.h"
#include "Actor.h"
#include "Transform.h"

#include "Input.h"

#include "ETime.h"
#include "MathUtils.h"
#include "Random.h"
//#include "Test.h"

#include "Plane.h"
#include "Triangle.h"

#include <SDL.h>
#include <iostream>
#include <memory>

int main(int argc, char* argv[])
{
    srand((unsigned int)time(NULL));

    Time time;


    Renderer r;

    //Camera camera(800, 600); //change later to r.m_width and r.m_height
    //camera.SetView(glm::vec3{ 0, 0, -50 }, glm::vec3{ 0 });
    //camera.setProjection(90.0f, 800.0f / 600, 0.1f, 200.0f);
    Transform cameraTransform{ {0, 0, -20 } };

    

    r.Initialize();

    r.CreateWindow(800, 600, "Game Engine");

    // create renderer
    //SDL_Renderer* renderer = SDL_CreateRenderer(r.m_window, -1, 0);
    
    //Framebuffer framebuffer(r, 800, 600);
    SetBlendMode(BlendMode::Normal);

    
    


    //model->SetColor({ 0, 255, 50, 255 });

    Transform transformT{ {0, 0, 0}, glm::vec3{0, 0, 0}, glm::vec3{ 2 } }; //{} and () are interchangable for calling a constructor
    
    std::vector<std::unique_ptr<Actor>> actors;

    

        Framebuffer framebuffer(r, 800, 600);

        Camera camera{ 70.0f, framebuffer.m_width / (float)framebuffer.m_height };

        camera.SetView({ 5,5,5 }, { 0, 0, 0 });
        //camera.SetView({ 0,0,-30 }, { 0, 0, 0 });

        Scene scene;



        std::shared_ptr<Material> gray = std::make_shared<Lambertian>(color3_t{ 0.5f });
        std::shared_ptr<Material> bloodRed = std::make_shared<Lambertian>(color3_t{ 0.7, 0, 0.05 });
        std::shared_ptr<Material> red = std::make_shared<Lambertian>(color3_t{ 1, 0, 0 });
        std::shared_ptr<Material> blue = std::make_shared<Lambertian>(color3_t{ 0, 0.5, 1 });
        std::shared_ptr<Material> green = std::make_shared<Lambertian>(color3_t{ 0, 1, 0.5 });
        std::shared_ptr<Material> orange = std::make_shared<Lambertian>(color3_t{ 1, 0.3, 0 }); 
        std::shared_ptr<Material> yellow = std::make_shared<Lambertian>(color3_t{ 1, 0.6, 0 }); 

        
        std::shared_ptr<Material> grayM = std::make_shared<Metal>(color3_t{ 0.5f }, 0.0f);
        std::shared_ptr<Material> bloodRedM = std::make_shared<Metal>(color3_t{ 0.7, 0, 0.05 }, 0.2f);
        std::shared_ptr<Material> redM = std::make_shared<Metal>(color3_t{ 1, 0, 0 }, 0.0f);
        std::shared_ptr<Material> blueM = std::make_shared<Metal>(color3_t{ 0, 0.65, 1 }, 0.3f);
        std::shared_ptr<Material> greenM = std::make_shared<Metal>(color3_t{ 0, 1, 0.65 }, 0.1f);
        std::shared_ptr<Material> lightM = std::make_shared<Metal>(color3_t{ 0.3, 0.3, 0.3 }, 0.1f);
        
        std::shared_ptr<Material> bloodRedE = std::make_shared<Emissive>(color3_t{ 0.7, 0, 10.05 }, 1.2f);
        std::shared_ptr<Material> redE = std::make_shared<Emissive>(color3_t{ 1, 0, 0 }, 11.0f);
        std::shared_ptr<Material> blueE = std::make_shared<Emissive>(color3_t{ 0.2, 0.5, 1 }, 13.3f);
        std::shared_ptr<Material> greenE = std::make_shared<Emissive>(color3_t{ 0, 1, 0.5 }, 13.1f);
        std::shared_ptr<Material> yellowE = std::make_shared<Emissive>(color3_t{ 1, 0.5, 0 }, 13.1f);
        std::shared_ptr<Material> orangeE = std::make_shared<Emissive>(color3_t{ 1, 0.1, 0 }, 13.1f); //green as 0.2?
        //std::shared_ptr<Material> lightE = std::make_shared<Emissive>(color3_t{ 0.8, 0.8, 0.8 }, 0.1f);
        std::shared_ptr<Material> lightE = std::make_shared<Emissive>(color3_t{ 1, 1, 1 }, 13.1f);

        
        
        std::shared_ptr<Material> bloodRedD = std::make_shared<Dielectric>(color3_t{ 0.7, 0, 0.05 }, 1.2f);
        std::shared_ptr<Material> redD = std::make_shared<Dielectric>(color3_t{ 0.8, 0.1, 0.1 }, 1.3f);
        std::shared_ptr<Material> blueD = std::make_shared<Dielectric>(color3_t{ 0, 0.3, 0.8 }, 1.3f);
        std::shared_ptr<Material> greenD = std::make_shared<Dielectric>(color3_t{ 0, 0.8, 0.3 }, 1.1f);
        std::shared_ptr<Material> lightD = std::make_shared<Dielectric>(color3_t{ 0.5, 0.5, 0.5 }, 1.8f);


        std::vector<std::shared_ptr<Material>> materials;

        //materials.push_back(gray);
        materials.push_back(bloodRed);
        //materials.push_back(red);
        materials.push_back(blue);
        materials.push_back(green);
        materials.push_back(orange);
        materials.push_back(yellow);

        materials.push_back(bloodRedM);
        //materials.push_back(redM);
        materials.push_back(blueM);
        materials.push_back(greenM);
        materials.push_back(lightM);
        
        materials.push_back(bloodRedE);
        //materials.push_back(redE);
        materials.push_back(blueE);
        materials.push_back(greenE);
        //materials.push_back(yellowE);
        materials.push_back(orangeE);
        materials.push_back(lightE);
        
        
        materials.push_back(bloodRedD);
        //materials.push_back(redD);
        materials.push_back(blueD);
        materials.push_back(greenD);
        materials.push_back(lightD);



        //for (int i = 0; i <= 0; i++)
        //{
        //    int matNumber = random(0, materials.size());
        //
        //
        //    auto object = std::make_unique<Sphere>(randomf(glm::vec3{ -15 }, glm::vec3{ 15 }), randomf(1, 5), materials[matNumber]);
        //    //auto object = std::make_unique<Sphere>(random(glm::vec3{ -15 }, glm::vec3{ 15 }), randomf(1, 5), blue);
        //    scene.AddObject(std::move(object));
        //
        //}

        std::unique_ptr<SceneObject> object = std::make_unique<Triangle>(glm::vec3{ -5, 0, 0 }, glm::vec3{ 5, 0, 0 }, glm::vec3{ 0, 5, 0 }, bloodRed);
        //std::unique_ptr<SceneObject> object = std::make_unique<Triangle>(glm::vec3{ 5, 6, 1 }, glm::vec3{ -5, 3, 1 }, glm::vec3{ 2, 5, 1 }, bloodRed);
        //scene.AddObject(std::move(object));

        Model teapot = Model(bloodRed);
        teapot.Load("cube-2.obj");
        std::unique_ptr<SceneObject> tea = std::make_unique<Model>(teapot.m_vertices, bloodRed);
        scene.AddObject(std::move(tea));
        //model->SetColor({ 0, 255, 0, 255 });


        std::unique_ptr<SceneObject> lightSource = std::make_unique<Sphere>(randomf(glm::vec3{ -15 }, glm::vec3{ 15 }), randomf(1, 5), lightE);
        scene.AddObject(std::move(lightSource));


        //std::shared_ptr<Material> material = std::make_shared<Lambertian>(color3_t{ 1, 0, 1 });
        //std::unique_ptr<Sphere> object = std::make_unique<Sphere>(glm::vec3{ 0, 0, 40 }, 2.0f, material);
        //scene.AddObject(std::move(object));

        std::shared_ptr<Material> material2 = std::make_shared<Lambertian>(color3_t{ 0, 1, 1 });
        auto plane = std::make_unique<Plane>(glm::vec3{ 0, -30, 0 }, glm::vec3{ 0, 1, 0 }, gray);
        scene.AddObject(std::move(plane));





        framebuffer.Clear(color_t{ 0, 200, 200, 255 });

        //scene.Render(framebuffer, camera);
        scene.Render(framebuffer, camera, 100, 5);







    bool quit = false;
    while (!quit) //main loop
    {
        //UPDATE
        time.Tick();


        //Tracer tracer;
        
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
        


        framebuffer.Update(r);

        r.CopyFramebuffer(framebuffer);
        //r = framebuffer;


            // show screen
        SDL_RenderPresent(r.m_renderer);
        
    }

    return 0;
}