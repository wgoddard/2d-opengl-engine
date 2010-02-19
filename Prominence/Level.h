#pragma once

#include "Global.h"
#include "Export.h"
#include "Entity.h"

#include <vector>

namespace Prominence {

	class DECLSPEC Level
	{
	private:
		std::vector<Entity*> m_Entities;
	public:
		Level(void);
		~Level(void);
		void Update(Uint32 dt);
		void Render();
		void AddEntity(Entity * e) { m_Entities.push_back(e); }
	};

}