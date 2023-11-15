#include "Ball.h"

Ball::Ball()
{
}

Ball::Ball(b2World *physicWorld)
{
	this->physicWorld = physicWorld;

	physicProp->name = "ball";
	physicProp->width = 0.025f;
	physicProp->height = 0.025f;
	physicProp->objectType = ProjectileBall;

	// top right position
	vertices[0] = 0.f;
	vertices[1] = -0.35f;
	vertices[2] = 0.0f;

	// bottom right position
	vertices[8] = 0.f;
	vertices[9] = -0.43f;
	vertices[10] = 0.0f;

	// bottom left position
	vertices[16] = 0.10f;
	vertices[17] = -0.43f;
	vertices[18] = 0.0f;

	// top left position
	vertices[24] = 0.10f;
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
	vertices[6] = 0.40f;
	vertices[7] = 0.5f;

	// bottom right texture coords
	vertices[14] = 0.40f;
	vertices[15] = 0.46f;

	// bottom left texture coords
	vertices[22] = 0.44f;
	vertices[23] = 0.46f;

	// top left texture coords
	vertices[30] = 0.44f;
	vertices[31] = 0.5f;
}

Ball::~Ball()
{
	body->DestroyFixture(body->GetFixtureList());
}

void Ball::applyForce(b2Vec2 velocity)
{
	b2Vec2 desirevel;
	if( velocity.x < 0.f )
		desirevel.x = -6.f;
	else
		desirevel.x = 6.f;

	if( velocity.y < 0.f )
		desirevel.y = -6.f;
	else
		desirevel.y = 6.f;

	b2Vec2 velChange = {desirevel.x - velocity.x, desirevel.y - velocity.y};
	b2Vec2 impulse = {body->GetMass() * velChange.x, body->GetMass() * velChange.y};

	body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
}

void Ball::collision()
{
	applyForce(this->getLinearVelocity());
}

void Ball::create(unsigned int shader)
{
	createBuffer();
	initPhysics(b2_dynamicBody, position, 0.025f);

	transformLoc = glGetUniformLocation(shader, "transform");

	physicProp->go = this;
}

void Ball::draw()
{
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformGameObject));

	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, tex);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Ball::setLinearVelocity(b2Vec2 direction)
{
	body->SetLinearVelocity(direction);
}
