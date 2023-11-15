#ifndef __HEADERSYMBOL_H__
#define __HEADERSYMBOL_H__


#include <iostream>
#include "box2d/box2d.h"

enum ObjectType {
	LeftWall, RightWall, TopWall, RedBlock, PurpleBlock, YellowBlock, BlueBlock,
	SidePaddle, PrimaryPaddle, ProjectileBall, ProjectileBullet, LeftGate, RightGate,
	TopGate, BottomGate, Unspecified
};

enum BlockType { Red, Purple, Yellow, Blue };

enum GameState { Start, Pause, Play, GameOver };

struct WallProp
{
	int renderGateCount;
	int renderWallCount;
	b2Vec2 gatePhysicLoc;
};


const std::string RES_PATH = "../resources/";
const std::string ROOT_PATH = "../";

#endif /* __HEADERSYMBOL_H__ */
