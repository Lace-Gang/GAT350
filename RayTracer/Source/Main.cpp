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



void InitScene(Scene& scene);
void CornellScene(Scene& scene, Camera& camera);
void FinalScene(Scene& scene, Camera& camera);
void InitScene01(Scene& scene, Camera& camera);


int main(int argc, char* argv[])
{
    srand((unsigned int)time(NULL));

    Time time;


    Renderer r;

    

    

    r.Initialize();

    r.CreateWindow(800, 600, "Game Engine");

    // create renderer
    //SDL_Renderer* renderer = SDL_CreateRenderer(r.m_window, -1, 0);
    
    //Framebuffer framebuffer(r, 800, 600);
    SetBlendMode(BlendMode::Normal);

    
    


    //model->SetColor({ 0, 255, 50, 255 });

    Transform transformT{ {0, 0, 0}, glm::vec3{0, 0, 0}, glm::vec3{ 2 } }; //{} and () are interchangable for calling a constructor
    
    //std::vector<std::unique_ptr<Actor>> actors;

    

        Framebuffer framebuffer(r, 800, 600);

        Camera camera{ 70.0f, framebuffer.m_width / (float)framebuffer.m_height };

        //camera.SetView({ 5,5,5 }, { 0, 0, 0 });
        camera.SetView({ 10, 5, 30 }, { 0, 0, 0 });
        //camera.SetView({ 0,0,-30 }, { 0, 0, 0 });

        Scene scene;
        //InitScene(scene);
        //CornellScene(scene, camera);
        //InitScene01(scene, camera);
        FinalScene(scene, camera);



        




        //render

        framebuffer.Clear(color_t{ 0, 200, 200, 255 });
        scene.Update();
        //scene.Render(framebuffer, camera);
        //scene.Render(framebuffer, camera, 10, 5);
        scene.Render(framebuffer, camera, 100, 10);
        //scene.Render(framebuffer, camera, 200, 6);







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





#pragma region InitScene

void InitScene(Scene& scene)
{
    //scene.SetSky(HSVtoRGB(240, 1, 0.5), HSVtoRGB(240, 1, 1));
    
    //Camera camera(800, 600); //change later to r.m_width and r.m_height
    //camera.SetView(glm::vec3{ 0, 0, -50 }, glm::vec3{ 0 });
    //camera.setProjection(90.0f, 800.0f / 600, 0.1f, 200.0f);
    Transform cameraTransform{ {0, 0, -20 } };

    std::shared_ptr<Material> gray = std::make_shared<Lambertian>(color3_t{ 0.25f });
    std::shared_ptr<Material> bloodRed = std::make_shared<Lambertian>(color3_t{ 0.7, 0, 0.05 });
    std::shared_ptr<Material> red = std::make_shared<Lambertian>(color3_t{ 1, 0, 0 });
    std::shared_ptr<Material> blue = std::make_shared<Lambertian>(color3_t{ 0, 0.5, 1 });
    std::shared_ptr<Material> green = std::make_shared<Lambertian>(color3_t{ 0, 1, 0.5 });
    std::shared_ptr<Material> orange = std::make_shared<Lambertian>(color3_t{ 1, 0.3, 0 });
    std::shared_ptr<Material> yellow = std::make_shared<Lambertian>(color3_t{ 1, 0.6, 0 });


    std::shared_ptr<Material> grayM = std::make_shared<Metal>(color3_t{ 0.5f }, 0.0f);
    std::shared_ptr<Material> bloodRedM = std::make_shared<Metal>(color3_t{ 0.7, 0, 0.05 }, 0.3f);
    std::shared_ptr<Material> redM = std::make_shared<Metal>(color3_t{ 1, 0, 0 }, 0.0f);
    std::shared_ptr<Material> blueM = std::make_shared<Metal>(color3_t{ 0, 0.65, 1 }, 0.1f);
    std::shared_ptr<Material> greenM = std::make_shared<Metal>(color3_t{ 0, 1, 0.65 }, 0.1f);
    std::shared_ptr<Material> DarkM = std::make_shared<Metal>(color3_t{ 0.3, 0.3, 0.3 }, 0.1f);
    std::shared_ptr<Material> lightM = std::make_shared<Metal>(color3_t{ 0.8, 0.8, 0.8 }, 0.01f);

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
    std::shared_ptr<Material> yellowD = std::make_shared<Dielectric>(color3_t{ 1, 0.9, 0.0 }, 1.1f);
    std::shared_ptr<Material> orangeD = std::make_shared<Dielectric>(color3_t{ 1, 0.5, 0.0 }, 1.1f);
    std::shared_ptr<Material> DarkD = std::make_shared<Dielectric>(color3_t{ 0.5, 0.5, 0.5 }, 1.8f);
    std::shared_ptr<Material> lightD = std::make_shared<Dielectric>(color3_t{ 0.9, 0.9, 0.9 }, 1.8f);


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
    materials.push_back(DarkM);
    materials.push_back(lightM);

    materials.push_back(bloodRedE);
    //materials.push_back(redE);
    materials.push_back(blueE);
    materials.push_back(greenE);
    //materials.push_back(yellowE);
    materials.push_back(orangeE);
    materials.push_back(lightE);


    materials.push_back(bloodRedD);
    materials.push_back(redD);
    materials.push_back(blueD);
    materials.push_back(greenD);
    materials.push_back(yellowD);
    materials.push_back(orangeD);
    materials.push_back(DarkD);
    materials.push_back(lightD);



    for (int i = 0; i <= 7; i++)
    {
        int matNumber = random(0, materials.size());
        auto material = materials[matNumber];
    
        //auto object = std::make_unique<Sphere>(randomf(glm::vec3{ -15 }, glm::vec3{ 15 }), randomf(1, 5), materials[matNumber]);
        auto object = std::make_unique<Sphere>(Transform{ glm::vec3{ randomf(glm::vec3{ -15 }, glm::vec3{ 15 }) } }, 2.0f, materials[matNumber]);            //auto object = std::make_unique<Sphere>(random(glm::vec3{ -15 }, glm::vec3{ 15 }), randomf(1, 5), blue);
        //auto object = std::make_unique<Sphere>(Transform{ glm::vec3{ randomf(glm::vec3{ -15 }, glm::vec3{ 15 }) } }, 2.0f, yellowD);            //auto object = std::make_unique<Sphere>(random(glm::vec3{ -15 }, glm::vec3{ 15 }), randomf(1, 5), blue);
        scene.AddObject(std::move(object));
    
    }

    auto object = std::make_unique<Sphere>(Transform{ glm::vec3{ randomf(glm::vec3{ -15 }, glm::vec3{ 15 }) } }, 2.0f, lightE);   
    //scene.AddObject(std::move(object));

    //std::unique_ptr<SceneObject> tri = std::make_unique<Triangle>(glm::vec3{ -5, 0, 0 }, glm::vec3{ 5, 0, 0 }, glm::vec3{ 0, 5, 0 }, bloodRed);
    //std::unique_ptr<SceneObject> tri = std::make_unique<Triangle>(glm::vec3{ 5, 6, 1 }, glm::vec3{ -5, 3, 1 }, glm::vec3{ 2, 5, 1 }, bloodRed);
    //std::unique_ptr<SceneObject> tri = std::make_unique<Triangle>(Transform(glm::vec3{ 5, 6, 1 }, glm::vec3{ -5, 3, 1 }, glm::vec3{ 2, 5, 1 }), bloodRed);
    //scene.AddObject(std::move(tri));

    //Model teapot = Model(bloodRed);
    //teapot.Load("models/cube-2.obj");
    //teapot.Load("models/cube.obj");
    std::unique_ptr<Model> tea = std::make_unique<Model>(Transform(glm::vec3{ 0 }, glm::vec3{0, 40, 0}, glm::vec3{4}), orangeE);
    tea->Load("models/cube.obj");
    scene.AddObject(std::move(tea));


    //std::unique_ptr<SceneObject> lightSource = std::make_unique<Sphere>(randomf(glm::vec3{ -15 }, glm::vec3{ 15 }), randomf(1, 5), lightE);
    //scene.AddObject(std::move(lightSource));


    //std::shared_ptr<Material> material = std::make_shared<Lambertian>(color3_t{ 1, 0, 1 });
    //std::unique_ptr<Sphere> object = std::make_unique<Sphere>(glm::vec3{ 0, 0, 40 }, 2.0f, material);
    //scene.AddObject(std::move(object));

   std::shared_ptr<Material> material2 = std::make_shared<Lambertian>(color3_t{ 0, 1, 1 });
   std::shared_ptr<Material> material3 = std::make_shared<Lambertian>(HSVtoRGB(randomf(0, 360), 1.0f, 1.0f));
   //auto plane = std::make_unique<Plane>(glm::vec3{ 0, -30, 0 }, glm::vec3{ 0, 1, 0 }, gray);
   //auto plane = std::make_unique<Plane>(Transform(glm::vec3{ 0, -2, 0 }, glm::vec3{ 0, 0, 20 }), material3);
   auto plane = std::make_unique<Plane>(Transform(glm::vec3{ 0, -20, 0 }, glm::vec3{ 0, 0, 0 }), gray);
   scene.AddObject(std::move(plane));
}

#pragma endregion


#pragma region cornellScene
void CornellScene(Scene& scene, Camera& camera)
{
    //set camera
    camera.SetView({ 0, 5, 10 }, { 0, 5, 0 });
    //camera.SetView({ 0, 5, 0 }, { 0, 5, -10 });



    //make materials
    std::shared_ptr<Material> redL = std::make_shared<Lambertian>(color3_t{ 1, 0, 0 });
    std::shared_ptr<Material> greenL = std::make_shared<Lambertian>(color3_t{ 0, 1, 0 });
    std::shared_ptr<Material> whiteL = std::make_shared<Lambertian>(color3_t{ 1, 1, 1 });

    std::shared_ptr<Material> lightE = std::make_shared<Emissive>(color3_t{ 1, 1, 1 }, 13.1f);



    //make planes
    auto floor = std::make_unique<Plane>(Transform(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 0, 0 }), whiteL);
    auto ceiling = std::make_unique<Plane>(Transform(glm::vec3{ 0, 11, 0 }, glm::vec3{ 180, 0, 0 }), whiteL);
    auto backWall = std::make_unique<Plane>(Transform(glm::vec3{ 0, 0, -5 }, glm::vec3{ 0, 90, 90 }), whiteL);
    auto leftWall = std::make_unique<Plane>(Transform(glm::vec3{ 6, 0, 0 }, glm::vec3{ 0, 0, 90 }), redL);
    auto rightWall = std::make_unique<Plane>(Transform(glm::vec3{ -6, 0, 0 }, glm::vec3{ 0, 180, 90 }), greenL);
    auto hiddenWall = std::make_unique<Plane>(Transform(glm::vec3{ 0, 0, 11 }, glm::vec3{ 180, -90, -90 }), whiteL);

    //add planes
    scene.AddObject(std::move(floor));
    scene.AddObject(std::move(ceiling));
    scene.AddObject(std::move(backWall));
    scene.AddObject(std::move(leftWall));
    scene.AddObject(std::move(rightWall));
    scene.AddObject(std::move(hiddenWall));

    //make light
    //std::unique_ptr<Model> light = std::make_unique<Model>(Transform(glm::vec3{ 0, 11.99, 0 }, glm::vec3{ 0 }, glm::vec3{ 2 }), lightE);
    std::unique_ptr<Model> light = std::make_unique<Model>(Transform(glm::vec3{ 0, 12.32, 2 }, glm::vec3{ 0 }, glm::vec3{ 3 }), lightE);
    light->Load("models/cube.obj");


    //add light
    scene.AddObject(std::move(light));


    //make objects
    std::unique_ptr<Model> rect = std::make_unique<Model>(Transform(glm::vec3{ 2, 3, -3 }, glm::vec3{ 0, 25, 0 }, glm::vec3{ 3, 8, 3 }), whiteL);
    rect->Load("models/cube.obj");
   auto globe = std::make_unique<Sphere>(Transform{ glm::vec3{ -3, 2, -2 } }, 2.0f, whiteL);

    //add objects
    scene.AddObject(std::move(rect));
    scene.AddObject(std::move(globe));


    //temp

    auto object = std::make_unique<Sphere>(Transform{ glm::vec3{ 0, 0, 1 } }, 2.0f, lightE);            //auto object = std::make_unique<Sphere>(random(glm::vec3{ -15 }, glm::vec3{ 15 }), randomf(1, 5), blue);
    //scene.AddObject(std::move(object));
}
#pragma endregion


