#pragma once
#include "factory.h"

class GameState
{
	Factory factory;



public:

		void init()
	{
		puff_sprite =
			sfw::loadTextureMap("../res/particle_sprite.png");
	}

	void play()
	{
		for(int i = 0; i < 200; ++i)
		factory.spawnMouseAttractor(puff_sprite);
	}

	unsigned puff_sprite;
	
	void update(float dt)
	{
		sfw::drawCircle(sfw::getMouseX(), sfw::getMouseY(), 12);
		//factory.spawnStaticImage(puff_sprite, rand() % 800, rand() % 600, rand() % 40 + 40, rand() % 40 + 40, 3.f);

		for (auto e = factory.begin(); e != factory.end();)
		{
			if (e->sprt)
			{
				e->sprt->draw(*e->trans);
			}
			if (e->life)
			{
				if (!(e->life->isAlive()))
				{
					factory.destroy(e);
					continue;
				}
				e->life->age(dt);
			}
	
			if (e->rgbd && e->trans)
			{
				e->rgbd->integrate(*e->trans, dt);
			}

			if (e->ctrl  && e->rgbd && e->trans)
			{
				e->ctrl->poll(*e->trans, *e->rgbd);
			}


			if (e->part && e->life && e->trans && e->sprt)
			{
				e->part->update(*e->life, *e->trans, *e->sprt);
			}

			++e;
		}
	}
};
