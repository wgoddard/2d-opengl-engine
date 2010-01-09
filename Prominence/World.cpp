#include "World.h"


namespace Prominence { 

	World::World(Logger & logger) : m_Logger(logger)
	{
		b2AABB worldAABB;
		worldAABB.lowerBound.Set(0.0f, 0.0f);
		worldAABB.upperBound.Set(800.0f, 600.0f);

		// Define the gravity vector.
		b2Vec2 gravity(0.0f, -20.0f);

		// Do we want to let bodies sleep?
		bool doSleep = true;

		// Construct a world object, which will hold and simulate the rigid bodies.
		m_b2World = new b2World(worldAABB, gravity, doSleep);

		// Define the ground body.
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(400.0f, 20.0f);

		// Call the body factory which allocates memory for the ground body
		// from a pool and creates the ground box shape (also from a pool).
		// The body is also added to the world.
		b2Body* groundBody = m_b2World->CreateBody(&groundBodyDef);

		// Define the ground box shape.
		b2PolygonDef groundShapeDef;

		// The extents are the half-widths of the box.
		groundShapeDef.SetAsBox(800.0f, 10.0f);

		// Add the ground shape to the ground body.
		groundBody->CreateShape(&groundShapeDef);

		// Define the dynamic body. We set its position and call the body factory.
		//b2BodyDef bodyDef;
		//bodyDef.position.Set(0.0f, 500.0f);
		//body = m_b2World->CreateBody(&bodyDef);

		// Define another box shape for our dynamic body.
		//b2PolygonDef shapeDef;
		//shapeDef.SetAsBox(1.0f, 1.0f);

		// Set the box density to be non-zero, so it will be dynamic.
		//shapeDef.density = 1.0f;

		// Override the default friction.
		//shapeDef.friction = 0.3f;

		// Add the shape to the body.
		//body->CreateShape(&shapeDef);

		// Now tell the dynamic body to compute it's mass properties base
		// on its shape.
		//body->SetMassFromShapes();

		// Prepare for simulation. Typically we use a time step of 1/60 of a
		// second (60Hz) and 10 iterations. This provides a high quality simulation
		// in most game scenarios.
		///float32 timeStep = 1.0f / 60.0f;
		//int32 iterations = 10;


		// This is our little game loop.
		//for (int32 i = 0; i < 60; ++i)
		//{
		//	// Instruct the world to perform a single step of simulation. It is
		//	// generally best to keep the time step and iterations fixed.
		//	m_World->Step(timeStep, iterations);

		//	// Now print the position and angle of the body.
		//	b2Vec2 position = body->GetPosition();
		//	float32 angle = body->GetAngle();

		//	printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
		//}
	}

	World::~World(void)
	{
		delete m_b2World;
	}

	void World::Update(Uint32 dt)
	{
		int32 iterations = 10;
		float32 timeStep = 1.0f / 120.0f;
		m_b2World->Step(timeStep, iterations);
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

	b2Body * World::CreateBody(Uint32 width, Uint32 height)
	{
		b2BodyDef bodyDef;
		bodyDef.position.Set(100.0f, 500.0f);
		b2Body * body = m_b2World->CreateBody(&bodyDef);

		// Define another box shape for our dynamic body.
		b2PolygonDef shapeDef;
		shapeDef.SetAsBox(width, height);

		// Set the box density to be non-zero, so it will be dynamic.
		shapeDef.density = 1.0f;

		// Override the default friction.
		shapeDef.friction = 0.3f;

		// Add the shape to the body.
		body->CreateShape(&shapeDef);

		// Now tell the dynamic body to compute it's mass properties base
		// on its shape.
		body->SetMassFromShapes();

		return body;
	}

}
