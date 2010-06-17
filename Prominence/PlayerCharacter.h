#pragma once

#include "Export.h"
#include "Actor.h"
#include "InputDevice.h"

namespace Prominence {


	class DECLSPEC PlayerCharacter :
		public Actor
	{
		//enum Class {Janitor, Rocktard, Voodoo, Ninja};
	private:
		InputDevice &m_InputDevice;
	public:
		PlayerCharacter(AnimatedSprite & sprite, b2Body & body, InputDevice &device);
		~PlayerCharacter(void);
		void Update(Uint32 dt);
		//void SetClass(CharacterClass *cclass) { m_Class = cclass; }

	};

}