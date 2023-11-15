#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(b2World* physicWorld, b2Vec2 position)
{
	bulletRes = new Resource(RES_PATH + "bullet.png");

	this->physicWorld = physicWorld;
	this->position = position;

	physicProp->name = "bullet";
	physicProp->width = 0.1f;
	physicProp->height = 0.1f;
	physicProp->objectType = ProjectileBullet;

	// top right position
	vertices[0] = 0.2f;
	vertices[1] = 0.3f;
	vertices[2] = 0.f;

	// bottom right position
	vertices[8] = 0.2f;
	vertices[9] = -0.1f;
	vertices[10] = 0.f;

	// bottom left position
	vertices[16] = -0.2f;
	vertices[17] = -0.1f;
	vertices[18] = 0.f;

	// top left position
	vertices[24] = -0.2f;
	vertices[25] = 0.3f;
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

Bullet::~Bullet()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Bullet::collision()
{
	setRemovePhysic(true);
}

void Bullet::create(unsigned int shader)
{
	float x = 0.f;
	float y = 0.f;

	// top right texture coords
	vertices[6] = x - 0.0f;
	vertices[7] = y - 0.0f;

	// bottom right texture coords
	vertices[14] = x - 0.0f;
	vertices[15] = y + 1.0f;

	// bottom left texture coords
	vertices[22] = x + 0.125f;
	vertices[23] = y + 1.0f;

	// top left texture coords
	vertices[30] = x + 0.125f;
	vertices[31] = y - 0.0f;

	createBuffer();
	CreateTexture(bulletRes);
	initPhysics(b2_dynamicBody, position, 0.016f);

	offsetLocation = glGetUniformLocation(shader, "offset");
	transformLoc = glGetUniformLocation(shader, "transform");

	physicProp->go = this;

	body->ApplyForce({0.f, speed}, {0.f, 0.f}, true);
}

void Bullet::draw()
{
	if (getDispose()) {
		return;
	}

	if( isRemovePhysic() ) {
		body->DestroyFixture(body->GetFixtureList());
		setRemovePhysic(false);
		setDispose(true);
	}

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformGameObject));

	if( animFramePosX >= 0.875f ) {
		animFramePosX = 0.f;
	}
	else
		animFramePosX += 0.125f;

	glUniform2f(offsetLocation, animFramePosX, 0.f);

	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, tex);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Bullet::setLinearVelocity(b2Vec2 direction)
{
	body->SetLinearVelocity(direction);
}

