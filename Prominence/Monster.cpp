#include "Monster.h"

namespace Prominence {

	Monster::Monster(AnimatedSprite & sprite, b2Body & body) : Actor(sprite, body)
	{
	}

	Monster::~Monster(void)
	{
	}

}
