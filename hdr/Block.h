#ifndef __BLOCK_H_
#define __BLOCK_H_

#include "HeaderSymbol.h"
#include "Score.h"

class Block: public GameObject
{
public:
	Block();
	Block(b2World*, BlockType, Score*);
	virtual ~Block();

	void collision();
	void create(unsigned int) override;
	BlockType getBlockType() {
		return blockType;
	}
	void draw() override;
	

private:
	void setupBlock();

	float offset = 0.02f;
	float animFramePosX = 0.f;

	BlockType blockType;

	Score* score = nullptr;

	Resource* blockRes = nullptr;
};

#endif /* __BLOCK_H_ */
