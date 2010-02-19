#include "World.h"


namespace Prominence { 

	World::World(Logger & logger, Renderer & renderer) : m_Logger(logger), m_Renderer(renderer)
	{

		b2AABB worldAABB;
		worldAABB.lowerBound.Set(0.0f, 0.0f);
		worldAABB.upperBound.Set(1000.0f, 800.0f);


		// Define the gravity vector.
		b2Vec2 gravity(0.0f, 0.0f);

		// Do we want to let bodies sleep?
		bool doSleep = true;

		// Construct a world object, which will hold and simulate the rigid bodies.
		m_b2World = new b2World(worldAABB, gravity, doSleep);

		ContactListener * listen = new ContactListener;
		m_b2World->SetContactListener(listen);

		//b2Version ver = b2g
		//m_Logger.Outputf(P_INFO, OTHER, "Initializing Box2d %i.%i.%i.\n", ver.major, ver.minor, ver.revision);

		//m_b2World->SetDebugDraw(new DebugDraw());

		// Define the ground body.
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(400.0f, 0.0f);

		// Call the body factory which allocates memory for the ground body
		// from a pool and creates the ground box shape (also from a pool).
		// The body is also added to the world.
		b2Body* groundBody = m_b2World->CreateBody(&groundBodyDef);

		// Define the ground box shape.
		b2PolygonDef groundShapeDef;

		// The extents are the half-widths of the box.
		groundShapeDef.SetAsBox(400.0f, 2.0f);

		// Add the ground shape to the ground body.
		groundBody->CreateShape(&groundShapeDef);

		groundShapeDef.SetAsBox(5.0f, 400.0f);
		groundBodyDef.position.Set(0.0f, 0.0f);
		m_b2World->CreateBody(&groundBodyDef)->CreateShape(&groundShapeDef);


		m_CurrentLevel = new Level();
	}

	World::~World(void)
	{
		delete m_b2World;
		delete m_CurrentLevel;
	}

	void World::Update(Uint32 dt)
	{
		int32 iterations = 10;
		//float32 timeStep = 1.0f / 66.0f;
		float32 timeStep = dt / 1000.0f;
		m_b2World->Step(timeStep, iterations);
		m_CurrentLevel->Update(dt);
	}

	void World::Render()
	{
		m_CurrentLevel->Render();
	}

	Quad World::GetBody()
	{
		Quad q = {0};
		b2Vec2 pos = body->GetPosition();
		
		q.z = 0.5f;
		q.v[0].x = pos.x;		q.v[0].y = pos.y;
		q.v[1].x = pos.x + 50;	q.v[1].y = pos.y;
		q.v[2].x = pos.x + 50;	q.v[2].y = pos.y + 50;
		q.v[3].x = pos.x;		q.v[3].y = pos.y + 50;
		
		return q;
	}

	b2Body * World::CreateBody(b2PolygonDef * polyDef, float x, float y)
	{
		b2BodyDef bodyDef;
		bodyDef.fixedRotation = true;
		bodyDef.position.Set(x, y);
		b2Body * body = m_b2World->CreateBody(&bodyDef);
		polyDef->friction = 1.0f;
		polyDef->restitution = 0.0f;
		//bodyDef.linearDamping = 100.0f;
		//bodyDef.
		

		b2PolygonDef feet(*polyDef);

		for (int i = 0; i < 4; ++i) {feet.vertices[i].y -= 0.5f; feet.vertices[i].x *= 0.9f; }
		//feet.vertices[3].y = polyDef->vertices[0].y;
		//feet.vertices[2].y = polyDef->vertices[1].y;
		//feet.vertices[0].y = feet.vertices[3].y += 0.2f;
		//feet.vertices[1].y = feet.vertices[2].y += 0.2f;
		//feet.vertices[0].y = feet.vertices[3].y -= 0.3f;
		//feet.vertices[1].y = feet.vertices[2].y -= 0.3f;

		feet.isSensor = true;
		feet.density = 0.0f;
		feet.filter.
		

		std::cout << "1. x " << polyDef->vertices[0].x << "\t y " << polyDef->vertices[0].y << '\n';
		std::cout << "2. x " << polyDef->vertices[1].x << "\t y " << polyDef->vertices[1].y << '\n';
		std::cout << "3. x " << polyDef->vertices[2].x << "\t y " << polyDef->vertices[2].y << '\n';
		std::cout << "4. x " << polyDef->vertices[3].x << "\t y " << polyDef->vertices[3].y << '\n';


		b2Shape * s = body->CreateShape(&feet);



		


		// Add the shape to the body.
		body->CreateShape(polyDef);

		// Now tell the dynamic body to compute it's mass properties base
		// on its shape.
		body->SetMassFromShapes();


		return body;
	}

	void World::DrawBoxes()
	{
		for (b2Body* b = m_b2World->GetBodyList(); b; b = b->GetNext())
		{
			Quad q = {0};
			b2Shape * shape = b->GetShapeList();
			if (shape == NULL)
			{
				//std::cout << "NILL\n\n\n";
				continue;
			}
			b2AABB bb;

			shape->ComputeAABB(&bb, b[0].GetXForm());

			q.v[0].x = bb.lowerBound.x;		q.v[0].y = bb.lowerBound.y;
			q.v[1].x = bb.upperBound.x;		q.v[1].y = bb.lowerBound.y;
			q.v[2].x = bb.upperBound.x;		q.v[2].y = bb.upperBound.y;
			q.v[3].x = bb.lowerBound.x;		q.v[3].y = bb.upperBound.y;
			q.z = 0.6f;

			m_Renderer.AddFrame(q);
		}
	}

	Entity * World::CreateEntity(AnimatedSprite * sprite, float x, float y)
	{
		b2Body * body = CreateBody(sprite->GetPolyDef(), x, y);
		Entity * e = new Entity(*sprite, *body);
		m_CurrentLevel->AddEntity(e);
		return e;
	}

}
