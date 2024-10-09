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

		Image image;
		image.Load("Lake.jpg");

		Image image2;
		image.Load("Lake.jpg");

		Image image3;
		image.Load("Lake.jpg");

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

		framebuffer.DrawImage(100, 100, image);
		framebuffer.DrawImage(200, 200, image2);
		framebuffer.DrawImage(300, 300, image3);

		int mx, my;
		SDL_GetMouseState(&mx, &my);

		framebuffer.DrawCubicCurve(100, 200, 100, 100, mx, my, 300, 200, { 255, 255, 255, 255 });

		int ticks = SDL_GetTicks();
		float time = ticks * 0.001f;
		float t = std::abs(std::sin(time));
		int x, y;
		CubicPoint(100, 200, 100, 100, mx, my, 300, 200, t, x, y);
		framebuffer.DrawRect(x - 20, y - 20, 60, 50, { 255, 255, 0, 255 });


		//framebuffer.DrawCircle(100, 100, 30, { 255, 255, 255, 255 });

		//framebuffer.DrawTriangle(100, 200, 50, 200, 50, 100, {255, 255, 255, 255});

		//framebuffer.DrawLine(300, 200, 350, 250, { 255, 255, 255, 255 });

		//PostProcess::Brightness(framebuffer.m_buffer, -245);

		framebuffer.Update();

		renderer = framebuffer;
		//renderer.CopyFramebuffer(framebuffer);

		SDL_RenderPresent(renderer.m_renderer);
	}

	return 0;
}