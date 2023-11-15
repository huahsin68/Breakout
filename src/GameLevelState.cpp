#include <GameLevelState.h>

GameLevelState::GameLevelState()
{
	// default to play state
	gameState = Start;
}

GameLevelState::GameLevelState(GameState gameState)
{
	this->gameState = gameState;

	cout << "GameLevelState(GameState) constructor, " << gameState << endl;
}

GameLevelState::GameLevelState(GameLevel *gameLevel, GameState gameState) : GameLevelState(gameState)
{
	this->gameLevel = gameLevel;
}

GameLevelState::GameLevelState(GameLevel *gameLevel)
{
	this->gameLevel = gameLevel;
}

GameLevelState::~GameLevelState()
{
}

