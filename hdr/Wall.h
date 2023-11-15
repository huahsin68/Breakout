#ifndef __WALL_H__
#define __WALL_H__

#include "HeaderSymbol.h"
#include "GameObject.h"


class Wall : public GameObject {
public:
	Wall();
	Wall(b2World*, ObjectType, int boxCount=0, b2Vec2 renderPos={0.f, 0.f});
	virtual ~Wall();

	void create(unsigned int) override;
	virtual void draw() override;
	void setupWall();


private:
	float offset = 0.02f;

	b2Vec2 renderPos = {0.f, 0.f};

	const float boxHeight = 0.1f;
	const float boxWidth = 0.08f;
};

#endif /* __WALL_H__ */
