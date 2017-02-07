#include "sfwdraw.h"
#include "maths.h"
#include "particles.h"
#include "ParticleEmitter.h"

void main()
{
	sfw::initContext();
	
	unsigned sprite = sfw::loadTextureMap("../res/particle_sprite.png");

	ParticleEmitter pe;
	pe.emitRateLow = 0.1f;
	pe.emitRateHigh = 0.3f;

	pe.sprite = sprite;

	pe.pos = vec2{ 400,300 };
	pe.angleLow = 0;
	pe.angleHigh = 360;
	pe.speedLow = 120;
	pe.speedHigh = 450;
	pe.dimLowStart = vec2{ 8,8 };
	pe.dimHighStart = vec2{ 32,32 };
	pe.dimLowEnd = vec2{ 256,256 };
	pe.dimHighEnd = vec2{ 512,512 };

	pe.colorLowStart.ui_color = GREEN;
	pe.colorHighStart.ui_color = YELLOW;
	pe.colorLowEnd.ui_color = BLUE;
	pe.colorHighEnd.ui_color = RED;

	pe.lifespanLow = .3f;
	pe.lifespanHigh = .7f;


	while (sfw::stepContext())
	{
		float dt = sfw::getDeltaTime();
		
		pe.update(dt);
	}

	sfw::termContext();
}