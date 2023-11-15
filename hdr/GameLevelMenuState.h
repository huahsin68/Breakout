#ifndef __GAMELEVELMENUSTATE_H_
#define __GAMELEVELMENUSTATE_H_


#include "GameLevelState.h"


class GameLevelMenuState : public GameLevelState
{
public:
	GameLevelMenuState();
	GameLevelMenuState(GameLevel*, GameState);
	GameLevelMenuState(GameLevel*);
	virtual ~GameLevelMenuState();

	void invokeKey(int, bool) override;
	void render() override;
	void entryState() override;
	void exitState() override;
};

#endif /* __GAMELEVELMENUSTATE_H_ */
