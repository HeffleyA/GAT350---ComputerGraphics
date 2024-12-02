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
#include "Shader.h"

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
	renderer.CreateWindow("Game Engine", 800, 600);

	Input input;
	input.Initialize();
	input.Update();

	SetBlendMode(BlendMode::Normal);

	Framebuffer framebuffer(renderer, 800, 600);

	Camera camera(renderer.m_width, renderer.m_height);
	camera.SetView(glm::vec3{ 0, 0, -50 }, glm::vec3{ 0 });
	camera.SetProjection(60.0f, 800.0f / 600, 0.1f, 200.0f);
	Transform cameraTransform{ { 0, 0, -20 } };

	// shader
	VertexShader::uniforms.view = camera.GetView();
	VertexShader::uniforms.projection = camera.GetProjection();
	VertexShader::uniforms.ambient = color3_t{ 0.01f };
	VertexShader::uniforms.light.position = glm::vec3{ 10, 10, -10 };
	VertexShader::uniforms.light.direction = glm::vec3{ 0, -1, 0 }; // light pointing down
	VertexShader::uniforms.light.color = color3_t{ 1 }; // white light

	Shader::framebuffer = &framebuffer;

	std::shared_ptr<Model> model1 = std::make_shared<Model>();
	model1->Load("Models/Cube.obj");
	model1->SetColor({ 0, 0, 1, 1 });

#pragma region ModelLoad
	//std::shared_ptr<Model> model2 = std::make_shared<Model>();
	//model2->Load("Models/duck.obj");

	//std::shared_ptr<Model> model3 = std::make_shared<Model>();
	//model3->Load("Models/AW101.obj");
#pragma endregion

	std::vector<std::unique_ptr<Actor>> actors;

	Transform transform1{ glm::vec3{ 0 }, glm::vec3{ 5 }, glm::vec3{1}};
	std::unique_ptr<Actor> actor1 = std::make_unique<Actor>(transform1, model1);
	actors.push_back(std::move(actor1));

#pragma region ModelDraw
	//Transform transform2{ { 0, -50, 50 }, glm::vec3{-45, 180, 0}, glm::vec3{0.5} };
	//std::unique_ptr<Actor> actor2 = std::make_unique<Actor>(transform2, model2);
	//actor2->SetColor({ 255, 255, 0, 255 });
	//actors.push_back(std::move(actor2));

	//Transform transform3{ { 0, -25, 25 }, glm::vec3{0, 90, 0}, glm::vec3{0.25} };
	//std::unique_ptr<Actor> actor3 = std::make_unique<Actor>(transform3, model3);
	//actor3->SetColor({ 0, 0, 0, 255 });
	//actors.push_back(std::move(actor3));
#pragma endregion

#pragma region imageLoad
	//Image image;
	//image.Load("clouds.jpeg");

#pragma endregion

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
	
		SetBlendMode(BlendMode::Normal);
		//framebuffer.DrawImage(0, 0, image);

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


		if (input.GetMouseButtonDown(2))
		{
			input.SetRelativeMode(true);

			glm::vec3 direction{ 0 };
			if (input.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;
			if (input.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
			if (input.GetKeyDown(SDL_SCANCODE_E)) direction.y = 1;
			if (input.GetKeyDown(SDL_SCANCODE_Q)) direction.y = -1;
			if (input.GetKeyDown(SDL_SCANCODE_W)) direction.z = 1;
			if (input.GetKeyDown(SDL_SCANCODE_S)) direction.z = -1;

			cameraTransform.rotation.y += input.GetMouseRelative().x * 0.25f;
			cameraTransform.rotation.x += input.GetMouseRelative().y * 0.25f;

			glm::vec3 offset = cameraTransform.GetMatrix() * glm::vec4{ direction, 0 };

			cameraTransform.position += offset * 70.0f * time.GetDeltaTime();
		}
		else
		{
			input.SetRelativeMode(false);
		}

		camera.SetView(cameraTransform.position, cameraTransform.position + cameraTransform.GetForward());
		VertexShader::uniforms.view = camera.GetView();

		for (auto& actor : actors)
		{
			actor->Draw();
		}

		framebuffer.Update();

		renderer = framebuffer;

		SDL_RenderPresent(renderer.m_renderer);
	}

	return 0;
}