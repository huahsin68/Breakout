#include <GameLevelPlayState.h>

GameLevelPlayState::GameLevelPlayState()
{
	setState(Play);
}

GameLevelPlayState::GameLevelPlayState(GameLevel* gameLevel, GameState gameState) : GameLevelState(gameLevel, gameState)
{
}

GameLevelPlayState::GameLevelPlayState(GameLevel* gameLevel) : GameLevelState(gameLevel)
{
}

GameLevelPlayState::~GameLevelPlayState()
{
}

void GameLevelPlayState::invokeKey(int key, bool release)
{
	list<GameObject*> paddles = gameLevel->getPaddles();

	switch(key)
	{
	case 1:
	case 2:
	case 3:
	case 4:
		if( ready == true ) {
			return;
		}

		for( list<GameObject*>::iterator it = paddles.begin(); it != paddles.end(); it++ ) {
			static_cast<Paddle*>(*it)->invokeKey(key, release);
		}
		break;

	case 7:
		if( ready == true ) {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> xdist(-3,3);
			std::uniform_int_distribution<> ydist(1,4);

			b2Vec2 ballDirection = {(float)xdist(gen), (float)ydist(gen)};
			static_cast<Ball*>(gameLevel->getBall())->launch(ballDirection);

			ready = false;
		}
		else {
			static_cast<Paddle*>(gameLevel->getPaddle())->launchMissile(gameLevel);
		}
		break;
	}
}

void GameLevelPlayState::render()
{
	gameLevel->renderGamePlay();
}

void GameLevelPlayState::entryState()
{
	cout << "Enter GameLevel play state" << endl;
}

void GameLevelPlayState::exitState()
{
	// freeze paddle when play state is exit
	ready = true;
}
