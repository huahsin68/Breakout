#include "GameLevel.h"
#include "MyContactListener.h"


StateController *StateController::stateController = StateController::getInstance();
GameLevel *GameLevel::instance = 0;

GameLevel::GameLevel()
{
	StateController::stateController->initState(this);

	spriteRes = new Resource("../resources/breakout_sprites.png");
	
	gravity.x = 0;
	gravity.y = 0;

	physicWorld = new b2World(gravity);
	
	MyContactListener *listener = new MyContactListener();
	physicWorld->SetContactListener(listener);

//	enableDebugDraw();

	StateController::stateController->switchState(Pause);

	menuScreen = new MenuScreen();
	gameOverScreen = new GameOverScreen();
	score = new Score();

	paddle = new Paddle(physicWorld, 8.f, {0.f, -0.95f}, PrimaryPaddle);
	paddles.push_back(paddle);

	ball = new Ball(physicWorld);
	WallProp *wallProp[4];
	wallProp[0] = new WallProp();
	wallProp[1] = new WallProp();
	wallProp[2] = new WallProp();
	wallProp[3] = new WallProp();

	srand((int)time(0));
	leftWallGate = generateWall(LeftWall, {0.f, 0.f}, wallProp[0]);
	rightWallGate = generateWall(RightWall, {1.92f, 0.f}, wallProp[1]);
	topWallGate = generateWall(TopWall, {0.08f, 0.f}, wallProp[2]);

	bottomWall = new Gate(physicWorld, BottomGate, 0, 23);

	string resPath = ROOT_PATH + "breakout.xml";
	docStatus = doc.load_file(resPath.c_str());
	if( docStatus ) {
		int iLevel = 1 + (std::rand() % 2);
		string strLevel = "level" + to_string(iLevel);

		pugi::xml_node rowNode = doc.child("setting").child(strLevel.c_str()).child("row");
		levelProp->rowCount = stoi(rowNode.child_value());

		pugi::xml_node colNode = doc.child("setting").child(strLevel.c_str()).child("col");
		levelProp->colCount = stoi(colNode.child_value());

		pugi::xml_node blocksNode = doc.child("setting").child(strLevel.c_str()).child("blocks");
		int j = 0;
		for (pugi::xml_node block = blocksNode.first_child(); block; block = block.next_sibling()) {
			stringstream curLevel(block.child_value());
			string token;
			int i=0;
			while( std::getline(curLevel, token, ',') ) {
				levelProp->level[j][i] = stoi(token);
				i++;
			}

			j++;
		}
	}
}

GameLevel::~GameLevel()
{
	if( leftWallGate )
		delete leftWallGate;
	if( rightWallGate )
		delete rightWallGate;
	if( topWallGate )
		delete topWallGate;
}

Block* GameLevel::createBlock(int typeIndicator)
{
	BlockType type;
	switch( typeIndicator ) {
	case 1:
		type = Red;
		break;
	case 2:
		type = Purple;
		break;
	case 3:
		type = Yellow;
		break;
	case 4:
		type = Blue;
		break;
	default:
		type = Red;
	}

	return new Block(physicWorld, type, score);
}

Bullet* GameLevel::createBullet(b2Vec2 position)
{
	Bullet *bullet = new Bullet(physicWorld, position);
	bullet->create(shaderAnimation);

	bullets.push_back(bullet);
	return nullptr;
}

void GameLevel::enableDebugDraw()
{
	physicWorld->SetDebugDraw(&mydebugdraw);
	mydebugdraw.SetFlags(b2Draw::e_shapeBit);
}

