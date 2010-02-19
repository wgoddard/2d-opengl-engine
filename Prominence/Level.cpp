#include "Level.h"

namespace Prominence {

	Level::Level(void)
	{
	}

	Level::~Level(void)
	{
		for (unsigned int i = 0; i < m_Entities.size(); ++i)
			delete m_Entities[i];
	}

	void Level::Update(Uint32 dt)
	{
		std::vector<Entity*>::iterator i;

		for (i = m_Entities.begin(); i != m_Entities.end(); ++i)
		{
			(*i)->Update(dt);
		}
	}

	void Level::Render()
	{
		std::vector<Entity*>::iterator i;

		for (i = m_Entities.begin(); i != m_Entities.end(); ++i)
		{
			(*i)->Render();
		}
	}

}