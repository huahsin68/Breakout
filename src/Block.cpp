#include "Block.h"

Block::Block()
{
}

Block::Block(b2World *physicWorld, BlockType type, Score *score)
{
	blockRes = new Resource(RES_PATH + "sprites_block.png");

	this->physicWorld = physicWorld;
	this->blockType = type;
	this->score = score;

	physicProp->name = "block";
	physicProp->width = 0.045f;
	physicProp->height = 0.045f;

	float xOffset = 0.f;
	float yOffset = 0.f;

	// top right position
	vertices[0] = -0.92f + xOffset;
	vertices[1] = 1.f - yOffset;
	vertices[2] = 0.f;

	// bottom right position
	vertices[8] = -0.92f + xOffset;
	vertices[9] = 0.9f - yOffset;
	vertices[10] = 0.f;

	// bottom left position
	vertices[16] = -1.f + xOffset;
	vertices[17] = 0.9f - yOffset;
	vertices[18] = 0.f;

	// top left position
	vertices[24] = -1.f + xOffset;
	vertices[25] = 1.f - yOffset;
	vertices[26] = 0.f;

	// top right color
	vertices[3] = 1.0f;
	vertices[4] = 0.0f;
	vertices[5] = 0.0f;

	// bottom right color
	vertices[11] = 0.0f;
	vertices[12] = 1.0f;
	vertices[13] = 0.0f;

	// bottom left color
	vertices[19] = 0.0f;
	vertices[20] = 0.0f;
	vertices[21] = 1.0f;

	// top left color
	vertices[27] = 1.0f;
	vertices[28] = 1.0f;
	vertices[29] = 0.0f;
}

Block::~Block()
{
	body->DestroyFixture(body->GetFixtureList());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Block::collision()
{
	switch( blockType ) {
	case Blue:
		score->setScore(2);
		break;

	case Red:
		score->setScore(1);
		break;

	case Yellow:
		score->setScore(1);
		break;

	case Purple:
		score->setScore(1);
		break;
	}

	setTriggerAnimation(true);
	setRemovePhysic(true);

	score->updateScore();
}

void Block::create(unsigned int shader)
{
	setupBlock();
	createBuffer();
	CreateTexture(blockRes);
	initRectPhysics(b2_staticBody, position);

	offsetLocation = glGetUniformLocation(shader, "offset");
	transformLoc = glGetUniformLocation(shader, "transform");

	physicProp->go = this;
}

void Block::draw()
{
	if (getDispose()) {
		return;
	}

	if( isRemovePhysic() ) {
		body->DestroyFixture(body->GetFixtureList());
		setRemovePhysic(false);
	}

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformGameObject));

	if( isTriggerAnimation() == true ) {
		if( animFramePosX >= 0.84f ) {
			setDispose(true);
		}
		else
			animFramePosX += 0.125f;
	}

	glUniform2f(offsetLocation, animFramePosX, 0.f);

	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, tex);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Block::setupBlock()
{
	float x = 0.f;
	float y = 0.f;

	switch (blockType) {
	case Red:
		x = 0.f;
		y = 0.3f;

		physicProp->objectType = RedBlock;
		break;

	case Purple:
		x = 0.f;
		y = 0.8f;

		physicProp->objectType = PurpleBlock;
		break;

	case Yellow:
		x = 0.f;
		y = 0.55f;

		physicProp->objectType = YellowBlock;
		break;

	case Blue:
		x = 0.f;
		y = 0.06f;

		physicProp->objectType = BlueBlock;
		break;
	}

	// top right texture coords
	vertices[6] = x + 0.01f;
	vertices[7] = y - 0.04f;

	// bottom right texture coords
	vertices[14] = x + 0.01f;
	vertices[15] = y + 0.17f;

	// bottom left texture coords
	vertices[22] = x + 0.12f;
	vertices[23] = y + 0.17f;

	// top left texture coords
	vertices[30] = x + 0.12f;
	vertices[31] = y - 0.04f;
}
