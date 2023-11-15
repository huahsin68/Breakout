#ifndef __GAMELEVEL_H__
#define __GAMELEVEL_H__

#include "HeaderSymbol.h"

#include <iostream>
#include <list>
#include <sstream>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "StateController.h"
#include "Paddle.h"
#include "Wall.h"
#include "Ball.h"
#include "Bullet.h"
#include "Block.h"
#include "Gate.h"
#include "Resource.h"
#include "Score.h"
#include "MenuScreen.h"
#include "GameOverScreen.h"
#include "pugixml.hpp"
#include "MyDebugDraw.h"


using namespace std;

struct isDispose
{
	bool operator() (GameObject* obj)
	{
		PhysicProp *p = obj->getPhysicProp();
		return obj->getDispose();
	}
};

struct LevelProp
{
	int rowCount = 0;
	int colCount = 0;
	int level[5][20]; // max element is 18 block in each row
	bool gate[4] = {false, false, false, false};
};

class GameLevelState;

class GameLevel
{
public:
	GameLevel();
	virtual ~GameLevel();

	Bullet* createBullet(b2Vec2);
	inline GameObject* getBall() {
		return ball;
	}
	inline GameObject* getPaddle() {  // return primary paddle
		return paddle;
	}
	inline list<GameObject*> getPaddles() {
		return paddles;
	}
	virtual void invokeKey(int, bool);
	virtual void launchGame();
	void render();
	virtual void renderGameOverScreen();
	virtual void renderGamePlay();
	virtual void renderMenuScreen();
	void restartGame();
	void stepPhysicWorld(int);
	void setAnimationShader(unsigned int shader) {
		shaderAnimation = shader;
	}
	void setMultiInstanceShader(unsigned int shader) {
		this->shader = shader;
	}
	void setSingleInstanceShader(unsigned int shader) {
		shaderSingleInstance = shader;
	}


private:
	void enableDebugDraw();
	GameObject* generateWall(ObjectType, b2Vec2, WallProp*);
	void genWallGap(int, WallProp*);
	virtual void loadBlocks();
	void resetBlock();


private:
	static GameLevel *instance;

	int timeFrame = 0;
	int desiredPhysicFPS = 500; // the smaller the number, the faster
	int physicFps = 1000/desiredPhysicFPS;

	int desiredAnimFPS = 250;
	int animFps = 1000/desiredAnimFPS;


protected:
	bool loadImage();
	Block* createBlock(int);

	b2Vec2 gravity;
	b2World *physicWorld = nullptr;

	unsigned int shader = 0;
	unsigned int shaderSingleInstance = 0;
	unsigned int shaderAnimation = 0;
	
	glm::mat4 transWallVertical = glm::mat4(1.f);
	glm::mat4 transWallHorizontal = glm::mat4(1.f);
	glm::mat4 *instanceBox = new glm::mat4[2];

	GameObject *paddle = nullptr;  // primary paddle
	GameObject *bottomWall = nullptr;
	GameObject *topWallGate = nullptr;
	GameObject *leftWallGate = nullptr;
	GameObject *rightWallGate = nullptr;
	GameObject *ball = nullptr;

	list<GameObject*> blocks;
	list<GameObject*> bullets;
	list<GameObject*> walls;
	list<GameObject*> paddles;

	pugi::xml_document doc;
	pugi::xml_parse_result docStatus;

	MyDebugDraw mydebugdraw;

	LevelProp *levelProp = new LevelProp();

	Resource* spriteRes = nullptr;
	
	Score *score = nullptr;
	MenuScreen *menuScreen = nullptr;
	GameOverScreen *gameOverScreen = nullptr;

	float animFrameIndex = 0.f;
};


#endif /* __GAMELEVEL_H_ */
