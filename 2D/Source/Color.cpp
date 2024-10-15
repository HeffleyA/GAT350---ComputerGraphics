#include "Color.h"

color_t(*blend_func)(const color_t& src, const color_t& dst);

void SetBlendMode(BlendMode blendMode)
{
	switch (blendMode)
	{
	case BlendMode::Normal:
		blend_func = NormalBlend;
		break;
	case BlendMode::Alpha:
		blend_func = AlphaBlend;
		break;
	case BlendMode::Additive:
		blend_func = AdditiveBlend;
		break;
	case BlendMode::Multiply:
		break;
	default:
		break;
	}
}

color_t ColorBlend(const color_t& src, const color_t& dst)
{
	return blend_func(src, dst);
}

color_t NormalBlend(const color_t& src, const color_t& dst)
{
	return src;
}

color_t AlphaBlend(const color_t& src, const color_t& dst)
{
	uint8_t alpha = src.a;
	uint8_t inv_alpha = 255 - alpha;

	color_t color;
	color.r = (src.r * alpha + dst.r * inv_alpha) >> 8;
	color.g = (src.g * alpha + dst.g * inv_alpha) >> 8;
	color.b = (src.b * alpha + dst.b * inv_alpha) >> 8;
	color.a = src.a;

	return color;
}

color_t AdditiveBlend(const color_t& src, const color_t& dst)
{
	color_t color;
	color.r = std::min(src.r + dst.r, 255) >> 8;
	color.g = std::min(src.g + dst.g, 255) >> 8;
	color.b = std::min(src.b + dst.b, 255) >> 8;
	color.a = src.a;

	return color;
}