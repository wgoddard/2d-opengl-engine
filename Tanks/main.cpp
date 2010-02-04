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
//AnimatedSprite * kis;

Entity * megaman;
Entity * megaman2;
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
			case SDL_KEYDOWN:
			{
				if (event.key.keysym.sym == SDLK_z)
				{
					e.Resize(800, 600, 32, true);
					std::cout << "Hello";
				}
				switch (event.key.keysym.sym)
				{
				case SDLK_a:
					//kis->Animate("Attack");
					//anim->Animate("Enter");
					megaman->Left(true);
					break;
				case SDLK_s:
					//kis->Animate("Still");
					//anim->Animate("Still");
					break;
				case SDLK_d:
					//kis->Animate("Walking");
					//anim->Animate("Running");
					megaman->Right(true);
					break;
				case SDLK_f:
					//anim->Animate("Injured");
					break;
				case SDLK_g:
					//anim->Animate("Skidding");
					break;
				case SDLK_h:
					//anim->Animate("Shooting");
					break;
				case SDLK_w:
					megaman->Jump(true);
					break;
				case SDLK_ESCAPE:
					return false;
				}
			}
			break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym)
				{
				case SDLK_a:
					megaman->Left(false);
					break;
				case SDLK_d:
					megaman->Right(false);
					break;
				}
				break;
		}
	}

	if (e.GetKeyDown(SDLK_RIGHT))
	{
		//AnimatedSprite leaktest(e.GetResourceManager(), e.GetRenderer(), e.GetLogger(), "megaman6b.txt");
		x++;
	}
	//SDL_Delay(12);
	return true;
}

bool RenderFunc()
{
	//e.GetRenderer().StartFrame();
	e.GetRenderer().ClearFrame();
	e.GetWorld().Update(e.GetDelta());


	//e.GetWorld().DrawBoxes();
	sprite->Render(0,0);
	wall->Render(5/44, 0);
	megaman->Render();
	megaman2->Render();






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

	megaman = e.CreateEntity(anim, 0.10f, 20);//new Entity(*anim);
	megaman2 = e.CreateEntity(anim, 10.0f, 20);
	//anim = new AnimatedSprite("gintoki.txt");
	//kis = new AnimatedSprite("kis4.txt");



	e.SetFrameFunc(&FrameFunc);
	e.SetRenderFunc(&RenderFunc);

	e.Execute();

	delete sprite;
	delete anim;
	//delete kis;
	delete megaman;
	delete megaman2;

	e.GetLogger().Outputf(P_WARNING, AUDIO, "No sound yet!\n");



	return 0;
}