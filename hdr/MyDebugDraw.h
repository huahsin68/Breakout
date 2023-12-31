#ifndef __MYDEBUGDRAW_H_
#define __MYDEBUGDRAW_H_


#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "box2d/box2d.h"
#include <glm/glm.hpp>


using namespace std;

class MyDebugDraw : public b2Draw
{
public:
    MyDebugDraw();
    ~MyDebugDraw();
    // We won't be implementing all of these, but if we don't declare them here we'll get an override error
    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
    void DrawCircle(const b2Vec2& center, float radius, const b2Color& color);
    void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color);
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
    void DrawTransform(const b2Transform& xf);
    void DrawPoint(const b2Vec2& p, float size, const b2Color& color);
};

#endif
