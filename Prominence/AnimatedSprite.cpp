#include "AnimatedSprite.h"


namespace Prominence {


	AnimatedSprite::AnimatedSprite(ResourceManager & rm, Renderer & renderer, Logger & logger, std::string xml_file) : Sprite(rm, renderer), m_Logger(logger)
	{
		m_FrameTimer = m_CurrentFrame = 0;
		m_CurrentSequence = NULL;

		TiXmlDocument doc(xml_file.c_str());

		if (!doc.LoadFile())
		{
			m_Logger.Outputf(P_WARNING, OTHER, "Failed to load XML %s.\n", xml_file.c_str());
		}




		TiXmlElement * root = doc.FirstChildElement("sprites");
		TiXmlElement * sprite = root->FirstChildElement("sprite");

		TiXmlElement * elem = sprite->FirstChildElement("texture");

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
			m_CurrentSequence = seq;
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

	}

	void AnimatedSprite::Render(GLfloat x, GLfloat y)
	{
		x -= m_CurrentSequence->frames[m_CurrentFrame]->xAnchor;
		y -= m_CurrentSequence->frames[m_CurrentFrame]->yAnchor;
		Quad & quad = m_CurrentSequence->frames[m_CurrentFrame]->quad;

		int width = m_CurrentSequence->frames[m_CurrentFrame]->width;
		int height = m_CurrentSequence->frames[m_CurrentFrame]->height;

		quad.v[0].x = x;			quad.v[0].y = y;
		//quad.v[0].tx = 0; quad.v[0].ty = 0; quad.v[0].x = 0; quad.v[0].y = 0; quad.v[0].color[3] = 0;
		//quad.v[1].tx = 1; quad.v[1].ty = 0; 
		quad.v[1].x = x+width;		quad.v[1].y = y; //quad.v[1].color[3] = 0;
		//quad.v[2].tx = 1; quad.v[2].ty = 1; 
		quad.v[2].x = x+width;		quad.v[2].y = y+height;// quad.v[2].color[3] = 0;
		//quad.v[3].tx = 0; quad.v[3].ty = 1; 
		quad.v[3].x = x;			quad.v[3].y = y+height; //quad.v[3].color[3] = 0;
		//std::cout << "rendering " << m_CurrentSequence->frames[m_CurrentFrame]->texture->GetId() << '\n';
		m_Renderer.AddQuad(m_CurrentSequence->frames[m_CurrentFrame]->texture->GetId(), quad);
	}

	void AnimatedSprite::Update(Uint32 dt)
	{
		m_FrameTimer += dt;
		if (m_FrameTimer > m_CurrentSequence->frames[m_CurrentFrame]->time * 1000)
		{
			m_FrameTimer -= m_CurrentSequence->frames[m_CurrentFrame]->time * 1000;
			m_CurrentFrame++;
			if (m_CurrentFrame >= m_CurrentSequence->frames.size()) m_CurrentFrame = m_CurrentSequence->returnLoopFrame;
		}
		//std::cout << m_CurrentSequence->name << " " << m_FrameTimer << '\n';
	}

	void AnimatedSprite::Animate(std::string sequence_name)
	{
		if (sequence_name == m_CurrentSequence->name)
			return;

		std::vector<Sequence *>::iterator i;
		
		for (i = sequences.begin(); i != sequences.end(); ++i)
		{
			if (sequence_name == (*i)->name)
			{
				m_CurrentSequence = (*i);
				m_CurrentFrame = 0;
				m_FrameTimer = 0;
				return;
			}
		}

	}
}
