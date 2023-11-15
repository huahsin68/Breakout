#ifndef __STATECONTROLLER_H__
#define __STATECONTROLLER_H__

#include "GameLevel.h"
#include "GameLevelState.h"


class GameLevel;
class GameLevelState;

class StateController
{
public:
	StateController(StateController&) = delete;

	virtual ~StateController();

	inline GameLevelState* getCurrentState() {
		return currentState;
	}
	inline GameState getGameState() {
		return gameState;
	}

	static StateController *getInstance();
	void initState(GameLevel*);

	void switchState(GameState);
	void operator=(const StateController&) = delete;


public:
	static StateController *stateController;


private:
	StateController();


private:
	GameLevelState *playState = nullptr;
	GameLevelState *menuState = nullptr;
	GameLevelState *gameOverState = nullptr;

	GameLevelState *currentState = nullptr;

	GameState gameState = Play;
};



#endif /* __STATECONTROLLER_H_ */
