#ifndef __TEXT_H__
#define __TEXT_H__

#include "GameObject.h"
#include "Resource.h"


class Text : public GameObject
{
public:
	Text();
	Text(Resource*, b2Vec2, b2Vec2);
	virtual ~Text();

	void create(unsigned int) override;
	void draw() override;
	void updateText(char text);
	

private:
	void locateUV(b2Vec2);


private:
	Resource* fontRes = nullptr;
};

#endif /* __TEXT_H_ */
