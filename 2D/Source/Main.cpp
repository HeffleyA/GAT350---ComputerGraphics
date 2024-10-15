#include "Renderer.h"
#include "Framebuffer.h"
#include "MathUtils.h"
#include "Image.h"
#include "PostProcess.h"

#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
	Renderer renderer;

	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);

	Framebuffer framebuffer(renderer, 400, 300);

	Image image;
	image.Load("Lake.jpg");

	bool quit = false;
	while (!quit)
	{
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
		framebuffer.Clear(color_t{ 0, 0, 0, 255 });

		SetBlendMode(BlendMode::Normal);
		framebuffer.DrawImage(100, 100, image);

		for (int i = 0; i < 10; i++)
		{
			int x1 = rand() % framebuffer.m_width;
			int y1 = rand() % framebuffer.m_height;
			int x2 = rand() % framebuffer.m_width;
			int y2 = rand() % framebuffer.m_height;
			int x3 = rand() % framebuffer.m_width;
			int y3 = rand() % framebuffer.m_height;

			//framebuffer.DrawImage(x1, y1, image);
			//framebuffer.DrawPoint(x, y, { 255, 255, 255, 255 });
			//framebuffer.DrawLine(x1, y1, x2, y2, { 255, 255, 255, 255 });
			//framebuffer.DrawTriangle(x1, y1, x2, y2, x3, y3, { 255, 255, 255, 255 });
			//framebuffer.DrawCircle(x1, y1, r, { 255, 255, 255, 255 });
		}

		//SetBlendMode(BlendMode::Alpha);
		//framebuffer.DrawImage(100, 100, imageAlpha);

		//PostProcess::BoxBlur(image.m_buffer, 50, 50);
		//PostProcess::GaussianBlur(image.m_buffer, 50, 50);
		//PostProcess::Sharpen(image.m_buffer, 50, 50);
		//PostProcess::Edge(image.m_buffer, 50, 50, 100);
		//PostProcess::Emboss(image.m_buffer, 50, 50);

		//int mx, my;
		//SDL_GetMouseState(&mx, &my);

		//framebuffer.DrawCubicCurve(100, 200, 100, 100, mx, my, 300, 200, { 255, 255, 255, 255 });

		//int ticks = SDL_GetTicks();
		//float time = ticks * 0.001f;
		//float t = std::abs(std::sin(time));
		//int x, y;
		//CubicPoint(100, 200, 100, 100, mx, my, 300, 200, t, x, y);
		//framebuffer.DrawRect(x - 20, y - 20, 60, 50, { 255, 255, 0, 255 });


		//framebuffer.DrawCircle(100, 100, 30, { 255, 255, 255, 255 });
		//framebuffer.DrawTriangle(100, 200, 50, 200, 50, 100, {255, 255, 255, 255});
		//framebuffer.DrawLine(300, 200, 350, 250, { 255, 255, 255, 255 });
		
#pragma region post_process
		//PostProcess::Invert(framebuffer.m_buffer);
		//PostProcess::Monochrome(framebuffer.m_buffer);
		//PostProcess::Brightness(framebuffer.m_buffer, 50);
		//PostProcess::ColorBalance(framebuffer.m_buffer, 150, -50, -50);
		//PostProcess::Noise(framebuffer.m_buffer, 80);
		//PostProcess::Noise(framebuffer.m_buffer, 150);
		//PostProcess::Posterize(framebuffer.m_buffer, 6);
#pragma endregion

		framebuffer.Update();

		renderer = framebuffer;
		//renderer.CopyFramebuffer(framebuffer);

		SDL_RenderPresent(renderer.m_renderer);
	}

	return 0;
}