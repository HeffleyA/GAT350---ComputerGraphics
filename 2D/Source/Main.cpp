#include "Renderer.h"
#include "Framebuffer.h"

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

		for (int i = 0; i < 100; i++)
		{
			int x = rand() % 400;
			int y = rand() % 300;
			framebuffer.DrawPoint(x, y, { 255, 255, 255, 255 });
		}

		framebuffer.DrawRect(150, 150, 60, 50, { 255, 255, 0, 255 });
		framebuffer.Update();

		renderer = framebuffer;
		//renderer.CopyFramebuffer(framebuffer);

		SDL_RenderPresent(renderer.m_renderer);
	}

	return 0;
}