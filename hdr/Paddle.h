#ifndef PADDLE_H_
#define PADDLE_H_

#include <list>
#include "Bullet.h"
#include "GameLevel.h"


class GameLevel;

enum Direction {
	LEFT_RIGHT,
	UP_DOWN_FACE_RIGHT,
	UP_DOWN_FACE_LEFT
};

class Paddle : public GameObject {
public:
	struct {
		int maxBulletCnt = 3;
		int launchBulletCnt = 0;
	} BulletController;


public:
	Paddle();
	Paddle(b2World*, float, b2Vec2, ObjectType, Direction moveDirection = LEFT_RIGHT);
	virtual ~Paddle();

	void create(unsigned int) override;
	void draw() override;
	inline b2Vec2 getLinearVelocity() {
		cout << "debug: " << body->GetWorldCenter().x << ", " << body->GetWorldCenter().y << endl;
		return body->GetWorldCenter();
	}
	void invokeKey(int, bool);
	void launchMissile(GameLevel*);
	void setLinearVelocity(b2Vec2);
	void updateObjectPosition(b2Vec2);


public:
	inline float getSpeed() {
		return speed;
	}
	inline void setSpeed(float speed) {
		this->speed = speed;
	}


private:
	float speed;

	bool powerUp = false;
	bool eventTrigger = false;
	Direction moveDirection = LEFT_RIGHT;
};

#endif /* PADDLE_H_ */
