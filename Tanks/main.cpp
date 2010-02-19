#include "..\Prominence\Prominence.h"
//#include "..\Prominence\Engine.h"
#include "..\Prominence\SimpleSprite.h"
#include "..\Prominence\AnimatedSprite.h"
#include "..\Prominence\Entity.h"


using namespace Prominence;
Engine e(E_DEBUG);

SimpleSprite * sprite;
SimpleSprite * wall;
AnimatedSprite * anim;
AnimatedSprite * iso;
//AnimatedSprite * kis;

Entity * megaman;
Entity * megaman2;
IsoEntity * archer;
//World * world;

float x; float y;

bool FrameFunc()
{

	//std::cout << "Hello\n";
	//std::cout << e.GetDelta() << '\n';
	//e.Delay(10);
	char delta[10];
	_itoa(e.GetDelta(), delta, 10);
	char fps[10];
	_itoa(e.GetFPS(), fps, 10);
	char hz[10];
	_snprintf(hz, 9, "%.3f", e.GetDelta()/1000.0f);
	std::string name = std::string("Engine delta:") + delta + std::string(" fps: ") + fps + std::string(" timestep ") + hz;

	//std::cout << "Fps should be " << 1000.0f/e.GetDelta() << '\n';

	//std::cout << "FPS: " << e.GetFPS() << " but is listed as " << fps << '\n';
	

	//anim->Update(e.GetDelta());
	//kis->Update(e.GetDelta());
	megaman->Update(e.GetDelta());
	megaman2->Update(e.GetDelta());
	archer->Update(e.GetDelta());
	//world->Update(e.GetDelta());
	
	e.SetName(name);

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
			{
				return false;
			}
			break;
			case SDL_MOUSEMOTION:
				{
				int x = event.motion.x;
				int y = event.motion.y;
				double angle = atan2((double)y-300, (double)x-400);
				//std::cout << "Angle is " << angle << '\n';
				archer->SetAngle(angle);
				}

				break;
			case SDL_MOUSEBUTTONDOWN:
				std::cout << "Archer is at " << archer->GetPos().x << ", " << archer->GetPos().y << '\n';
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_z)
				{
					//archer->UpdateState();
				}
				switch (event.key.keysym.sym)
				{
				case SDLK_a:
					archer->Left(true);
					break;
				case SDLK_d:
					archer->Right(true);
					break;
				case SDLK_w:
					archer->Up(true);
					break;
				case SDLK_s:
					archer->Down(true);
					break;
				case SDLK_ESCAPE:
					return false;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym)
				{
				case SDLK_a:
					archer->Left(false);
					break;
				case SDLK_d:
					archer->Right(false);
					break;
				case SDLK_w:
					archer->Up(false);
					break;
				case SDLK_s:
					archer->Down(false);
					break;
				}
				break;
		}
	}

	return true;
}

bool RenderFunc()
{
	e.GetRenderer().StartFrame();
	e.GetRenderer().ClearFrame();

	//Update it in here for now because b2d's built in debugdraw happens in update
	e.GetWorld().Update(e.GetDelta());
	

	b2Vec2 pos = archer->GetPos();

	e.GetRenderer().ViewAt(-pos.x, -pos.y);
	//e.GetRenderer().ViewAt(-400/44, -600/44);
	//glTranslatef(pos.x, pos.y, 0);


	//e.GetWorld().DrawBoxes();
	sprite->Render(-1/44.0f,-1/44.0f);
	wall->Render(5/44, 0);
	//megaman->Render();
	//megaman2->Render();
	archer->Render();





	e.GetWorld().Render();

	e.GetRenderer().EndFrame();

	return true;
}

int main(int argc, char *argv[])
{	
	//Engine e(E_DEBUG);
	//Engine f;
	e.SetName("WordXX");
	//e.SetMode(E_RELEASE);
	//e.Resize(640, 640, 32, false);
	//e.GetWindow().ToggleFullscreen();

	e.Initialize();

	//world = new World(e.GetLogger());

	//sprite = new SimpleSprite("A.png", 0.25f, 0.25f, 256, 256, 512, 512);

	anim = e.CreateSprite("megaman6c.txt");
	wall = e.CreateSprite("wall.png", 0.0f, 0.0f, 240/44, 480/44, 240/44, 480/44);
	//kis = e.CreateSprite("kis5.txt");
	sprite = e.CreateSprite("bg.png", 0.0f, 0.0f, 480/22, 320/22, 480/22, 320/22);

	megaman = e.CreateEntity(anim, 18, 2.5);//new Entity(*anim);
	megaman2 = e.CreateEntity(anim, 12, 2.5);

	iso = e.CreateSprite("blue archer.xml");
	archer = e.CreateIsoEntity(iso, 6, 2.5);
	//anim = new AnimatedSprite("gintoki.txt");
	//kis = new AnimatedSprite("kis4.txt");



	e.SetFrameFunc(&FrameFunc);
	e.SetRenderFunc(&RenderFunc);

	e.Execute();

	delete sprite;
	delete anim;
	//delete kis;
	//delete megaman;
	//delete megaman2;
	delete iso;
	delete archer;

	e.GetLogger().Outputf(P_WARNING, AUDIO, "No sound yet!\n");



	return 0;
}