#ifndef __GAMELEVELGAMEOVERSTATE_H__
#define __GAMELEVELGAMEOVERSTATE_H__

#include "GameLevelState.h"


class GameLevelGameOverState : public GameLevelState
{
public:
	GameLevelGameOverState();
	GameLevelGameOverState(GameLevel*, GameState);
	GameLevelGameOverState(GameLevel*);
	virtual ~GameLevelGameOverState();

	void invokeKey(int, bool) override;
	void render() override;
	void entryState() override;
	void exitState() override;


private:
	bool ready = true;
};

#endif /* __GAMELEVELPLAYSTATE_H__ */
