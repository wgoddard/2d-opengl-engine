#include "AnimatedSprite.h"


namespace Prominence {


	AnimatedSprite::AnimatedSprite(ResourceManager & rm, Renderer & renderer, Logger & logger, std::string xml_file) : Sprite(rm, renderer), m_Logger(logger)
	{

		TiXmlDocument doc(xml_file.c_str());

		if (!doc.LoadFile())
		{
			m_Logger.Outputf(P_WARNING, OTHER, "Failed to load XML %s.\n", xml_file.c_str());
		}


		TiXmlElement * root = doc.FirstChildElement("sprites");
		TiXmlElement * sprite = root->FirstChildElement("sprite");

		TiXmlElement * elem = sprite->FirstChildElement("texture");

		TiXmlElement * rect = sprite->FirstChildElement("rect");

		if (rect == NULL)
		{
			m_Logger.Outputf(P_WARNING, OTHER, "%s (%s) has no bounding rect.\n", sprite->Attribute("Name"), xml_file);
			throw("No bounding");
		}
		float rW, rH = 5.0f;
		m_PolyDef = new b2PolygonDef();
		rW = atof(rect->Attribute("Width")) / 2.0f / PIXELS_PER_UNIT;
		rH = atof(rect->Attribute("Height")) / 2.0f / PIXELS_PER_UNIT;
		m_PolyDef->SetAsBox(rW, rH);
		m_PolyDef->density = 1.0f;

		if (elem == 0)
		{
			//std::cout << "No textures?? error.\n";
			m_Logger.Outputf(P_ERROR, OTHER, "%s has no textures.\n", sprite->Attribute("Name"));
			exit(0);
		}

		struct texture
		{
			Texture * loaded_tex;
			Uint32 width;
			Uint32 height;
		};

		std::vector <texture *> textures;

		do
		{
			texture * tex = new texture;
			tex->loaded_tex = m_ResourceManager.GetTexture(elem->Attribute("File"));
			tex->width = atoi(elem->Attribute("Width"));
			tex->height = atoi(elem->Attribute("Height"));
			textures.push_back(tex);
		} while (elem = elem->NextSiblingElement("texture"));

		elem = sprite->FirstChildElement("sequence");

		if (elem == NULL)
		{
			std::cout << "No sequences? error.\n";
			exit(0);
		}


		do
		{

			Sequence *seq = new Sequence();

			seq->name = elem->Attribute("Name");
			seq->returnLoopFrame = atoi(elem->Attribute("Return_Loop_Frame"));
			seq->loops = atoi(elem->Attribute("Loops"));
			//std::cout << seq->name << '\n';

			TiXmlElement * frameElem = elem->FirstChildElement("frame");

			if (frameElem == 0) std::cout << "No frames. Error.\n";

			do
			{
				Frame * frame = new Frame();
				frame->time = atof(frameElem->Attribute("Time"));
				//Tex_X="206" Tex_Y="549" Width="39" Height="54" Anchor_X="19.5" Anchor_Y="27" Texture="0" />
				int tex_x = atoi(frameElem->Attribute("Tex_X"));
				int tex_y = atoi(frameElem->Attribute("Tex_Y"));
				int width = atoi(frameElem->Attribute("Width"));
				int height = atoi(frameElem->Attribute("Height"));
				int texindex = atoi(frameElem->Attribute("Texture"));
				float xAnchor = atof(frameElem->Attribute("Anchor_X"));
				float yAnchor = atof(frameElem->Attribute("Anchor_Y"));
				Texture * texid = textures[texindex]->loaded_tex;

				frame->texture = texid;
				//GLfloat color[4] = {0};
				for (int i = 0; i < 4; ++i)
				{
					for (int j = 0; j < 4; ++j)
					{
						frame->quad.v[i].color[j] = 0.5f;
					}
				}
				frame->quad.z = 0.5f;

				frame->width = width;
				frame->height = height;
				frame->xAnchor = xAnchor;
				frame->yAnchor = yAnchor;

				int texW = textures[texindex]->width;
				int texH = textures[texindex]->height;

				frame->quad.v[0].tx = (GLfloat)tex_x / texW;				frame->quad.v[0].ty = (GLfloat)tex_y / texH;
				frame->quad.v[1].tx = (GLfloat)(tex_x + width) / texW;		frame->quad.v[1].ty = (GLfloat)tex_y / texH;
				frame->quad.v[2].tx = (GLfloat)(tex_x + width) / texW;		frame->quad.v[2].ty = (GLfloat)(tex_y + height) / texH;
				frame->quad.v[3].tx = (GLfloat)tex_x / texW;				frame->quad.v[3].ty = (GLfloat)(tex_y + height) / texH;

				seq->frames.push_back(frame);
			} while (frameElem = frameElem->NextSiblingElement("frame"));

			sequences.push_back(seq);
		} while(elem = elem->NextSiblingElement("sequence"));


		//clean up temp texture list
		std::vector<texture *>::iterator i;
		for (i = textures.begin(); i != textures.end(); ++i)
		{
			delete (*i);
		}

		//std::cout << elem->Attribute("File") << "\nblabla\n";
	}

	AnimatedSprite::~AnimatedSprite(void)
	{
		std::vector<Sequence *>::iterator i;

		for (i = sequences.begin(); i != sequences.end(); ++i)
		{
			std::vector<Frame *>::iterator j;
			for (j = (*i)->frames.begin(); j != (*i)->frames.end(); ++j)
			{
				delete (*j);
			}
			delete (*i);

		}

		delete m_PolyDef;

	}

	void AnimatedSprite::Render(GLfloat x, GLfloat y, Uint32 sequence, Uint32 frame, bool hflip)
	{
		Frame * workingFrame = sequences[sequence]->frames[frame];

		x -= workingFrame->xAnchor;
		y -= workingFrame->yAnchor;
		Quad quad = workingFrame->quad;

		int width = workingFrame->width;
		int height = workingFrame->height;

		quad.v[0].x = x;			quad.v[0].y = y;
		//quad.v[0].tx = 0; quad.v[0].ty = 0; quad.v[0].x = 0; quad.v[0].y = 0; quad.v[0].color[3] = 0;
		//quad.v[1].tx = 1; quad.v[1].ty = 0; 
		quad.v[1].x = x+width;		quad.v[1].y = y; //quad.v[1].color[3] = 0;
		//quad.v[2].tx = 1; quad.v[2].ty = 1; 
		quad.v[2].x = x+width;		quad.v[2].y = y+height;// quad.v[2].color[3] = 0;
		//quad.v[3].tx = 0; quad.v[3].ty = 1; 
		quad.v[3].x = x;			quad.v[3].y = y+height; //quad.v[3].color[3] = 0;
		//std::cout << "rendering " << m_CurrentSequence->frames[m_CurrentFrame]->texture->GetId() << '\n';

		if (hflip)
		{
			GLfloat temp = quad.v[0].tx;
			quad.v[0].tx  = quad.v[1].tx;
			quad.v[1].tx = temp;
			temp = quad.v[2].tx;
			quad.v[2].tx = quad.v[3].tx;
			quad.v[3].tx = temp;

		}

		m_Renderer.AddQuad(workingFrame->texture->GetId(), quad);
	}

}
