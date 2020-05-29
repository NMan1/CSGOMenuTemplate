#pragma once
#include <cstdint>
#include <d3d9.h>
#include <cmath>

struct color {
	float a, r, g, b;
	color() = default;
	color(float r, float g, float b, float a = 255) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	color(uint32_t color) {
		this->a = (color >> 24) & 0xff;
		this->r = (color >> 16) & 0xff;
		this->g = (color >> 8) & 0xff;
		this->b = (color & 0xff);
	}
	color from_uint(uint32_t uint) {
		return color(uint);
	}

	void random_color(int iTick)
	{
		this->r = sin(3.f * iTick + 0.f) * 127 + 128;
		this->g = sin(3.f * iTick + ((2.f * M_PI) / 3)) * 127 + 128;
		this->b = sin(3.f * iTick + ((4.f * M_PI) / 3)) * 127 + 128;
		this->a = 255;
		// decrease 0.3f if you want it smoother
	}

	static color black(float a = 255) { return { 0, 0, 0, a }; }
	static color white(float a = 255) { return { 255, 255, 255, a }; }
	static color red(float   a = 255) { return { 255, 0, 0, a }; }
	static color green(float a = 255) { return { 0, 255, 0, a }; }
	static color blue(float  a = 255) { return { 0, 0, 255, a }; }


};

static void rainbow(color& clr)
{
	static uint32_t cnt = 0;
	float freq = .005f;

	color _clr = color(
		std::sin(freq * cnt + 0) * 127 + 128,
		std::sin(freq * cnt + 2) * 127 + 128,
		std::sin(freq * cnt + 4) * 127 + 128,
		255);

	// Probably redundant
	if (cnt++ >= (uint32_t)-1) cnt = 0;

	clr = _clr;
}
