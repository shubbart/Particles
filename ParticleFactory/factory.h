#pragma once
#include "components.h"
#include "ObjectPool.h"

template<typename T>
using handle = ObjectPool<T>::iterator;
struct Entity
{
	class Factory *factory;
	handle<transform> trans;
	handle<rigidbody> rgbd;
	handle<lifetime> life;
	handle<sprite> sprt;
	handle<controller> ctrl;
	handle<particle> part;

	void onFree()
	{
		if (trans) trans.free();
		if (rgbd) rgbd.free();
		if (life) life.free();
		if (sprt) sprt.free();
		if (ctrl) ctrl.free();
		if (part) part.free();
	}
};

class Factory
{
	ObjectPool<Entity> entities;
	ObjectPool<transform> transforms;
	ObjectPool<rigidbody> rigibodies;
	ObjectPool<lifetime> lifetimes;
	ObjectPool<sprite> sprites;
	ObjectPool<controller> controllers;
	ObjectPool<particle> particles;

public:

	Factory() : entities(512), transforms(512), rigibodies(512), lifetimes(512), sprites(512), controllers(512), particles(512) {}

	handle<Entity> destroy(handle<Entity> &eit) { eit->onFree(); return eit.free(); }
	handle<Entity> begin() { return entities.begin(); }
	handle<Entity> end() { return entities.end(); }

	handle<Entity> spawnStaticImage(unsigned sprite_id, float x, float y, float w, float h, float time = -1)
	{
		handle<Entity> retval = entities.push();
		retval->trans = transforms.push();
		retval->sprt = sprites.push();

		retval->trans->pos = vec2{ x,y };
		retval->trans->scale = vec2{ w,h };
		retval->sprt->sprite_id = sprite_id;

		if (time > 0)
		{
			retval->life = lifetimes.push();
			retval->life->time = time;
		}
		return retval;
	}

};
