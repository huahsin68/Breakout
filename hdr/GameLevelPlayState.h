#ifndef __GAMELEVELPLAYSTATE_H_
#define __GAMELEVELPLAYSTATE_H_

#include "GameLevelState.h"


class GameLevelPlayState : public GameLevelState
{
public:
	GameLevelPlayState();
	GameLevelPlayState(GameLevel*, GameState);
	GameLevelPlayState(GameLevel*);
	virtual ~GameLevelPlayState();

	void invokeKey(int, bool) override;
	void render() override;
	void entryState() override;
	void exitState() override;


private:
	bool ready = true;
};

#endif /* __GAMELEVELPLAYSTATE_H_ */
