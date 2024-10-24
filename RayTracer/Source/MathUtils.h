#pragma once
#include <glm/glm.hpp>

template<typename T> 
inline T Lerp(const T& a, const T& b, float t)
{
    return static_cast<T>(a + ((b - a) * t));
}

inline void QuadraticPoint(int x1, int y1, int x2, int y2, int x3, int y3, float t, int& x, int& y)
{
	float one_minus_t = 1 - t;

	float a = one_minus_t * one_minus_t; // std::pow(one_minus_t1, 2)
	float b = 2 * one_minus_t * t;
	float c = t * t;

	x = (int)(a * x1 + b * x2 + c * x3);
	y = (int)(a * y1 + b * y2 + c * y3);
}

inline void CubicPoint(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, float t, int& x, int& y)
{
	float one_minus_t = 1 - t;

	float a = one_minus_t * one_minus_t * one_minus_t;
	float b = 3 * (one_minus_t * one_minus_t) * t;
	float c = 3 * one_minus_t * (t * t);
	float d = t * t * t;

	x = (int)((a * x1) + (b * x2) + (c * x3) + (d * x4));
	y = (int)((a * y1) + (b * y2) + (c * y3) + (d * y4));
}

template<typename T>
inline T Clamp(const T& value, const T& min, const T& max)
{
	return(value < min) ? min : (value > max) ? max : value;
}

inline glm::vec3 Cross(const glm::vec3& v1, const glm::vec3& v2)
{
	glm::vec3 result;

	result.x = (v1.y * v2.z) - (v2.y * v1.z);
	result.y = (v1.z * v2.x) - (v2.z * v1.x);
	result.z = (v1.x * v2.y) - (v2.x * v1.y);

	return result;
}