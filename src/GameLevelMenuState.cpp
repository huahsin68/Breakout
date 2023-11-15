/*
 * GameLevelMenuState.cpp
 *
 *  Created on: Mar 31, 2023
 *      Author: kokhoe
 */

#include "GameLevelMenuState.h"
#include "GameLevel.h"

GameLevelMenuState::GameLevelMenuState()
{
	setState(Pause);
}

GameLevelMenuState::GameLevelMenuState(GameLevel* gameLevel, GameState gameState) : GameLevelState(gameLevel, gameState)
{
	cout << "GameLevelMenuState(GameLevel, GameState) constructor" << endl;
}

GameLevelMenuState::GameLevelMenuState(GameLevel* gameLevel) : GameLevelState(gameLevel)
{
	cout << "GameLevelMenuState(GameLevel) constructor" << endl;
}

GameLevelMenuState::~GameLevelMenuState()
{
}

void GameLevelMenuState::invokeKey(int key, bool release)
{
	switch(key)
	{
	case 6:
		StateController::stateController->switchState(Play);
		break;
	}
}

void GameLevelMenuState::render()
{
	gameLevel->renderMenuScreen();
}

void GameLevelMenuState::entryState()
{
	cout << "Enter GameLevel menu state" << endl;
}

void GameLevelMenuState::exitState()
{
	cout << "Exit GameLevel menu state" << endl;
}
