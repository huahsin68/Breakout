#include "MyDebugDraw.h"

MyDebugDraw::MyDebugDraw()
{
}

MyDebugDraw::~MyDebugDraw()
{
}

void MyDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) 
{
	glBegin(GL_LINES);
        glColor3f(1, 1, 1);
        glVertex2f(vertices[0].x, vertices[0].y);
        glVertex2f(vertices[1].x, vertices[1].y);
        glVertex2f(vertices[1].x, vertices[1].y);
        glVertex2f(vertices[2].x, vertices[2].y);
        glVertex2f(vertices[2].x, vertices[2].y);
        glVertex2f(vertices[3].x, vertices[3].y);
        glVertex2f(vertices[3].x, vertices[3].y);
        glVertex2f(vertices[0].x, vertices[0].y);
    glEnd();
}

void MyDebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
	float cx = center.x;
    float cy = center.y;
    int numSegment = 50;
    float theta = 3.1415926 * 2.f / float(numSegment);
    float tangetial_factor = tanf(theta);//calculate the tangential factor
    float radial_factor = cosf(theta);//calculate the radial factor
    float x = radius;//we start at angle = 0
    float y = 0.f;

    glBegin(GL_LINE_LOOP);
    glColor3f(1, 1, 1);
    for (int ii = 0; ii < numSegment; ii++) {
        glVertex2f(x + cx, y + cy);//output vertex

        //calculate the tangential vector
		//remember, the radial vector is (x, y)
		//to get the tangential vector we flip those coordinates and negate one of them

		float tx = -y;
		float ty = x;

		//add the tangential vector

		x += tx * tangetial_factor;
		y += ty * tangetial_factor;

		//correct using the radial factor

		x *= radial_factor;
		y *= radial_factor;
    }
    glEnd();
}

void MyDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    glBegin(GL_LINES);
    	glColor3f(1, 1, 1);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
    glEnd();
}

void MyDebugDraw::DrawTransform(const b2Transform& xf) {}
void MyDebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color) {}
// We just need to have these to prevent override errors, they don't actually do anything right now
void MyDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
}

void MyDebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
}
