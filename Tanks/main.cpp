#include "..\Prominence\Prominence.h"
//#include "..\Prominence\Engine.h"
#include "..\Prominence\SimpleSprite.h"
#include "..\Prominence\AnimatedSprite.h"
#include "..\Prominence\Entity.h"
#include "..\Prominence\InputHandler.h"


using namespace Prominence;
Engine e(E_DEBUG);

InputHandler inputHandler;

SimpleSprite * sprite;
SimpleSprite * wall;
AnimatedSprite * anim;
AnimatedSprite * iso;
//AnimatedSprite * kis;

Entity * megaman;
Entity * megaman2;
IsoActor * archer;
//World * world;

float x; float y;

bool FrameFunc()
{

	inputHandler.Poll();

	e.Delay(10);
	e.GetWorld().Update(e.GetDelta());
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
	//megaman->Update(e.GetDelta());
	//megaman2->Update(e.GetDelta());
	//archer->Update(e.GetDelta());
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
				case SDLK_z:
					std::cout << "Woot\n\n\n";
					e.GetWorld().NextLevel();
					archer = e.GetWorld().CreateIsoActor(iso, 126, 93);
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
	e.GetWorld().Render();
	

	b2Vec2 pos = archer->GetPos();

	e.GetRenderer().ViewAt(-pos.x*PPU, -pos.y*PPU);
	//e.GetRenderer().ViewAt(400, 600);
	//e.GetRenderer().ViewAt(126*44, 93*44);


	//e.GetWorld().DrawBoxes();
	sprite->Render(-1/44.0f,-1/44.0f);
	wall->Render(5/44, 0);
	//megaman->Render();
	//megaman2->Render();
	//archer->Render();


	e.GetRenderer().EndFrame();

	return true;
}

int main(int argc, char *argv[])
{	
	//Engine e(E_DEBUG);
	//Engine f;
	//e.SetName("WordXX");
	//e.SetMode(E_RELEASE);
	//e.SetWindow(1280, 720, 32, false);
	e.Resize(1024, 768, 32, false);
	//e.GetWindow().ToggleFullscreen();

	e.Initialize();

	e.GetWorld().SetWorldFile("..\\Resources\\Levels\\royal2.txt");
	e.GetWorld().NextLevel();

	//world = new World(e.GetLogger());

	//sprite = new SimpleSprite("A.png", 0.25f, 0.25f, 256, 256, 512, 512);

	anim = e.CreateSprite("..\\Resources\\megaman6c.txt");
	wall = e.CreateSprite("..\\Resources\\wall.png", 0.0f, 0.0f, 240/FPU, 480/FPU, 240/FPU, 480/FPU);
	//kis = e.CreateSprite("kis5.txt");
	sprite = e.CreateSprite("..\\Resources\\bg.png", 0.0f, 0.0f, 480/22, 320/22, 480/22, 320/22);

	//megaman = e.CreateEntity(anim, 18, 2.5);//new Entity(*anim);
	//megaman2 = e.CreateEntity(anim, 12, 2.5);
	//megaman = e.GetWorld().CreateAnimatedEntity(anim, 18, 2.5);
	megaman2 = e.GetWorld().CreateAnimatedEntity(anim, 12, 2.5);
	megaman = e.GetWorld().CreateActor(anim, 18, 2.5);

	iso = e.CreateSprite("..\\Resources\\blue archer.xml");
	//archer = e.CreateIsoActor(iso, 6, 2.5);
	 archer = e.GetWorld().CreateIsoActor(iso, 126, 93);
	//archer = e.GetWorld().CreateIsoActor(iso, 12, 2.5);
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
	//delete archer;

	e.GetLogger().Outputf(P_WARNING, AUDIO, "No sound yet!\n");



	return 0;
}