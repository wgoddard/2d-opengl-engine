#pragma once

#include "Global.h"
#include "Export.h"
#include "Entity.h"
#include "tinyxml.h"
#include "Logger.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "SimpleSprite.h"
#include "Box2d.h"

#include <vector>

namespace Prominence {

	class DECLSPEC Level
	{
	private:
		std::vector<Entity*> m_Entities;
		std::string m_Name;
		ResourceManager & m_ResourceManager;
		Renderer & m_Renderer;
		b2World * m_b2World;
		b2Body* body;
	public:
		Level(ResourceManager & rm, Renderer & renderer);
		~Level(void);
		void Update(Uint32 dt);
		void Render();
		void AddEntity(Entity * e) { m_Entities.push_back(e); }
		bool LoadXML(Logger & logger, std::string file, int index);
		b2Body * CreateBody(b2PolygonDef * polyDef, float x, float y);
	};

}