#pragma region FinalScene
void FinalScene(Scene& scene, Camera& camera)
{
    //Camera position
    camera.SetView({ 0, 15, -30 }, { 0, 0, 0 });

    //Sky
    //scene.SetSky({ 0, 0.001, 0.5 }, { 0.1, 0, 0 });
    //scene.SetSky({ 0.01, 0, 0.001 }, { 0.1, 0, 0 });
    //scene.SetSky({ 0.1, 0, 0.01 }, { 0.1, 0, 0 });
    //scene.SetSky({ 0.1, 0, 0.01 }, { 0, 0, 0.1 });
    //scene.SetSky({ 0, 0, 0.05 }, { 0.3, 0.3, 0.3 });
    scene.SetSky({ 0, 0, 0.05 }, { 0.6, 0.6, 0.6 });



    //Make Materials
        //lambertians
    //std::shared_ptr<Material> whiteL = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
    std::shared_ptr<Material> passionFruitL = std::make_shared<Lambertian>(color3_t{ 0.75, 0.0, 0.25 });
    std::shared_ptr<Material> pomegranateL = std::make_shared<Lambertian>(color3_t{ 0.8, 0.0, 0.05 });
    std::shared_ptr<Material> grapeL = std::make_shared<Lambertian>(color3_t{ 0.1, 0.01, 0.8 });


        //Metals
    //std::shared_ptr<Material> floorL = std::make_shared<Metal>(color3_t{ 0.11, 0.05, 0.15 }, 0.4f);
    //std::shared_ptr<Material> floorL = std::make_shared<Metal>(color3_t{ 0.055, 0.025, 0.075 }, 0.2f);
    std::shared_ptr<Material> leavesM = std::make_shared<Metal>(color3_t{ 0.0, 0.4, 0.08 }, 0.1f);
    std::shared_ptr<Material> whiteSeedM = std::make_shared<Metal>(color3_t{ 1, 1, 0.6 }, 0.01f);
    std::shared_ptr<Material> blackSeedM = std::make_shared<Metal>(color3_t{ 0.1, 0.1, 0.06 }, 0.04f);
    std::shared_ptr<Material> grapeM = std::make_shared<Metal>(color3_t{ 0.07, 0.01, 0.8 }, 0.5f);


        //Dielectric
    //std::shared_ptr<Material> floorL = std::make_shared<Dielectric>(color3_t{ 0.075, 0.0, 0.025 }, 0.2f);
    //std::shared_ptr<Material> floorL = std::make_shared<Dielectric>(color3_t{ 0.075, 0.0, 0.015 }, 0.2f);
    std::shared_ptr<Material> floorD = std::make_shared<Dielectric>(color3_t{ 0.11, 0.05, 0.15 }, 0.2f);
    //std::shared_ptr<Material> floorL = std::make_shared<Dielectric>(color3_t{ 0.075, 0.0, 0.0 }, 0.2f);
    //std::shared_ptr<Material> bloodD = std::make_shared<Dielectric>(color3_t{ 0.75, 0.0, 0.15 }, 1.8f);
    std::shared_ptr<Material> bloodD = std::make_shared<Dielectric>(color3_t{ 0.5, 0.0, 0.07 }, 0.8f);
    std::shared_ptr<Material> wineD = std::make_shared<Dielectric>(color3_t{ 0.5, 0.0, 0.07 }, 1.2f);
    //std::shared_ptr<Material> darkSeedsD = std::make_shared<Dielectric>(color3_t{ 0.1, 0.0, 0.05 }, 1.8f);
    std::shared_ptr<Material> darkSeedsD = std::make_shared<Dielectric>(color3_t{ 0.2, 0.0, 0.1 }, 0.8f);
    std::shared_ptr<Material> blueD = std::make_shared<Dielectric>(color3_t{ 0.1, 0.0, 0.4 }, 1.5f);
    std::shared_ptr<Material> leavesD = std::make_shared<Dielectric>(color3_t{ 0.0, 0.4, 0.1 }, 1.9f);
    std::shared_ptr<Material> lightD = std::make_shared<Dielectric>(color3_t{ 0.8, 0.8, 0.8 }, 1.8f);

        //Emmiters
   std::shared_ptr<Material> whiteE = std::make_shared<Emissive>(color3_t{ 0.8, 0.8, 0.8 }, 10.2f);
   std::shared_ptr<Material> ghostE = std::make_shared<Emissive>(color3_t{ 0.03, 0.014, 1 }, 10.2f);
   std::shared_ptr<Material> blueE = std::make_shared<Emissive>(color3_t{ 0.0, 0.014, 0.95 }, 10.2f);
   std::shared_ptr<Material> softE = std::make_shared<Emissive>(color3_t{ 1, 0.023, 0.009}, 7.2f);




    //Add Materials
   std::vector<std::shared_ptr<Material>> pomMat1;
   std::vector<std::shared_ptr<Material>> pomMat2;
   std::vector<std::shared_ptr<Material>> grapeMat1;
   std::vector<std::shared_ptr<Material>> grapeMat2;
   std::vector<std::shared_ptr<Material>> lights;


         //pom
   //pomMatrials.push_back(pomegranateL);
   pomMat1.push_back(darkSeedsD);
   pomMat1.push_back(bloodD);
   pomMat2.push_back(whiteSeedM);
   pomMat2.push_back(whiteE);
   //pomMat2.push_back(ghostE);

        //grape
   grapeMat1.push_back(leavesD);
   grapeMat1.push_back(leavesM);

   grapeMat2.push_back(leavesM);
   grapeMat2.push_back(whiteSeedM);
   grapeMat2.push_back(whiteE);
   grapeMat2.push_back(grapeL);
   grapeMat2.push_back(grapeM);

        //lights
   lights.push_back(whiteE);
   lights.push_back(whiteE);
   lights.push_back(ghostE);
   lights.push_back(softE);
   lights.push_back(blueE);


    


    //Plane(s)
        //make planes
    auto floor = std::make_unique<Plane>(Transform(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 0, 0 }), floorD);

        //add planes
    scene.AddObject(std::move(floor));

    //Handplaced Spheres
        //Make Spheres
   //auto light = std::make_unique<Sphere>(Transform{ glm::vec3{ 0, 0, 0 } }, 1.0f, whiteE);
   //auto front = std::make_unique<Sphere>(Transform{ glm::vec3{ -13, 0, -22 } }, 1.0f, whiteE);
   //auto back = std::make_unique<Sphere>(Transform{ glm::vec3{ 50, 0, 30 } }, 1.0f, whiteE);
   //scene.AddObject(std::move(light));
   //scene.AddObject(std::move(front));
   //scene.AddObject(std::move(back));
    
        //Pomegranite
    auto pomegranite1 = std::make_unique<Sphere>(Transform{ glm::vec3{ 30, 7, 25 } }, 7.0f, pomegranateL);
    auto pomegranite2 = std::make_unique<Sphere>(Transform{ glm::vec3{ 22, 5, 20 } }, 5.0f, pomegranateL);
    auto pomegranite3 = std::make_unique<Sphere>(Transform{ glm::vec3{ 17, 8, 38 } }, 8.0f, pomegranateL);

    scene.AddObject(std::move(pomegranite1));
    scene.AddObject(std::move(pomegranite2));
    scene.AddObject(std::move(pomegranite3));

        //Grape
    auto grape1 = std::make_unique<Sphere>(Transform{ glm::vec3{ -28, 2.1, 4.5 } }, 2.1f, grapeL);
    auto grape2 = std::make_unique<Sphere>(Transform{ glm::vec3{ -25.5, 2, 3 } }, 2.0f, grapeM);
    auto grape3 = std::make_unique<Sphere>(Transform{ glm::vec3{ -26.5, 4.5, 4.6 } }, 2.0f, grapeL);
    auto grape4 = std::make_unique<Sphere>(Transform{ glm::vec3{ -24, 4, 4.6 } }, 1.8f, grapeL);
    auto grape5 = std::make_unique<Sphere>(Transform{ glm::vec3{ -23, 1.9, 3.7 } }, 1.9f, grapeL);
    auto grape6 = std::make_unique<Sphere>(Transform{ glm::vec3{ -25, 5.3, 5.7 } }, 1.9f, grapeM);
    auto grape7 = std::make_unique<Sphere>(Transform{ glm::vec3{ -22.5, 1.9, 6 } }, 1.9f, grapeM);
    auto grape8 = std::make_unique<Sphere>(Transform{ glm::vec3{ -20.6, 1.7, 3.5 } }, 1.7f, grapeL);
    auto grape9 = std::make_unique<Sphere>(Transform{ glm::vec3{ -24, 2.0, 4.6 } }, 2.0f, grapeL);
    auto grape10 = std::make_unique<Sphere>(Transform{ glm::vec3{ -23.2, 4, 5.3} }, 1.5f, grapeM);
    
    scene.AddObject(std::move(grape1));
    scene.AddObject(std::move(grape2));
    scene.AddObject(std::move(grape3));
    scene.AddObject(std::move(grape4));
    scene.AddObject(std::move(grape5));
    scene.AddObject(std::move(grape6));
    scene.AddObject(std::move(grape7));
    scene.AddObject(std::move(grape8));
    scene.AddObject(std::move(grape9));
    scene.AddObject(std::move(grape10));


    
    //Random Spheres
    //for (int i = 0; i <= 7; i++)
    //{
    //    int matNumber = random(0, materials.size());
    //
    //    auto object = std::make_unique<Sphere>(Transform{ glm::vec3{ randomf(glm::vec3{ -15 }, glm::vec3{ 15 }) } }, randomf(0.5, 4), materials[matNumber]);
    //    //scene.AddObject(std::move(object));
    //
    //}
    
        //pomagranite
    for (int i = 0; i <= 7; i++)
    {
        int matNumber = random(0, pomMat1.size());
        float radius = randomf(1, 3);

        auto object = std::make_unique<Sphere>(Transform{ glm::vec3{ randomf(glm::vec3{ 5, radius, -5 }, glm::vec3{ 30, radius, 30 }) } }, radius, pomMat1[matNumber]);
        scene.AddObject(std::move(object));
    }
    
    for (int i = 0; i <= 14; i++)
    {
        int matNumber = random(0, pomMat2.size());
        float radius = randomf(0.5, 1.5);

        auto object = std::make_unique<Sphere>(Transform{ glm::vec3{ randomf(glm::vec3{ 4, 0, -10 }, glm::vec3{ 30, radius, 35 }) } }, radius, pomMat2[matNumber]);
        scene.AddObject(std::move(object));
    }
    
    
        //grape
   for (int i = 0; i <= 5; i++)
   {
       int matNumber = random(0, grapeMat1.size());
       float radius = randomf(1.5, 4);
   
       auto object = std::make_unique<Sphere>(Transform{ glm::vec3{ randomf(glm::vec3{ -40, radius, 9 }, glm::vec3{ -25, radius, 20 }) } }, radius, grapeMat1[matNumber]);
       scene.AddObject(std::move(object));
   }
    
    for (int i = 0; i <= 17; i++)
    {
        int matNumber = random(0, grapeMat2.size());
        float radius = randomf(0.5, 1.5);
    
        auto object = std::make_unique<Sphere>(Transform{ glm::vec3{ randomf(glm::vec3{ -20, 0, 10 }, glm::vec3{ -3, radius, -17 }) } }, radius, grapeMat2[matNumber]);
        scene.AddObject(std::move(object));
    }


           //lights
    for (int i = 0; i <= 20; i++)
    {
        int matNumber = random(0, lights.size());
        float radius = randomf(1, 1.5);

        auto object = std::make_unique<Sphere>(Transform{ glm::vec3{ randomf(glm::vec3{ -40, 20, -20 }, glm::vec3{ 40, 40, 20 }) } }, radius, whiteE);
        scene.AddObject(std::move(object));
    }

    //Handplaced Models

    std::unique_ptr<Model> cube = std::make_unique<Model>(Transform(glm::vec3{ -7, 0, -20 }, glm::vec3{ 0, 40, 0 }, glm::vec3{ 3 }), leavesD);
    cube->Load("models/cube.obj");
    scene.AddObject(std::move(cube));
    
    std::unique_ptr<Model> cube2 = std::make_unique<Model>(Transform(glm::vec3{ 10, 0, -15 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 3.4 }), wineD);
    cube2->Load("models/cube.obj");
    scene.AddObject(std::move(cube2));
    
    
    std::unique_ptr<Model> cube3 = std::make_unique<Model>(Transform(glm::vec3{ -3, 0, 25 }, glm::vec3{ 0, 72, 0 }, glm::vec3{ 6 }), blueD);
    cube3->Load("models/cube.obj");
    scene.AddObject(std::move(cube3));

    



    //Temp

    
    auto temp3 = std::make_unique<Sphere>(Transform{ glm::vec3{ 5, 0, -5 } }, 3.0f, blueE);
    //scene.AddObject(std::move(temp3));




}
#pragma endregion