GameObject* GameLevel::generateWall(ObjectType wallType, b2Vec2 wallPosition, WallProp* wallProp)
{
	Gate *gate = nullptr;
	ObjectType gateType = BottomGate;
	int randomGate = 0;
	int gateIndex = 0;

	switch( wallType ) {
	case LeftWall:
		gateIndex = 0;
		gateType = LeftGate;
		break;

	case RightWall:
		gateIndex = 1;
		gateType = RightGate;
		break;

	case TopWall:
		gateIndex = 2;
		gateType = TopGate;
		break;

	default:
		break;
	}

	// skip top wall from generating gate
	if( wallType == LeftWall || wallType == RightWall ) {
		randomGate = std::rand() % 2;
	}

	if( randomGate == 0 ) {
		wallProp[gateIndex].renderGateCount = 0;

		if( wallType == TopWall )
			wallProp[gateIndex].renderWallCount = 23;
		else
			wallProp[gateIndex].renderWallCount = 20;
	}
	else {
		genWallGap(gateIndex, wallProp);
	}

	walls.push_back(new Wall(physicWorld, wallType, wallProp[gateIndex].renderWallCount, wallPosition));

	if( wallProp[wallType].renderGateCount > 0 ) {
		levelProp->gate[gateIndex] = true;

		int secondPart = wallProp[gateIndex].renderWallCount + wallProp[gateIndex].renderGateCount;
		int remainWall = 0;

		if( wallType == TopWall ) {
			remainWall = 23 - secondPart;
			wallPosition.x = (secondPart + 1) * 0.08f;
		}
		else {
			remainWall = 20 - secondPart;
			wallPosition.y = secondPart / -10.f;
		}

		walls.push_back(new Wall(physicWorld, wallType, remainWall, wallPosition));

		// generate the gate physic
		// treat this as invisible wall
		int startPos = wallProp[gateIndex].renderWallCount;
		int endPos = wallProp[gateIndex].renderWallCount + wallProp[gateIndex].renderGateCount;

		gate = new Gate(physicWorld, gateType, startPos, endPos, wallProp);

		if( wallType == LeftWall ) {
			float meanPos = (wallProp->gatePhysicLoc.x - wallProp->gatePhysicLoc.y) / 2;

			Paddle *paddle = new Paddle(physicWorld, 15.f, {-0.95f, wallProp->gatePhysicLoc.x - meanPos}, SidePaddle, UP_DOWN_FACE_RIGHT);
			paddles.push_back(paddle);
		}
		else if( wallType == RightWall ) {
			float meanPos = (wallProp->gatePhysicLoc.x - wallProp->gatePhysicLoc.y) / 2;

			Paddle *paddle = new Paddle(physicWorld, 15.f, {0.95f, wallProp->gatePhysicLoc.x - meanPos}, SidePaddle, UP_DOWN_FACE_LEFT);
			paddles.push_back(paddle);
		}
	}

	return gate;
}

void GameLevel::genWallGap(int gateIndex, WallProp* wallProp)
{
	int wallCount = 20;
	if( gateIndex == TopWall ) {
		wallCount = 23;
	}

	wallProp[gateIndex].renderGateCount = 3 + std::rand() % (wallCount - 3);

	if( wallProp[gateIndex].renderGateCount == 20 ) {
		wallProp[gateIndex].renderWallCount = 1;
	}
	else {
		wallProp[gateIndex].renderWallCount = 2 + std::rand() % ((wallCount-2)-2);

		if( wallProp[gateIndex].renderGateCount + wallProp[gateIndex].renderWallCount >= wallCount )
			genWallGap(gateIndex, wallProp);
	}
}

void GameLevel::invokeKey(int key, bool release)
{
	StateController::stateController->getCurrentState()->invokeKey(key, release);
}

void GameLevel::launchGame()
{
	assert(this->shader != 0);
	assert(this->shaderSingleInstance != 0);

	if( docStatus ) {
		loadBlocks();
	}

	bool init = loadImage();
	assert(init == true);

	ball->setPosition({ -0.f, -0.44f });
	ball->create(shaderSingleInstance);

	list<GameObject*>::iterator it;
	for( it = walls.begin(); it != walls.end(); it++ ) {
		((GameObject*)*it)->create(shader);
	}

	for( it = paddles.begin(); it != paddles.end(); it++ ) {
		((GameObject*)*it)->create(shaderSingleInstance);
	}

	score->create(shader);
	menuScreen->create(shaderSingleInstance);
	gameOverScreen->create(shaderSingleInstance);
}

void GameLevel::loadBlocks()
{
	// default arrangement when there is no gate on the left and right
	float xPos = -0.7f;
	float yPos = 0.8f;
	float nextBlockPos = 0.09f;

	for( int j=0; j<levelProp->colCount; j++ ) {
		for (int i=0; i<levelProp->rowCount; i++) {
			if( levelProp->level[j][i] > 0 ) {
				GameObject* block = createBlock(levelProp->level[j][i]);
				block->setPosition({ xPos, yPos });
				block->create(shaderAnimation);

				blocks.push_back(block);
			}
			xPos += nextBlockPos;
		}

		xPos = -0.7f;
		yPos -= 0.15f;
	}
}

