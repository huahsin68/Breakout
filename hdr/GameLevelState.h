#ifndef __GAMESTATE_H_
#define __GAMESTATE_H_

#include "HeaderSymbol.h"
#include "GameLevel.h"


class GameLevel;

class GameLevelState {
public:
	GameLevelState();
	GameLevelState(GameState);
	GameLevelState(GameLevel*, GameState);
	GameLevelState(GameLevel*);
	virtual ~GameLevelState();

	virtual void invokeKey(int, bool) = 0;
	virtual void render() = 0;
	virtual void entryState() = 0;
	virtual void exitState() = 0;

	inline GameState getState() {
		return gameState;
	}
	inline void setState(GameState gameState) {
		this->gameState = gameState;
	}


protected:
	GameLevel *gameLevel = nullptr;


private:
	GameState gameState = Start;
};

#endif /* __GAMESTATE_H_ */
