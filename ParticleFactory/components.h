#pragma once

#include "maths.h"
#include "sfwdraw.h"

struct transform
{
	vec2 pos, scale;
	float angle = 0;
};

struct rigidbody
{
	vec2 velocity = { 0,0 }, acceleration = { 0,0 };
	void integrate(transform &T, float dt)
	{
		velocity = velocity + acceleration * dt;
		T.pos = T.pos + velocity * dt;
	}
};

struct lifetime
{
	float time = 0, lifespan;

	void age(float dt) { time += dt; }
	bool isAlive() const { return time < lifespan; }
	float pctAlive() const { return time / lifespan; }
};

struct sprite
{
	size_t sprite_id;
	color tint = { WHITE };

	void draw(const transform &T)
	{
		sfw::drawTexture(sprite_id, T.pos.x, T.pos.y,
			T.scale.x, T.scale.y, T.angle, true, 0, tint.ui_color);
	}
};

struct controller
{
	float speed;
	void poll(transform &T, rigidbody &RB)
	{
		vec2 mouse = vec2{ sfw::getMouseX(), sfw::getMouseY() };

		RB.acceleration = normal(mouse - T.pos) * speed;
	}
};

struct particles
{
	vec2 sDim, eDim;
	color sColor, eColor;

	void update(const lifetime &life, transform &trans, sprite &sprt)
	{
		trans.scale = lerp(sDim, eDim, life.pctAlive());
		sprt.tint = lerp(sColor, eColor, life.pctAlive());
	}
};
