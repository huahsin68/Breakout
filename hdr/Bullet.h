#ifndef __BULLET_H_
#define __BULLET_H_

#include "GameObject.h"


class Bullet : public GameObject
{
public:
	Bullet();
	Bullet(b2World*, b2Vec2);
	virtual ~Bullet();

	void collision();
	void create(unsigned int) override;
	void draw() override;
	void setLinearVelocity(b2Vec2);


private:
	float animFramePosX = 0.f;

	Resource* bulletRes = nullptr;


private:
	float speed = 1.f;
};

#endif /* __BULLET_H_ */
