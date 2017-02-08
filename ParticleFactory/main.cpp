#include "sfwdraw.h"
#include "maths.h"
#include "particles.h"
#include "ParticleEmitter.h"
#include "ObjectPool.h"
#include "factory.h"
#include "GameState.h"

void main()
{
	sfw::initContext();

	GameState gs;
	gs.init();
	gs.play();

	while (sfw::stepContext())
	{
		float dt = sfw::getDeltaTime();

		gs.update(dt);
	}
}

/*void main()
{
	sfw::initContext(800, 1000);
	
	unsigned sprite = sfw::loadTextureMap("../res/particle_sprite.png");

	ParticleEmitter pe;
	pe.emitRateLow = 0.01f;
	pe.emitRateHigh = 0.03f;

	pe.sprite = sprite;

	pe.pos = vec2{ 400,1020 };
	pe.angleLow = 270;
	pe.angleHigh = 270;
	pe.speedLow = 100;
	pe.speedHigh = 900;
	pe.dimLowStart = vec2{ 8,8 };
	pe.dimHighStart = vec2{ 32,32 };
	pe.dimLowEnd = vec2{ 256,256 };
	pe.dimHighEnd = vec2{ 512,512 };

	pe.colorLowStart.ui_color = NONE;
	pe.colorHighStart.ui_color = CYAN;
	pe.colorLowEnd.ui_color = CYAN;
	pe.colorHighEnd.ui_color = BLUE;

	pe.lifespanLow = .6f;
	pe.lifespanHigh = 1.7f;

	ParticleEmitter pe2;
	pe2.emitRateLow = 0.01f;
	pe2.emitRateHigh = 0.03f;

	pe2.sprite = sprite;

	pe2.pos = vec2{ 400,-70 };
	pe2.angleLow = 0;
	pe2.angleHigh = 180;
	pe2.speedLow = 120;
	pe2.speedHigh = 250;
	pe2.dimLowStart = vec2{ 8,8 };
	pe2.dimHighStart = vec2{ 32,32 };
	pe2.dimLowEnd = vec2{ 256,256 };
	pe2.dimHighEnd = vec2{ 512,512 };

	pe2.colorLowStart.ui_color = WHITE;
	pe2.colorHighStart.ui_color = CYAN;
	pe2.colorLowEnd.ui_color = CYAN;
	pe2.colorHighEnd.ui_color = WHITE;

	pe2.lifespanLow = .3f;
	pe2.lifespanHigh = .7f;


	while (sfw::stepContext())
	{
		float dt = sfw::getDeltaTime();
		
		pe.update(dt);
		pe2.update(dt);
	}

	sfw::termContext();
}*/