#pragma region InitScene01
void InitScene01(Scene& scene, Camera& camera)
{
    camera.SetFOV(20.0f);
    camera.SetView({ 13, 2, 3 }, { 0, 0, 0 });

    auto ground_material = std::make_shared<Lambertian>(color3_t(0.5f));
    scene.AddObject(std::make_unique<Plane>(Transform{ glm::vec3{ 0 } }, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = randomf();
            glm::vec3 center(a + 0.9 * randomf(), 0.2, b + 0.9 * randomf());

            if ((center - glm::vec3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = HSVtoRGB(randomf(0, 360), 1.0f, 1.0f);
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = HSVtoRGB(randomf(0, 360), 1.0f, 1.0f);
                    auto fuzz = randomf(0.0f, 0.5f);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, sphere_material));
                }
                else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(color3_t{ 1 }, 1.5f);
                    scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(color3_t{ 1 }, 1.5f);
    scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{ 0, 1, 0 } }, 1.0f, material1));

    auto material2 = std::make_shared<Lambertian>(color3_t(0.4f, 0.2f, 0.1f));
    scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{ -4, 1, 0 } }, 1.0f, material2));

    auto material3 = std::make_shared<Metal>(color3_t(0.7f, 0.6f, 0.5f), 0.0f);
    scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{ 4, 1, 0 } }, 1.0f, material3));
}
#pragma endregion


