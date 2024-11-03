#include "Renderer.h"
#include "Framebuffer.h"
#include "MathUtils.h"
#include "Image.h"
#include "PostProcess.h"
#include "Model.h"
#include "Transform.h"
#include "ETime.h"
#include "Input.h"
#include "Camera.h"
#include "Actor.h"
#include "Random.h"
#include "Tracer.h"
#include "Scene.h"
#include "Triangle.h"

#include <SDL.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

int main(int argc, char* argv[])
{
	srand((unsigned int)time(NULL));
	//initialize
	Time time;

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", 800, 600);

	SetBlendMode(BlendMode::Normal);

	Framebuffer framebuffer(renderer, renderer.m_width, renderer.m_height);

	Camera camera{ 70.0f, framebuffer.m_width / (float)framebuffer.m_height };
	camera.SetView({ 0, 5, -5 }, { 0, 0, 0 });

	Scene scene;

	std::vector<std::shared_ptr<Material>> materials;

	std::shared_ptr<Material> gray = std::make_shared<Lambertian>(color3_t{ 0.5f });
	std::shared_ptr<Material> red = std::make_shared<Emissive>(color3_t{ 1, 0, 0 }, 10.0f);
	std::shared_ptr<Material> blue = std::make_shared<Metal>(color3_t{ 0, 0, 1 }, 2.5f);
	std::shared_ptr<Material> green = std::make_shared<Lambertian>(color3_t{ 0, 1, 0 });
	std::shared_ptr<Material> yellow = std::make_shared<Metal>(color3_t{ 1, 1, 0 }, 0.1f);
	std::shared_ptr<Material> white = std::make_shared<Dielectric>(color3_t{ 1, 1, 1 }, 1.33f);

	materials.push_back(red);
	materials.push_back(blue);
	materials.push_back(green);
	materials.push_back(yellow);
	materials.push_back(white);

	//auto plane = std::make_unique<Plane>(glm::vec3{ 0, -5, 0 }, glm::vec3{ 0, 1, 0 }, gray);
	//scene.AddObject(std::move(plane));

	//auto triangle = std::make_unique<Triangle>(glm::vec3{ -10, 0, 0 }, glm::vec3{ 0, 10, 0 }, glm::vec3{ 10, 0, 0 }, blue);
	//scene.AddObject(std::move(triangle));

	auto model = std::make_unique<Model>(green);
	model->Load("cube-2.obj");
	scene.AddObject(std::move(model));

	//std::shared_ptr<Material> material = std::make_shared<Lambertian>(color3_t{ 1, 0, 0 });
	//auto object = std::make_unique<Sphere>(glm::vec3{ 0, 0, 40 }, 5.0f, material);
	//scene.AddObject(std::move(object));

	//for (int i = 0; i < 5; i++)
	//{
	//	std::shared_ptr<Material> random_material = materials[random((unsigned int)materials.size())];

		//auto sphere = std::make_unique<Sphere>(random(glm::vec3{ -10 }, glm::vec3{ 10 }), randomf(1, 5), random_material);
	//	scene.AddObject(std::move(sphere));
	//}

	//auto sphere = std::make_unique<Sphere>(glm::vec3{ 0.0f }, 2.0f, red);
	//scene.AddObject(std::move(sphere));

	//framebuffer.Clear(ColorConvert(color4_t{ 0, 0.25f, 0, 1 }));
	scene.Render(framebuffer, camera, 10, 5);
	framebuffer.Update();

	bool quit = false;
	while (!quit)
	{
		time.Tick();

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

		// show screen
		renderer = framebuffer;
		SDL_RenderPresent(renderer.m_renderer);
	}

	return 0;
}