#include "Level.h"

namespace Prominence {

	Level::Level(ResourceManager &rm, Renderer & renderer) : m_ResourceManager(rm), m_Renderer(renderer)
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

		//ContactListener * listen = new ContactListener;
		//m_b2World->SetContactListener(listen);

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
	}

	Level::~Level(void)
	{

		
		for (unsigned int i = 0; i < m_Entities.size(); ++i)
			delete m_Entities[i];
		delete m_b2World;
	}

	bool Level::LoadXML(Logger & logger, std::string file, int index)
	{

		TiXmlDocument doc(file.c_str());

		if (!doc.LoadFile())
		{
			logger.Outputf(P_WARNING, WORLD, "Failed in XML file %s: couldn't load file.\n", file.c_str());
			return false;
			//m_Logger.Outputf(P_WARNING, OTHER, "Failed to load XML %s.\n", xml_file.c_str());
		}

		

		TiXmlElement * root = doc.FirstChildElement("world");


		//index is 1 based level identifier (world.m_Level starts at 0, but is passed with + 1)
		TiXmlElement * level = root->FirstChildElement("level");
		int indexer = index;
		while (indexer > 1)
		{
			level = level->NextSiblingElement("level");
		}

		if (level == NULL)
		{
			logger.Outputf(P_WARNING, WORLD, "Failed in XML %s: level %i was not found.\n", file.c_str(), index);
			return false;
		}
		else
		{
			m_Name = std::string(level->Attribute("Name"));
		}

		
		////Index all of the image resources
		TiXmlElement * image = root->FirstChildElement("image");
		std::vector<std::string> images;

		if (image == 0)
		{	
			logger.Outputf(P_INFO, WORLD, "%s has no textures.\n", m_Name.c_str());
		}
		else
		{
			do
			{
				images.push_back(std::string(image->Attribute("File")));
			}
			while (image = image->NextSiblingElement("image"));
			logger.Outputf(P_INFO, WORLD, "Indexed %i images while loading level\n", images.size());
		}


		TiXmlElement * layer = level->FirstChildElement("layer");

		int layerIndex = 0;
		if (layer == NULL)
		{
			logger.Outputf(P_WARNING, WORLD, "There are no layers in level %i of %s\n", index, file.c_str());
			return false;
		}
		else
		{
			do
			{
				TiXmlElement * Texture = layer->FirstChildElement("Texture");

				if (Texture == NULL)
				{
					logger.Outputf(P_INFO, WORLD, "No static graphics exist in %s\n", m_Name.c_str());
				}
				else
				{
					do
					{
						TiXmlElement * resource = Texture->FirstChildElement("resource");
						int id = atoi(resource->Attribute("ID"));
						int width = atoi(Texture->Attribute("Width"));
						int height = atoi(Texture->Attribute("Height"));
						//width +=500;
						//height +=500;
						float x = atof(Texture->Attribute("X"));
						float y = atof(Texture->Attribute("Y"));
						SimpleSprite s = SimpleSprite(m_ResourceManager, m_Renderer, images[id], 0, 0, width/FPU, height/FPU, width/FPU, height/FPU);
						//Warning memory leak
						s.StaticRender(x/FPU, y/FPU);
						//AddEntity(new Entity(*s, x/FPU , y/FPU));
					}
					while (Texture = Texture->NextSiblingElement("Texture"));
				}

				TiXmlElement * Rectangle = layer->FirstChildElement("Rectangle");
				if (Rectangle == NULL)
				{
					logger.Outputf(P_INFO, WORLD, "No rectangles exist in layer %s of %s\n", layer->Attribute("Name"), m_Name.c_str());
				}
				else
				{
					
					do
					{
						std::cout << "Making a rectangle\n";
						float x = atof(Rectangle->Attribute("X"));
						float y = atof(Rectangle->Attribute("Y"));
						int width = atoi(Rectangle->Attribute("Width"));
						int height = atoi(Rectangle->Attribute("Height"));

						float awidth = width/2/PPU;
						float aheight = height/2/PPU;

						if (awidth < 0.1) awidth = 0.1;
						if (aheight < 0.1) aheight = 0.1;

						b2BodyDef groundBodyDef;
						groundBodyDef.position.Set(x/PPU, y/PPU);
						b2Body* groundBody = m_b2World->CreateBody(&groundBodyDef);
						b2PolygonDef groundShapeDef;

						// The extents are the half-widths of the box.

						std::cout << "Width = " << width/2/PPU << '\n';


						groundShapeDef.SetAsBox(awidth, aheight);
						//groundShapeDef.SetAsBox(2,2);

						// Add the ground shape to the ground body.
						groundBody->CreateShape(&groundShapeDef);

						//groundShapeDef.SetAsBox(5.0f, 400.0f);
						//groundBodyDef.position.Set(0.0f, 0.0f);
						m_b2World->CreateBody(&groundBodyDef)->CreateShape(&groundShapeDef);
					}
					while (Rectangle = Rectangle->NextSiblingElement("Rectangle"));
				}

				layerIndex++;
			} while (layer = layer->NextSiblingElement("layer"));
		}

		logger.Outputf(P_WARNING, WORLD, doc.Error() ? "there is an xml error\n" : "there is no xml error\n");

		return true;
	}

	void Level::Update(Uint32 dt)
	{
		int32 iterations = 10;
		float32 timeStep = dt / 1000.0f;
		m_b2World->Step(timeStep, iterations);

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
		DrawBoxes();
	}

	void Level::DrawBoxes()
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



			q.v[0].x = bb.lowerBound.x * PPU;		q.v[0].y = bb.lowerBound.y * PPU;
			q.v[1].x = bb.upperBound.x * PPU;		q.v[1].y = bb.lowerBound.y * PPU;
			q.v[2].x = bb.upperBound.x * PPU;		q.v[2].y = bb.upperBound.y * PPU;
			q.v[3].x = bb.lowerBound.x * PPU;		q.v[3].y = bb.upperBound.y * PPU;
			q.z = 0.6f;

			m_Renderer.AddFrame(q);
		}
	}

	b2Body * Level::CreateBody(b2PolygonDef * polyDef, float x, float y)
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
		////std::cout << "2. x " << polyDef->vertices[1].x << "\t y " << polyDef->vertices[1].y << '\n';
		//std::cout << "3. x " << polyDef->vertices[2].x << "\t y " << polyDef->vertices[2].y << '\n';
		//std::cout << "4. x " << polyDef->vertices[3].x << "\t y " << polyDef->vertices[3].y << '\n';


		b2Shape * s = body->CreateShape(&feet);

		// Add the shape to the body.
		body->CreateShape(polyDef);

		// Now tell the dynamic body to compute it's mass properties base
		// on its shape.
		body->SetMassFromShapes();

		return body;
	}

}