#pragma region ExperimentalScene
void ExperimentalScene(Scene& scene, Camera& camera)
{
    std::shared_ptr<Material> whiteL = std::make_shared<Metal>(color3_t{ 1, 0, 1 }, 0.1);
    //std::shared_ptr<Material> whiteL = std::make_shared<Emissive>(color3_t{ 0.055, 0.025, 0.075 }, 10.2f);

    //std::shared_ptr<Material> whiteL = std::make_shared<Emissive>(color3_t{ 0.55, 0.25, 0.75 }, 10.2f);
    //std::shared_ptr<Material> lightD = std::make_shared<Dielectric>(color3_t{ 0.9, 0.9, 0.9 }, 1.8f);

    //std::shared_ptr<Material> light = std::make_shared<Emissive>(color3_t{ 0.075, 0.025, 0.025 }, 30.2f);
    //std::shared_ptr<Material> light = std::make_shared<Emissive>(color3_t{ 0.075, 0.005, 0 }, 3000.2f);
    //std::shared_ptr<Material> light = std::make_shared<Emissive>(color3_t{ 0.6, 0.04, 0 }, 3000.2f);
    //std::shared_ptr<Material> light = std::make_shared<Emissive>(color3_t{ 0.9, 0.06, 0 }, 3000.2f);

    //std::shared_ptr<Material> light = std::make_shared<Emissive>(color3_t{ 0.9, 0.03, 0 }, 3000.2f);
    //std::shared_ptr<Material> lightD = std::make_shared<Dielectric>(color3_t{ 0.9, 0.9, 0.9 }, 1.3f);

    //std::shared_ptr<Material> light = std::make_shared<Emissive>(color3_t{ 1, 1, 1 }, 10.2f);
    //std::shared_ptr<Material> lightD = std::make_shared<Dielectric>(color3_t{ 0.9, 0.4, 0 }, 13.9f);
    ////std::shared_ptr<Material> outerD = std::make_shared<Dielectric>(color3_t{ 0.9, 0.9, 0.9 }, 13.9f);
    //std::shared_ptr<Material> outerD = std::make_shared<Dielectric>(color3_t{ 1, 1, 0.7 }, 0.95f);

    std::shared_ptr<Material> templight = std::make_shared<Emissive>(color3_t{ 1, 1, 1 }, 100.2f);
    //std::shared_ptr<Material> lightD = std::make_shared<Dielectric>(color3_t{ 0.9, 0.4, 0 }, 0.95f);
    //std::shared_ptr<Material> lightD = std::make_shared<Dielectric>(color3_t{ 0.9, 0.9, 0.9 }, 0.95f);
    //std::shared_ptr<Material> midD = std::make_shared<Dielectric>(color3_t{ 1, 1, 0.1 }, 1.05f);
    //std::shared_ptr<Material> outerD = std::make_shared<Dielectric>(color3_t{ 1, 0.4, 0 }, 0.95f);

    std::shared_ptr<Material> lightD = std::make_shared<Dielectric>(color3_t{ 0.9, 0.9, 0.9 }, 0.95f);
    std::shared_ptr<Material> midD = std::make_shared<Dielectric>(color3_t{ 1, 1, 0 }, 1.05f);
    std::shared_ptr<Material> outerD = std::make_shared<Dielectric>(color3_t{ 1, 1, 1 }, 0.95f);


    //auto temp1 = std::make_unique<Sphere>(Transform{ glm::vec3{ 0, 0, 0.55 } }, 1.0f, templight);
   //scene.AddObject(std::move(temp1));
   //auto temp2 = std::make_unique<Sphere>(Transform{ glm::vec3{ 0, 0, 0 } }, 1.1f, lightD);
   //scene.AddObject(std::move(temp2));
   //auto temp4 = std::make_unique<Sphere>(Transform{ glm::vec3{ 0, 0, 0 } }, 1.5f, midD);
   //scene.AddObject(std::move(temp4));
   //auto temp5 = std::make_unique<Sphere>(Transform{ glm::vec3{ 0, 0, 0 } }, 1.7f, outerD);
   //scene.AddObject(std::move(temp5));

    auto temp3 = std::make_unique<Sphere>(Transform{ glm::vec3{ 5, 0, -5 } }, 3.0f, whiteL);
    scene.AddObject(std::move(temp3));

    std::shared_ptr<Material> floorlight = std::make_shared<Emissive>(color3_t{ 0.9, 0.9, 0.9 }, 111.2f);

    auto templane = std::make_unique<Plane>(Transform(glm::vec3{ 0, -4, 0 }, glm::vec3{ 0, 0, 0 }), floorlight);
    //scene.AddObject(std::move(templane));
}

#pragma endregion