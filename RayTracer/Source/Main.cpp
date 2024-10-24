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

#include <SDL.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

int main(int argc, char* argv[])
{
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

	std::shared_ptr<Material> material = std::make_shared<Material>(color3_t{ 1, 0, 0 });
	auto object = std::make_unique<Sphere>(glm::vec3{ 0, 0, 40 }, 5.0f, material);
	scene.AddObject(std::move(object));

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

		framebuffer.Clear(ColorConvert(color4_t{ 0, 0.25f, 0, 1 }));

		scene.Render(framebuffer, camera);

		framebuffer.Update();

		// show screen
		renderer = framebuffer;
		SDL_RenderPresent(renderer.m_renderer);
	}

	return 0;
}