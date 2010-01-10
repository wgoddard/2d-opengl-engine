#pragma once
#include "Box2d.h"
#include "Export.h"
#include "SDL_opengl.h"

namespace Prominence {

	class DECLSPEC DebugDraw :
		public ::b2DebugDraw
	{
	public:
		DebugDraw(void);
		virtual ~DebugDraw(void);
		void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
		void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
		void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
		void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
		void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
		void DrawXForm(const b2XForm& xf);
		void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);
		void DrawString(int x, int y, const char* string, ...); 
		void DrawAABB(b2AABB* aabb, const b2Color& color);


	};

}