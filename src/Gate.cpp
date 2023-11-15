#include "Gate.h"
#include "StateController.h"

Gate::Gate(b2World* physicWorld, ObjectType gateType, int startPos, int endPos, WallProp *wallProp)
{
	this->physicWorld = physicWorld;

	physicProp->name = "Gate";
	physicProp->objectType = gateType;

	if( gateType == TopGate ) {
		linePos1 = { -0.93f + (startPos * boxWidth), 0.97f };
		linePos2 = { -0.93f + (endPos * boxWidth) + 0.02f, 0.97f };
		initPhysics(linePos1, linePos2);
	}
	else if( gateType == LeftGate ) {
		linePos1 = { -0.99f, 1.f - (startPos * boxHeight) };
		linePos2 = { -0.99f, 1.f - (endPos * boxHeight) };

		initPhysics(linePos1, linePos2);

		wallProp->gatePhysicLoc = {linePos1.y, linePos2.y};
	}
	else if( gateType == RightGate ) {
		linePos1 = { 0.98f, 1.f - (startPos * boxHeight) };
		linePos2 = { 0.98f, 1.f - (endPos * boxHeight) };

		initPhysics(linePos1, linePos2);

		wallProp->gatePhysicLoc = {linePos1.y, linePos2.y};
	}
	else if( gateType == BottomGate ) {
		linePos1 = { -0.93f + (startPos * boxWidth), -0.99f };
		linePos2 = { -0.93f + (endPos * boxWidth) + 0.02f, -0.99f };
		initPhysics(linePos1, linePos2);
	}

}

Gate::~Gate()
{
}

void Gate::collision()
{
	StateController::stateController->switchState(GameOver);
}

void Gate::create(unsigned int)
{
}

void Gate::draw()
{
}
