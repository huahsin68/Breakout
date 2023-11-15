#ifndef __MYCONTACTLISTENER_H_
#define __MYCONTACTLISTENER_H_

#include <iostream>

#include "box2d/box2d.h"

#include "Block.h"
#include "Bullet.h"
#include "Ball.h"
#include "Gate.h"


using namespace std;

class MyContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif
