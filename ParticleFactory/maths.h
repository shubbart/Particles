#pragma once
#include <random>
#include <cmath>

inline float rand01()
{
	return (float)rand() / RAND_MAX;
}

inline float lerp(float s, float e, float t) { return s*(1 - t) + e*t; };

#define DEG2RAD 0.0174533

struct vec2 { float x, y; };
inline vec2 operator+(const vec2 &a, const vec2 &b)
{
	return vec2{ a.x + b.x, a.y + b.y };
}

inline vec2 operator*(const vec2 &a, float b)
{
	return vec2{ a.x * b, a.y * b };
}

inline vec2 lerp(const vec2 &s, const vec2 &e, float t)
{
	return s*(1 - t) + e*t;
}

inline vec2 randRange(const vec2&min, const vec2 &max)
{
	return vec2{ lerp(min.x,max.x,rand01()), lerp(min.y,max.y, rand01()) };
}

inline vec2 randDir(float min_degrees, float max_degrees)
{
	float deg = lerp(min_degrees, max_degrees, rand01());
	float rad = DEG2RAD * deg;

	return vec2{ cos(rad), sin(rad) };
}

union color
{
	unsigned ui_color;
	struct {unsigned char a, b, r, g; };
};

inline color lerp(const color &s, const color &e, float t)
{
	color ret;
	ret.r = s.r*(1 - t) + e.r*t;
	ret.g = s.g*(1 - t) + e.g*t;
	ret.b = s.b*(1 - t) + e.b*t;
	ret.a = s.a*(1 - t) + e.a*t;
	return ret;
}
