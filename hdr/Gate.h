#ifndef __GATE_H_
#define __GATE_H_

#include "GameObject.h"


class Gate : public GameObject {
public:
	Gate(b2World*, ObjectType, int, int, WallProp* wallProp=nullptr);
	virtual ~Gate();

	void collision();
	void create(unsigned int) override;
	void draw() override;

private:
	const float boxHeight = 0.1f;
	const float boxWidth = 0.08f;
};

#endif /* __GATE_H_ */
