#pragma once
#include "particles.h"
#include "ObjectPool.h"

#define PART_SIZE 100000

class ParticleEmitter
{
	//particle particles[PART_SIZE];
	ObjectPool<particle> particles;
	void emit()
	{
		/*for (int i = 0; i < PART_SIZE; ++i)
			if (!particles[i].isActive())
			{
				particles[i] = _generate();
				return;
			}*/
		particles.push(_generate());
	}
	particle _generate()
	{
		particle part;
		part.pos = pos;
		part.sprite = sprite;
		part.vel = randDir(angleLow, angleHigh) * lerp(speedLow, speedHigh, rand01());
		part.lifespan = lerp(lifespanLow, lifespanHigh, rand01());
		part.sColor = lerp(colorLowStart, colorHighStart, rand01());
		part.eColor = lerp(colorLowEnd, colorHighEnd, rand01());
		part.sDim = lerp(dimLowStart, dimHighStart, rand01());
		part.eDim = lerp(dimLowEnd, dimHighEnd, rand01());
		part.lifetime = 0;
		return part;
	}
	float emissionTimer;
public:
	float emitRateLow, emitRateHigh;

	ParticleEmitter() : emissionTimer(0), particles(PART_SIZE) {}

	unsigned sprite;
	vec2 pos;
	float angleLow, angleHigh;
	float speedLow, speedHigh;
	vec2 dimLowStart, dimHighStart, dimLowEnd, dimHighEnd;
	color colorLowStart, colorHighStart, colorLowEnd, colorHighEnd;
	float lifespanLow, lifespanHigh;

	void update(float dt)
	{
		/*for (int i = 0; i < PART_SIZE; ++i)
		{
			if(particles[i].isActive())
			{
				particles[i].refresh(dt);
			}*/
		for (auto it = particles.begin(); it != particles.end();)
		{
			it->refresh(dt);
			if (it->isActive()) ++it;
			else it.free();
		}

		emissionTimer -= dt;
		while (emissionTimer < 0)
		{
			emit();
			emissionTimer += lerp(emitRateLow, emitRateHigh, rand01());
		}
	}
};
