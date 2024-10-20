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

#include <SDL.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main(int argc, char* argv[])
{
	//initialize
	Time time;
	Input input;
	input.Initialize();

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);

	SetBlendMode(BlendMode::Normal);

	Camera camera(renderer.m_width, renderer.m_height);
	camera.SetView(glm::vec3{ 0, 0, 50 }, glm::vec3{ 0 });
	camera.SetProjection(60.0f, 800.0f / 600, 0.1f, 200.0f);
	Transform cameraTransform{ { 0, 0, -20 } };

	Framebuffer framebuffer(renderer, 800, 600);

	//vertices_t vertices{ {-5, 5, 0}, {5, 5, 0}, {-5, -5, 0} };
	//Model model(vertices, {0, 255, 0, 255});
	Transform transform{ { 0, 0, 0 }, glm::vec3{ 0, 0, 45 }, glm::vec3{ 1 } };

	Model model;
	model.Load("teapot.obj");
	model.SetColor({ 0, 255, 0, 255 });

	Image image;
	image.Load("Lake.jpg");

	Image imageAlpha;
	imageAlpha.Load("colors.png");
	PostProcess::Alpha(imageAlpha.m_buffer, 128);

	bool quit = false;
	while (!quit)
	{
		time.Tick();
		input.Update();

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

		framebuffer.Clear({ 0, 0, 0, 255 });
#pragma region draw
		//for (int i = 0; i < 10; i++)
		//{
		//	int x1 = rand() % framebuffer.m_width;
		//	int y1 = rand() % framebuffer.m_height;
		//	int x2 = rand() % framebuffer.m_width;
		//	int y2 = rand() % framebuffer.m_height;
		//	int x3 = rand() % framebuffer.m_width;
		//	int y3 = rand() % framebuffer.m_height;

			//framebuffer.DrawImage(x1, y1, image);
			//framebuffer.DrawPoint(x, y, { 255, 255, 255, 255 });
			//framebuffer.DrawLine(x1, y1, x2, y2, { 255, 255, 255, 255 });
			//framebuffer.DrawTriangle(x1, y1, x2, y2, x3, y3, { 255, 255, 255, 255 });
			//framebuffer.DrawCircle(x1, y1, r, { 255, 255, 255, 255 });
		//}
	
		//SetBlendMode(BlendMode::Normal);
		//framebuffer.DrawImage(340, 250, image);

		//SetBlendMode(BlendMode::Alpha);
		//framebuffer.DrawImage(80, 100, imageAlpha);
		
		//int mx, my;
		//SDL_GetMouseState(&mx, &my);

		//framebuffer.DrawCubicCurve(100, 200, 100, 100, mx, my, 300, 200, { 255, 255, 255, 255 });

		//int x, y;
		//CubicPoint(100, 200, 100, 100, mx, my, 300, 200, t, x, y);
		//framebuffer.DrawRect(x - 20, y - 20, 60, 50, { 255, 255, 0, 255 });


		//framebuffer.DrawCircle(100, 100, 30, { 255, 255, 255, 255 });
		//framebuffer.DrawTriangle(100, 200, 50, 200, 50, 100, {255, 255, 255, 255});
		//framebuffer.DrawLine(300, 200, 350, 250, { 255, 255, 255, 255 });
#pragma endregion
		
#pragma region post_process
		//PostProcess::Invert(framebuffer.m_buffer);
		//PostProcess::Monochrome(framebuffer.m_buffer);
		//PostProcess::Brightness(framebuffer.m_buffer, 50);
		//PostProcess::ColorBalance(framebuffer.m_buffer, 150, -50, -50);
		//PostProcess::Noise(framebuffer.m_buffer, 80);
		//PostProcess::Noise(framebuffer.m_buffer, 150);
		//PostProcess::Posterize(framebuffer.m_buffer, 6);
		
		//PostProcess::BoxBlur(image.m_buffer, 120, 120);
		//PostProcess::GaussianBlur(image.m_buffer, 120, 120);
		//PostProcess::Sharpen(image.m_buffer, 120, 120);
		//PostProcess::Edge(image.m_buffer, 100, 100, 50);
		//PostProcess::Emboss(image.m_buffer, 120, 120);
#pragma endregion


		glm::vec3 direction{ 0 };
		if (input.GetKeyDown(SDL_SCANCODE_RIGHT)) direction.x = -1;
		if (input.GetKeyDown(SDL_SCANCODE_LEFT)) direction.x = 1;
		if (input.GetKeyDown(SDL_SCANCODE_UP)) direction.y = 1;
		if (input.GetKeyDown(SDL_SCANCODE_DOWN)) direction.y = -1;
		if (input.GetKeyDown(SDL_SCANCODE_W)) direction.z = 1;
		if (input.GetKeyDown(SDL_SCANCODE_S)) direction.z = -1;

		cameraTransform.position += direction * 100.0f * time.GetDeltaTime();
		camera.SetView(cameraTransform.position, cameraTransform.position + glm::vec3{ 0, 0, 1 });

		transform.rotation.z +=  90 * time.GetDeltaTime();
		model.Draw(framebuffer, transform.GetMatrix(), camera);

		framebuffer.Update();

		renderer = framebuffer;
		//renderer.CopyFramebuffer(framebuffer);

		SDL_RenderPresent(renderer.m_renderer);
	}

	return 0;
}