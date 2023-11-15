#include "Wall.h"

Wall::Wall()
{
}

Wall::Wall(b2World *physicWorld, ObjectType type, int boxCount, b2Vec2 renderPos)
{
	this->physicWorld = physicWorld;
	this->boxCount = boxCount;
	this->renderPos = renderPos;

	physicProp->name = "Wall";
	physicProp->objectType = type;

	transformGameObject = glm::rotate(transformGameObject, glm::radians(0.0f), glm::vec3(0.f, 0.f, 1.f));

	// top right position
	vertices[0] = -0.92f;
	vertices[1] = 1.f;
	vertices[2] = 0.f;

	// bottom right position
	vertices[8] = -0.92f;
	vertices[9] = 0.9f;
	vertices[10] = 0.f;

	// bottom left position
	vertices[16] = -1.f;
	vertices[17] = 0.9f;
	vertices[18] = 0.f;

	// top left position
	vertices[24] = -1.f;
	vertices[25] = 1.f;
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

Wall::~Wall()
{
}

void Wall::create(unsigned int shader)
{
	setupWall();
	createInstanceBuffer();

	transformLoc = glGetUniformLocation(shader, "transform");

	physicProp->go = this;
}

void Wall::draw()
{
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformGameObject));
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, tex);
	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, boxCount);
}

void Wall::setupWall()
{
	b2Vec2 physicPos = {0.f, 0.f };
	b2Vec2 topLine1 = {0.f, 0.f };
	b2Vec2 topLine2 = {0.f, 0.f };
	b2Vec2 bottomLine1 = {0.f, 0.f };
	b2Vec2 bottomLine2 = {0.f, 0.f };
	b2Vec2 sideLine1 = {0.f, 0.f };
	b2Vec2 sideLine2 = {0.f, 0.f };
	float yPosPhysic = 0.f;
	float xPosPhysic = 0.f;
	float xPos = 0.f;
	float yPos = 0.f;

	switch( physicProp->objectType ) {
	case LeftWall:
		physicPos = {-0.93f, 1.f};
		xPos = renderPos.x;
		yPos = renderPos.y;
		xPosPhysic = physicPos.x;
		yPosPhysic = physicPos.y + yPos;

		for (int i = 0; i < boxCount; i++) {
			translation[i].x = xPos;
			translation[i].y = yPos;

			yPos = yPos - 0.1f;
		}

		// top right texture coords
		vertices[6] = 0.1f - offset;
		vertices[7] = 0.9f;

		// bottom right texture coords
		vertices[14] = 0.1f - offset;
		vertices[15] = 0.8f + offset;

		// bottom left texture coords
		vertices[22] = 0.f;
		vertices[23] = 0.8f + offset;

		// top left texture coords
		vertices[30] = 0.f;
		vertices[31] = 0.9f;

		topLine1 = {xPosPhysic, yPosPhysic};
		topLine2 = {xPosPhysic - boxHeight, yPosPhysic};
		initPhysics(topLine1, topLine2);

		sideLine1 = { xPosPhysic, yPosPhysic };
		sideLine2 = { xPosPhysic, (yPosPhysic - boxHeight * boxCount) + 0.01f };
		initPhysics(sideLine1, sideLine2);

		bottomLine1 = {xPosPhysic, (yPosPhysic - boxHeight * boxCount) + 0.01f};
		bottomLine2 = {xPosPhysic - boxHeight, (yPosPhysic - boxHeight * boxCount) + 0.01f};
		initPhysics(bottomLine1, bottomLine2);

		physicProp->objectType = LeftWall;
		break;

	case RightWall:
		physicPos = {0.93f, 1.f};
		xPos = renderPos.x;
		yPos = renderPos.y;
		xPosPhysic = physicPos.x;
		yPosPhysic = physicPos.y + yPos;

		for (int i = 0; i < boxCount; i++) {
			translation[i].x = xPos;
			translation[i].y = yPos;

			yPos = yPos - 0.1f;
		}

		// top right texture coords
		vertices[6] = 0.1f - offset;
		vertices[7] = 0.9f;

		// bottom right texture coords
		vertices[14] = 0.1f - offset;
		vertices[15] = 0.8f + offset;

		// bottom left texture coords
		vertices[22] = 0.f;
		vertices[23] = 0.8f + offset;

		// top left texture coords
		vertices[30] = 0.f;
		vertices[31] = 0.9f;

		topLine1 = {xPosPhysic, yPosPhysic};
		topLine2 = {xPosPhysic + boxHeight, yPosPhysic};
		initPhysics(topLine1, topLine2);

		sideLine1 = { xPosPhysic, yPosPhysic };
		sideLine2 = { xPosPhysic, (yPosPhysic - boxHeight * boxCount) + 0.01f };
		initPhysics(sideLine1, sideLine2);

		bottomLine1 = {xPosPhysic, (yPosPhysic - boxHeight * boxCount) + 0.01f};
		bottomLine2 = {xPosPhysic + boxHeight, (yPosPhysic - boxHeight * boxCount) + 0.01f};
		initPhysics(bottomLine1, bottomLine2);

		physicProp->objectType = RightWall;
		break;

	case TopWall:
		physicPos = { -0.995f, 0.908f };
		xPos = renderPos.x;
		yPos = renderPos.y;
		xPosPhysic = physicPos.x + xPos;
		yPosPhysic = physicPos.y;

		for (int i = 0; i < boxCount; i++) {
			translation[i].x = xPos;
			translation[i].y = yPos;

			xPos = xPos + 0.08f;
		}

		// top right texture coords
		vertices[6] = 0.1f - offset;
		vertices[7] = 0.9f;

		// bottom right texture coords
		vertices[14] = 0.1f - offset;
		vertices[15] = 0.8f + offset;

		// bottom left texture coords
		vertices[22] = 0.f;
		vertices[23] = 0.8f + offset;

		// top left texture coords
		vertices[30] = 0.f;
		vertices[31] = 0.9f;

		topLine1 = {xPosPhysic + 0.005f, yPosPhysic};
		topLine2 = {xPosPhysic + 0.005f, yPosPhysic + boxWidth};
		initPhysics(topLine1, topLine2);

		sideLine1 = { xPosPhysic, yPosPhysic};
		sideLine2 = { xPosPhysic + (boxWidth * boxCount) - 0.015f, yPosPhysic };
		initPhysics(sideLine1, sideLine2);

		bottomLine1 = {xPosPhysic + boxWidth * boxCount - 0.015f, yPosPhysic};
		bottomLine2 = {xPosPhysic + boxWidth * boxCount - 0.015f, yPosPhysic + boxWidth};
		initPhysics(bottomLine1, bottomLine2);

		physicProp->objectType = TopWall;
		break;
	}
}
