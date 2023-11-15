#include "StateController.h"
#include "GameLevelPlayState.h"
#include "GameLevelMenuState.h"
#include "GameLevelGameOverState.h"


StateController::StateController() {
}

StateController::~StateController() {
	// TODO Auto-generated destructor stub
}

StateController* StateController::getInstance()
{
	if( stateController == nullptr )
		stateController = new StateController();

	return stateController;
}

void StateController::initState(GameLevel* gameLevel)
{
	playState = new GameLevelPlayState(gameLevel);
	menuState = new GameLevelMenuState(gameLevel);
	gameOverState = new GameLevelGameOverState(gameLevel);

	// default to menu state
	currentState = menuState;
}

void StateController::switchState(GameState gameState)
{
	currentState->exitState();

	switch(gameState) {
	case Play:
		currentState = playState;
		this->gameState = Play;
		break;

	case Pause:
		currentState = menuState;
		this->gameState = Pause;
		break;

	case GameOver:
		currentState = gameOverState;
		this->gameState = GameOver;
		break;

	default:
		break;
	}

	currentState->entryState();
}
