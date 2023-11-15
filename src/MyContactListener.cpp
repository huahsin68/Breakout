
#include "MyContactListener.h"


void MyContactListener::BeginContact(b2Contact* contact)
{
	if( contact->IsTouching() ) {
		PhysicProp *objA = reinterpret_cast<PhysicProp*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		PhysicProp *objB = reinterpret_cast<PhysicProp*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

		if ((objA->objectType == BlueBlock || objA->objectType == RedBlock ||
				objA->objectType == YellowBlock || objA->objectType == PurpleBlock)
				&& (objB->objectType == ProjectileBall || objB->objectType == ProjectileBullet)) {
			Block *go = ((Block*)objA->go);
			go->collision();

			if( objB->objectType == ProjectileBullet ) {
				Bullet *bullet = ((Bullet*)objB->go);
				bullet->collision();
			}
		}
		else if ((objB->objectType == BlueBlock || objB->objectType == RedBlock ||
				objB->objectType == YellowBlock || objB->objectType == PurpleBlock)
				&& objA->objectType == ProjectileBall) {
			//((Block*)objB)->collision(objB->go);
			Block *go = ((Block*)objB->go);
			go->collision();
		}
		else if ((objA->objectType == BlueBlock || objA->objectType == RedBlock ||
				objA->objectType == YellowBlock || objA->objectType == PurpleBlock)
				&& objB->objectType == ProjectileBullet) {
			Block *go = ((Block*)objA->go);
			go->collision();
		}
		else if( (objA->objectType == LeftWall || objA->objectType == RightWall ||
				objA->objectType == TopWall) && objB->objectType == ProjectileBullet ) {
			Bullet *bullet = ((Bullet*)objB->go);
			bullet->collision();
		}
		else if( (objA->objectType == LeftGate || objA->objectType == RightGate ||
				objA->objectType == TopGate || objA->objectType == BottomGate) &&
				objB->objectType == ProjectileBall ) {
			Gate *go = ((Gate*)objA->go);
			go->collision();
		}
	}
}

void MyContactListener::EndContact(b2Contact* contact)
{
	PhysicProp *objA = reinterpret_cast<PhysicProp*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
	PhysicProp *objB = reinterpret_cast<PhysicProp*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

	if( objB->objectType == ProjectileBall ) {
		Ball *go = static_cast<Ball*>(objB->go);
		go->collision();
	}
	else if( objA->objectType == ProjectileBall ) {
		Ball *go = static_cast<Ball*>(objA->go);
		go->collision();
	}
}

void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
}

void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}
