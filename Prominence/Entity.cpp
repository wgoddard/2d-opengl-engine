#include "Entity.h"

namespace Prominence {

	Entity::Entity(Sprite & sprite, float x, float y) : m_Sprite(sprite), m_X(x), m_Y(y)
	{
		m_HFlip = false;
	}

	Entity::~Entity(void)
	{

	}

	void Entity::Render()
	{
		m_Sprite.Render(m_X, m_Y);
	}


	
}
