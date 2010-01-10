#include "DebugDraw.h"

namespace Prominence {

	DebugDraw::DebugDraw(void)
	{
		SetFlags(0xFFFFFFFF);
	}

	DebugDraw::~DebugDraw(void)
	{
	}

	void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		glColor3f(color.r, color.g, color.b);
		glBegin(GL_LINE_LOOP);
		for (int32 i = 0; i < vertexCount; ++i)
		{
			glVertex2f(vertices[i].x, vertices[i].y);
		}
		glEnd();
	}
	void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){}
	void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color){}
	void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color){}

	void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
	{
		glColor3f(color.r, color.g, color.b);
		glBegin(GL_LINES);
		glVertex2f(p1.x, p1.y);
		glVertex2f(p2.x, p2.y);
		glEnd();
	}

	void DebugDraw::DrawXForm(const b2XForm& xf)
	{
		b2Vec2 p1 = xf.position, p2;
		const float32 k_axisScale = 0.4f;
		glBegin(GL_LINES);
		
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(p1.x, p1.y);
		p2 = p1 + k_axisScale * xf.R.col1;
		glVertex2f(p2.x, p2.y);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(p1.x, p1.y);
		p2 = p1 + k_axisScale * xf.R.col2;
		glVertex2f(p2.x, p2.y);

		glEnd();
	}

	void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color){}
	void DebugDraw::DrawString(int x, int y, const char* string, ...){}
	void DebugDraw::DrawAABB(b2AABB* aabb, const b2Color& color)
	{
		//glColor3f(c.r, c.g, c.b);
		glBegin(GL_LINE_LOOP);
		glVertex2f(aabb->lowerBound.x, aabb->lowerBound.y);
		glVertex2f(aabb->upperBound.x, aabb->lowerBound.y);
		glVertex2f(aabb->upperBound.x, aabb->upperBound.y);
		glVertex2f(aabb->lowerBound.x, aabb->upperBound.y);
		glEnd();
	}


}