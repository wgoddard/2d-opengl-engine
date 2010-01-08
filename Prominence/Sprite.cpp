#include "Sprite.h"

namespace Prominence {

Sprite::Sprite(ResourceManager & rm, Renderer & renderer) : m_ResourceManager(rm), m_Renderer(renderer)
{
}

Sprite::~Sprite(void)
{
}

} // Exit Prominence Namespace