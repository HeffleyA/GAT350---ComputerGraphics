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

void InitScene(Scene& scene);
void InitScene01(Scene& scene, Camera& camera);

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
	camera.SetView({ 0, 0, -20 }, { 0, 0, 0 });

	Scene scene;
	//InitScene(scene);
	InitScene01(scene, camera);

	//framebuffer.Clear(ColorConvert(color4_t{ 0, 0.25f, 0, 1 }));
	scene.Update();
	scene.Render(framebuffer, camera, 80, 6);
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

void InitScene(Scene& scene)
{
	//scene.SetSky(HSVtoRGB(240, 1, 0.5f), HSVtoRGB(240, 1, 1.0f));

	std::vector<std::shared_ptr<Material>> materials;

	std::shared_ptr<Material> gray = std::make_shared<Lambertian>(color3_t{ 0.5f });
	std::shared_ptr<Material> red = std::make_shared<Lambertian>(color3_t{ 1, 0, 0 });
	std::shared_ptr<Material> blue = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
	std::shared_ptr<Material> green = std::make_shared<Lambertian>(color3_t{ 0, 1, 0});
	std::shared_ptr<Material> yellow = std::make_shared<Metal>(color3_t{ 1, 1, 0 }, 0.1f);
	std::shared_ptr<Material> white = std::make_shared<Lambertian>(color3_t{ 1, 1, 1 });
	std::shared_ptr<Material> transparent = std::make_shared<Dielectric>(color3_t{ 1, 1, 1 }, 1.33f);
	std::shared_ptr<Material> light = std::make_shared<Emissive>(color3_t{ 1, 1, 1 }, 10.0f);

	materials.push_back(red);
	materials.push_back(blue);
	materials.push_back(green);
	materials.push_back(yellow);
	materials.push_back(white);

	auto rightWall = std::make_unique<Plane>(Transform{ glm::vec3{ 50, 0, 0 }, glm::vec3{ 0, 0, 90 } }, green);
	scene.AddObject(std::move(rightWall));

	auto leftWall = std::make_unique<Plane>(Transform{ glm::vec3{ -50, 0, 0 }, glm::vec3{ 0, 0, 90 } }, red);
	scene.AddObject(std::move(leftWall));

	auto roof = std::make_unique<Plane>(Transform{ glm::vec3{ 0, 50, 0 }, glm::vec3{ 0, 0 , 0 } }, white);
	scene.AddObject(std::move(roof));

	auto floor = std::make_unique<Plane>(Transform{ glm::vec3{ 0, -50, 0 }, glm::vec3{ 0, 0 , 0 } }, white);
	scene.AddObject(std::move(floor));

	//auto roofLight = std::make_unique<Plane>(Transform{ glm::vec3{ 0, 30, 0 }, glm::vec3{ 0, 0 , 0 }, glm::vec3{ 0.5f, 0.5f, 0  } }, light);
	//scene.AddObject(std::move(roofLight));

	Transform transform{ glm::vec3{ 0, 2, 2}, glm::vec3{ 0, 40, 0}, glm::vec3{ 4 } };

	//auto triangle = std::make_unique<Triangle>(glm::vec3{ -10, 0, 0 }, glm::vec3{ 0, 10, 0 }, glm::vec3{ 10, 0, 0 }, transform, blue);
	//scene.AddObject(std::move(triangle));

	auto model = std::make_unique<Model>(green);
	model->Load("Models/cube.obj");
	scene.AddObject(std::move(model));

	auto object = std::make_unique<Sphere>(glm::vec3{ 25, -30, 40 }, 5.0f, blue);
	scene.AddObject(std::move(object));

	auto object2 = std::make_unique<Sphere>(glm::vec3{ -15, -10, 40 }, 20.0f, transparent);
	scene.AddObject(std::move(object2));

	//for (int i = 0; i < 5; i++)
	//{
	//	std::shared_ptr<Material> random_material = materials[random((unsigned int)materials.size())];

	//	auto sphere = std::make_unique<Sphere>(Transform{ glm::vec3{ random(glm::vec3{ -10.0f }, glm::vec3{ 10.0f })} }, randomf(1.0f, 3.0f), random_material);
	//	scene.AddObject(std::move(sphere));
	//}

	//auto sphere = std::make_unique<Sphere>(glm::vec3{ 0 }, 2.0f, red);
	//scene.AddObject(std::move(sphere));
}

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