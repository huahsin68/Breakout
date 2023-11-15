#include <Paddle.h>


Paddle::Paddle()
{
	this->speed = 0.1f;
}

Paddle::Paddle(b2World *physicWorld, float speed, b2Vec2 position, ObjectType objectType, Direction moveDirection)
{
	this->physicWorld = physicWorld;
	this->speed = speed;
	this->moveDirection = moveDirection;
	this->position = position;

	physicProp->name = "paddle";
	physicProp->width = 0.08f;
	physicProp->height = 0.035f;
	physicProp->objectType = objectType;

	if( moveDirection == UP_DOWN_FACE_RIGHT ) {
		// position rotate to left, negative rotate to right
		transformGameObject = glm::rotate(transformGameObject, glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f));
	}
	else if( moveDirection == UP_DOWN_FACE_LEFT ) {
		// position rotate to left, negative rotate to right
		transformGameObject = glm::rotate(transformGameObject, glm::radians(-90.f), glm::vec3(0.f, 0.f, 1.f));
	}

	// top right position
	vertices[0] = 0.35f;
	vertices[1] = -0.35f;
	vertices[2] = 0.0f;

	// bottom right position
	vertices[8] = 0.35f;
	vertices[9] = -0.43f;
	vertices[10] = 0.0f;

	// bottom left position
	vertices[16] = 0.55f;
	vertices[17] = -0.43f;
	vertices[18] = 0.0f;

	// top left position
	vertices[24] = 0.55f;
	vertices[25] = -0.35f;
	vertices[26] = 0.0f;

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

	// top right texture coords
	vertices[6] = 0.f;
	vertices[7] = 0.5f;

	// bottom right texture coords
	vertices[14] = 0.f;
	vertices[15] = 0.44f;

	// bottom left texture coords
	vertices[22] = 0.24f;
	vertices[23] = 0.44f;

	// top left texture coords
	vertices[30] = 0.24f;
	vertices[31] = 0.5f;
}

Paddle::~Paddle()
{
}

void Paddle::create(unsigned int shader)
{
	float angle = 0.0f;
	if( moveDirection == UP_DOWN_FACE_RIGHT ) {
		angle = 1.57f;
	}
	else if( moveDirection == UP_DOWN_FACE_LEFT ) {
		angle = -1.57f;
	}

	createBuffer();
	initRectPhysics(b2_dynamicBody, position, angle);

	transformLoc = glGetUniformLocation(shader, "transform");

	physicProp->go = this;
}

void Paddle::draw()
{
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformGameObject));

	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, tex);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Paddle::invokeKey(int key, bool release)
{
	if (release) {
		eventTrigger = false;
		setLinearVelocity(b2Vec2(0.f, 0.f));
		return;
	}

	eventTrigger = true;

	switch (key) {
	// move to left
	case 1:
		if( moveDirection != UP_DOWN_FACE_RIGHT && moveDirection != UP_DOWN_FACE_LEFT )
			setLinearVelocity(b2Vec2(-(getSpeed()), 0.f));
		break;

	// move to right
	case 2:
		if( moveDirection != UP_DOWN_FACE_RIGHT && moveDirection != UP_DOWN_FACE_LEFT )
			setLinearVelocity(b2Vec2(getSpeed(), 0.f));
		break;

	// move upward
	case 3:
		if( moveDirection != LEFT_RIGHT)
			setLinearVelocity(b2Vec2(0.f, getSpeed()));
		break;

	// move downward
	case 4:
		if( moveDirection != LEFT_RIGHT)
			setLinearVelocity(b2Vec2(0.f, -(getSpeed())));
		break;
	}
}

void Paddle::launchMissile(GameLevel *gameLevel)
{
	if( BulletController.launchBulletCnt == BulletController.maxBulletCnt &&
			physicProp->objectType != PrimaryPaddle ) {
		return;
	}

	// doesn't follow paddle position when bullet is create
	b2Vec2 bulletPos = { body->GetWorldCenter().x / 2, position.y + .5f };
	gameLevel->createBullet(bulletPos);

	BulletController.launchBulletCnt++;
}

void Paddle::setLinearVelocity(b2Vec2 direction)
{
	body->SetLinearVelocity(direction);
}

void Paddle::updateObjectPosition(b2Vec2 offset)
{
	float physicWidth = physicProp->width;
	float physicHeight = physicProp->height;

	if( moveDirection == UP_DOWN_FACE_RIGHT ) {
		// top left
		vertices[0] = body->GetWorldCenter().y - physicWidth + offset.x;
		vertices[1] = body->GetWorldCenter().x + physicHeight + offset.y - (position.x * 2.f);// - offset;
		// bottom left
		vertices[8] = body->GetWorldCenter().y - physicWidth + offset.x;
		vertices[9] = body->GetWorldCenter().x - physicHeight + offset.y - (position.x * 2.f);
		// bottom right
		vertices[16] = body->GetWorldCenter().y + physicWidth + offset.x;// - offset;
		vertices[17] = body->GetWorldCenter().x - physicHeight + offset.y - (position.x * 2.f);
		// top right
		vertices[24] = body->GetWorldCenter().y + physicWidth + offset.x;// - offset;
		vertices[25] = body->GetWorldCenter().x + physicHeight + offset.y - (position.x * 2.f);// - offset;
	}
	else if( moveDirection == UP_DOWN_FACE_LEFT ) {
		// top left
		//cout << body->GetWorldCenter().x << ", " << body->GetWorldCenter().y << endl;
		vertices[0] = -(body->GetWorldCenter().y) - physicWidth + offset.x;
		vertices[1] = body->GetWorldCenter().x + physicHeight + offset.y;// - (position.y * 2.f);
		// bottom left
		vertices[8] = -(body->GetWorldCenter().y) - physicWidth + offset.x;
		vertices[9] = body->GetWorldCenter().x - physicHeight + offset.y;// - (position.y * 2.f);
		// bottom right
		vertices[16] = -(body->GetWorldCenter().y) + physicWidth + offset.x;
		vertices[17] = body->GetWorldCenter().x - physicHeight + offset.y;// - (position.y * 2.f);
		// top right
		vertices[24] = -(body->GetWorldCenter().y) + physicWidth + offset.x;
		vertices[25] = body->GetWorldCenter().x + physicHeight + offset.y;// - (position.y * 2.f);
	}
	else {
		// top left
		vertices[0] = body->GetWorldCenter().x - physicWidth + offset.x;
		vertices[1] = body->GetWorldCenter().y + physicHeight + offset.y;// - offset;
		// bottom left
		vertices[8] = body->GetWorldCenter().x - physicWidth + offset.x;
		vertices[9] = body->GetWorldCenter().y - physicHeight + offset.y;
		// bottom right
		vertices[16] = body->GetWorldCenter().x + physicWidth + offset.x;// - offset;
		vertices[17] = body->GetWorldCenter().y - physicHeight + offset.y;
		// top right
		vertices[24] = body->GetWorldCenter().x + physicWidth + offset.x;// - offset;
		vertices[25] = body->GetWorldCenter().y + physicHeight + offset.y;// - offset;
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
