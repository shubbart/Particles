#pragma once
#include "components.h"
#include "ObjectPool.h"

//template<typename T>
//using handle = ObjectPool<T>::iterator;
struct Entity
{
	class Factory *factory;
	ObjectPool<transform>::iterator trans;
	ObjectPool<rigidbody>::iterator rgbd;
	ObjectPool<lifetime>::iterator life;
	ObjectPool<sprite>::iterator sprt;
	ObjectPool<controller>::iterator ctrl;
	ObjectPool<particles>::iterator part;

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
	ObjectPool<rigidbody> rigidbodies;
	ObjectPool<lifetime> lifetimes;
	ObjectPool<sprite> sprites;
	ObjectPool<controller> controllers;
	ObjectPool<particles> particles;

public:

	Factory() : entities(512), transforms(512), rigidbodies(512), controllers(512),
		sprites(512), lifetimes(512), particles(512)
	{ }

	ObjectPool<Entity>::iterator begin() { return entities.begin(); }
	ObjectPool<Entity>::iterator end() { return entities.end(); }


	ObjectPool<Entity>::iterator destroy(ObjectPool<Entity>::iterator &eit) { eit->onFree(); return eit.free(); }

	// transform, sprite, O:lifetime
	ObjectPool<Entity>::iterator spawnStaticImage(unsigned sprite_id, float x, float y, float w, float h, float time = -1)
	{
		ObjectPool<Entity>::iterator retval = entities.push();
		if (!retval) return retval;

		retval->factory = this;

		retval->trans = transforms.push();
		retval->sprt = sprites.push();

		retval->trans->pos = vec2{ x, y };
		retval->trans->scale = vec2{ w, h };
		retval->sprt->sprite_id = sprite_id;

		if (time > 0)
		{
			retval->life = lifetimes.push();
			retval->life->lifespan = time;
		}

		return retval;
	}
};
