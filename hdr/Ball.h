#ifndef BALL_H_
#define BALL_H_

#include <random>

#include "GameObject.h"


class Ball: public GameObject {
public:
	Ball();
	Ball(b2World*);
	virtual ~Ball();

	void applyForce(b2Vec2);

	void collision();
	void create(unsigned int) override;
	void draw() override;
	inline b2Vec2 getLinearVelocity() {
		return body->GetLinearVelocity();
	}
	void setLinearVelocity(b2Vec2);
	inline void launch(b2Vec2 direction) {
		body->ApplyForce(direction, body->GetWorldCenter(), true);
	}

	float getSpeed() {
		return speed;
	}

private:
	float speed = 4.f;
};

#endif /* BALL_H_ */
