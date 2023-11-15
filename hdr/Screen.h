#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "GameObject.h"


class Screen: public GameObject
{
public:
	Screen();
	virtual ~Screen();

	void create(unsigned int) override;
	void draw() override;

protected:
	Resource* menuRes = nullptr;
};

#endif /* __SCREEN_H__ */
