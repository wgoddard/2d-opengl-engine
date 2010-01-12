#pragma once

#include "Export.h"
#include "Renderer.h"
#include "Global.h"
#include "Logger.h"
#include "Box2d.h"
#include "Entity.h"

#include "DebugDraw.h"

namespace Prominence {

	class DECLSPEC World
	{

		class ContactListener : public b2ContactListener
		{
		public:
			void Add(const b2ContactPoint* point)
			{
				if (point->shape1->IsSensor())
				{
					Entity * entity = (Entity *)point->shape1->GetBody()->GetUserData();
					entity->TouchGround();
				}
				if (point->shape2->IsSensor())
				{
					Entity * entity = (Entity *)point->shape2->GetBody()->GetUserData();
					entity->TouchGround();
				}
			}
		    
			void Persist(const b2ContactPoint* point)
			{
				//std::cout << "Contact persisting.\n";
			}
		    
			void Remove(const b2ContactPoint* point)
			{
				//Entity * temp;
				//if (temp = (Entity*)point->shape1->GetBody()->GetUserData())
				//	temp->UntouchGround();
				//if (temp = (Entity*)point->shape2->GetBody()->GetUserData())
				//	temp->UntouchGround();
				if (point->shape1->IsSensor())
				{
					Entity * entity = (Entity *)point->shape1->GetBody()->GetUserData();
					entity->UntouchGround();
				}
				if (point->shape2->IsSensor())
				{
					Entity * entity = (Entity *)point->shape2->GetBody()->GetUserData();
					entity->UntouchGround();
				}
			}
		    
			void Result(const b2ContactResult* point)
			{
				//std::cout << "Result?\n";
			}

		};

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