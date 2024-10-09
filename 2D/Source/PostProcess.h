#pragma once
#include "Framebuffer.h"

namespace PostProcess
{
	void Invert(std::vector<color_t>& buffer);
	void Monochrome(std::vector<color_t>& buffer);
	void Brightness(std::vector<color_t>& buffer, int brightness);
	void Brightness(std::vector<color_t>& buffer, int ro, int go, int bo);
}