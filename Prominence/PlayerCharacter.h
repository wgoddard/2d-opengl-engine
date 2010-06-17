#pragma once

#include "Export.h"
#include "Actor.h"
#include "InputDevice.h"

namespace Prominence {


	class DECLSPEC PlayerCharacter :
		public Actor
	{
		//enum Class {Janitor, Rocktard, Voodoo, Ninja};
	protected:
		InputDevice &m_InputDevice;
		Uint16 m_Busy;
	public:
		PlayerCharacter(AnimatedSprite & sprite, b2Body & body, InputDevice &device);
		virtual ~PlayerCharacter(void);
		void Update(Uint32 dt);
		//void SetClass(CharacterClass *cclass) { m_Class = cclass; }

	};

}