bool GameLevel::loadImage()
{
	if( spriteRes->getSpriteSheet() )
	{
		ball->CreateTexture(spriteRes);

		list<GameObject*>::iterator it;
		for( it = walls.begin(); it != walls.end(); it++ ) {
			((GameObject*)*it)->CreateTexture(spriteRes);
		}

		for( it = paddles.begin(); it != paddles.end(); it++ ) {
			((GameObject*)*it)->CreateTexture(spriteRes);
		}
	}
	else
	{
		std::cout << "Failed to load sprite texture" << std::endl;
		return false;
	}

	return true;
}

void GameLevel::render()
{
	static int lastTime = 0;

	int actTime = glutGet(GLUT_ELAPSED_TIME);
	int interval = actTime - lastTime;
	lastTime = actTime;

	timeFrame += interval;

	if( timeFrame > (1000/animFps) ) {
		timeFrame = 0;

		// main animation counter
		if( animFrameIndex >= 0.84f )
			animFrameIndex = 0.f;
		else
			animFrameIndex += 0.12f;
	}

	StateController::stateController->getCurrentState()->render();

	stepPhysicWorld(physicFps);

	glutPostRedisplay();
}

void GameLevel::renderGamePlay()
{
	glUseProgram(shaderSingleInstance);

	ball->draw();
	score->draw();

	for (list<GameObject*>::iterator it = paddles.begin(); it != paddles.end(); it++) {
		((GameObject*)*it)->draw();
	}

	glUseProgram(shaderAnimation);

	bool removeBlockFlag = false;
	for (list<GameObject*>::iterator it = blocks.begin(); it != blocks.end(); it++) {
		((GameObject*)*it)->draw();

		if (((GameObject*)*it)->getDispose() == true) {
			delete* it;
			removeBlockFlag = true;
		}
	}

	if (removeBlockFlag == true) {
		blocks.remove_if(isDispose());
		removeBlockFlag = false;
	}

	removeBlockFlag = false;
	for (list<GameObject*>::iterator it = bullets.begin(); it != bullets.end(); it++) {
		((GameObject*)*it)->draw();

		if (((GameObject*)*it)->getDispose() == true) {
			delete* it;
			removeBlockFlag = true;
		}
	}

	if (removeBlockFlag == true) {
		bullets.remove_if(isDispose());
		removeBlockFlag = false;
	}

	glUseProgram(shader);

	for (list<GameObject*>::iterator it = walls.begin(); it != walls.end(); it++) {
		((GameObject*)*it)->draw();
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);

	//physicWorld->DebugDraw();
}

void GameLevel::renderGameOverScreen()
{
	glUseProgram(shaderSingleInstance);

	gameOverScreen->draw();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void GameLevel::renderMenuScreen()
{
	glUseProgram(shaderSingleInstance);

	menuScreen->draw();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void GameLevel::resetBlock()
{
	// delete each of the block
	// after that remove them from container
	for (list<GameObject*>::iterator it = blocks.begin(); it != blocks.end(); it++) {
		delete *it;
	}
	blocks.clear();
	loadBlocks();
}

void GameLevel::restartGame()
{
	resetBlock();

	for( list<GameObject*>::iterator it = paddles.begin(); it != paddles.end(); it++ ) {
		((GameObject*)*it)->setPosition();
		static_cast<Paddle*>((GameObject*)*it)->setLinearVelocity({0.f, 0.f});
	}

	ball->setPosition();
	static_cast<Ball*>(ball)->setLinearVelocity({0.f, 0.f});
}

void GameLevel::stepPhysicWorld(int fps)
{
	physicWorld->Step((float)fps/1000, 6, 2);

	ball->updateObjectPosition({0.f, 0.f});

	for (list<GameObject*>::iterator it = paddles.begin(); it != paddles.end(); it++) {
		static_cast<Paddle*>((GameObject*)*it)->updateObjectPosition({0.f, 0.f});
	}

	for (list<GameObject*>::iterator it = bullets.begin(); it != bullets.end(); it++) {
		((GameObject*)*it)->updateObjectPosition({0.f, -0.02f});
	}
}
