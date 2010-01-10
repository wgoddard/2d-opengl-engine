#pragma once

#include "Export.h"
#include "Renderer.h"
#include "Global.h"
#include "Logger.h"
#include "Box2d.h"

//#include "DebugDraw.h"

namespace Prominence {

	class DECLSPEC World
	{
	private:
		Logger & m_Logger;
		Renderer & m_Renderer;
		b2World * m_b2World;
		b2Body* body;
	public:
		World(Logger & logger, Renderer & renderer);
		~World(void);
		void Update(Uint32 dt);
		Quad GetBody();
		b2Body * CreateBody(b2PolygonDef * polyDef, float x, float y);

		void DrawBoxes();

	};

}