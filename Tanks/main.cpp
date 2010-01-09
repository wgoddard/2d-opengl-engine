#include "..\Prominence\Prominence.h"
//#include "..\Prominence\Engine.h"
#include "SimpleSprite.h"
#include "AnimatedSprite.h"
#include "Entity.h"

using namespace Prominence;
Engine e(E_DEBUG);

SimpleSprite * sprite;
AnimatedSprite * anim;
//AnimatedSprite * kis;

Entity * megaman;

float x; float y;

bool FrameFunc()
{
	//std::cout << "Hello\n";
	//std::cout << e.GetDelta() << '\n';
	e.Delay(10);
	char delta[10];
	_itoa(e.GetDelta(), delta, 9);
	char fps[10];
	_itoa(e.GetFPS(), fps, 9);
	std::string name = std::string("Engine delta:") + delta + std::string(" fps: ") + fps;

	//anim->Update(e.GetDelta());
	//kis->Update(e.GetDelta());
	megaman->Update(e.GetDelta());
	
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
					e.Resize(300, 200, 32, true);
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
	e.GetRenderer().StartFrame();
	e.GetRenderer().ClearFrame();


	//sprite->Render((float)(x/5),100);
	//anim->Render(x/2.5, 100);
	//kis->Render(x/100, 600-256);
	megaman->Render();

	e.GetRenderer().EndFrame();

	return true;
}

int main(int argc, char *argv[])
{	
	//Engine e(E_DEBUG);
	//Engine f;
	e.SetName("WordXX");
	//e.SetMode(E_RELEASE);
	//e.Resize(300, 200, 32, false);
	//e.GetWindow().ToggleFullscreen();

	e.Initialize();

	//sprite = new SimpleSprite("A.png", 0.25f, 0.25f, 256, 256, 512, 512);

	anim = e.CreateSprite("megaman6b.txt");
	//kis = e.CreateSprite("kis5.txt");
	sprite = e.CreateSprite("A.png", 0.25f, 0.25f, 256, 256, 512, 512);

	megaman = new Entity(*anim);
	//anim = new AnimatedSprite("gintoki.txt");
	//kis = new AnimatedSprite("kis4.txt");



	e.SetFrameFunc(&FrameFunc);
	e.SetRenderFunc(&RenderFunc);

	e.Execute();

	delete sprite;
	delete anim;
	//delete kis;
	delete megaman;

	e.GetLogger().Outputf(P_WARNING, AUDIO, "No sound yet!\n");


	return 0;
}