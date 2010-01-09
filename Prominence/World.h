#pragma once

#include "Export.h"
#include "Global.h"
#include "Logger.h"
#include "Box2d.h"

namespace Prominence {

	class DECLSPEC World
	{
	private:
		Logger & m_Logger;
		b2World * m_b2World;
		b2Body* body;
	public:
		World(Logger & logger);
		~World(void);
		void Update(Uint32 dt);
		Quad GetBody();
		b2Body * CreateBody(Uint32 width, Uint32 height);

	};

}