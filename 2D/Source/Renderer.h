#pragma once
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>

class Renderer
{
public:
	Renderer() = default;
	~Renderer();

	bool Initialize();

	bool CreateWindow(std::string title, int width, int height);
	void CopyFramebuffer(const class Framebuffer& framebuffer);

	friend class Framebuffer;

	void operator = (const class Framebuffer& framebuffer);

public:
	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };

	int m_width{ 0 };
	int m_height{ 0 };
};