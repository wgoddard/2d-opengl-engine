#include "World.h"


namespace Prominence { 

	World::World(ResourceManager & resourceManager, Logger & logger, Renderer & renderer) : m_Logger(logger), m_Renderer(renderer), m_ResourceManager(resourceManager)
	{

		m_LevelIndex = 0;
		m_WorldFile = "";


		m_CurrentLevel = new Level(m_ResourceManager, m_Renderer);
	}

	World::~World(void)
	{
		delete m_CurrentLevel;
	}

	void World::NextLevel()
	{
		Level * nextLevel = new Level(m_ResourceManager, m_Renderer);

		if (nextLevel->LoadXML(m_Logger, m_WorldFile, m_LevelIndex + 1) )
		{
			delete m_CurrentLevel;
			m_CurrentLevel = nextLevel;
			m_Logger.Outputf(P_INFO, WORLD, "Successfully advanced levels.\n");
		}
		else
		{
			m_Logger.Outputf(P_WARNING, WORLD, "Failed to advance levels.\n");
			delete nextLevel;
		}
	}

	void World::Update(Uint32 dt)
	{
		m_CurrentLevel->Update(dt);
	}

	void World::Render()
	{
		m_CurrentLevel->Render();
	}

	//Quad World::GetBody()
	//{
	//	Quad q = {0};
	//	b2Vec2 pos = body->GetPosition();
	//	
	//	q.z = 0.5f;
	//	q.v[0].x = pos.x;		q.v[0].y = pos.y;
	//	q.v[1].x = pos.x + 50;	q.v[1].y = pos.y;
	//	q.v[2].x = pos.x + 50;	q.v[2].y = pos.y + 50;
	//	q.v[3].x = pos.x;		q.v[3].y = pos.y + 50;
	//	
	//	return q;
	//}

	b2Body * World::CreateBody(b2PolygonDef * polyDef, float x, float y)
	{
		return m_CurrentLevel->CreateBody(polyDef, x, y);
	}

	Entity * World::CreateEntity(Sprite * sprite, float x, float y)
	{
		//b2Body * body = CreateBody(sprite->GetPolyDef(), x, y);
		Entity * e = new Entity(*sprite, x, y);
		m_CurrentLevel->AddEntity(e);
		return e;
	}

	AnimatedEntity * World::CreateAnimatedEntity(AnimatedSprite * sprite, float x, float y)
	{
		AnimatedEntity * e = new AnimatedEntity(*sprite, x, y);
		m_CurrentLevel->AddEntity(e);
		return e;
	}

	Actor * World::CreateActor(AnimatedSprite * sprite, float x, float y)
	{
		b2Body * body = m_CurrentLevel->CreateBody(sprite->GetPolyDef(), x, y);
		Actor * e = new Actor(*sprite, *body);
		m_CurrentLevel->AddEntity(e);
		return e;
	}

	IsoActor * World::CreateIsoActor(AnimatedSprite * sprite, float x, float y)
	{
		b2Body * body = m_CurrentLevel->CreateBody(sprite->GetPolyDef(), x, y);
		IsoActor * e = new IsoActor(*sprite, *body);
		m_CurrentLevel->AddEntity(e);
		return e;
	}

}
