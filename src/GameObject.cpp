#include <GameObject.h>

GameObject::GameObject()
{
	physicWorld = nullptr;
	body = nullptr;
}

GameObject::~GameObject()
{
}

void GameObject::createBuffer()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * 32, &vertices[0], GL_DYNAMIC_DRAW);

	glGenBuffers(1, &idc);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idc);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * 6, &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void GameObject::createInstanceBuffer()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * 32, &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &idc);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idc);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * 6, &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &inst);
	glBindBuffer(GL_ARRAY_BUFFER, inst);
	glBufferData(GL_ARRAY_BUFFER, sizeof(translation) * boxCount, &translation[0], GL_STATIC_DRAW);

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glVertexAttribDivisor(3, 1);
}

void GameObject::CreateTexture(Resource *resource)
{
	//stbi_set_flip_vertically_on_load(true);

	// load and create a texture
	// -------------------------
	// texture
	// -------
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, GameLevel::width, GameLevel::height, 0, GL_RGBA, GL_UNSIGNED_BYTE, GameLevel::sprite_sheet);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, resource->getWidth(), resource->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, resource->getSpriteSheet());
	glGenerateMipmap(GL_TEXTURE_2D);
}

void GameObject::initPhysics(b2BodyType bodyType, b2Vec2 position, float radius)
{
	b2BodyDef bd;
	bd.type = bodyType;
	bd.position.Set(position.x, position.y);
	bd.userData.pointer = reinterpret_cast<uintptr_t>(physicProp);

	body = physicWorld->CreateBody(&bd);

	b2CircleShape shape;
	shape.m_p.Set(position.x, position.y);
	shape.m_radius = radius;

	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 0.1f;
	fd.friction = 0.f;
	fd.restitution = 0.5f;

	body->CreateFixture(&fd);

	updateObjectPosition();
}

void GameObject::initRectPhysics(b2BodyType bodyType, b2Vec2 position, float angle)
{
	b2BodyDef bd;
	bd.type = bodyType;
	bd.position.Set(position.x, position.y);
	bd.userData.pointer = reinterpret_cast<uintptr_t>(physicProp);

	body = physicWorld->CreateBody(&bd);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(physicProp->width - 0.007f, physicProp->height - 0.007f, {0.f, 0.f}, 0.f);

	b2FixtureDef fd;
	fd.shape = &boxShape;
	fd.density = 5.f;
	fd.friction = 0.f;

	body->CreateFixture(&fd);
	body->SetFixedRotation(true);

	//'' rotate: 0.7cm,1.2cm //original: 0.5cm, 1.8cm
	// positive - rotate left, negative - rotate right
	body->SetTransform(bd.position, angle);

	updateObjectPosition();
}

void GameObject::initPhysics(b2Vec2 pointStart, b2Vec2 pointEnd)
{

	b2BodyDef bd;
	bd.type = b2_staticBody;
	if( pointStart.x == pointEnd.x )
		bd.position.Set(pointStart.x, 0.f);
	else if( pointStart.y == pointEnd.y )
		bd.position.Set(0.f, pointEnd.y);
	else
		bd.position.Set(0.f, 0.f);
	bd.userData.pointer = reinterpret_cast<uintptr_t>(physicProp);

	body = physicWorld->CreateBody(&bd);

	b2EdgeShape wall;
	if( pointStart.x == pointEnd.x ) {
		pointStart.x = 0.f;
		pointEnd.x = 0.f;
	}
	else if( pointStart.y == pointEnd.y ) {
		pointStart.y = 0.f;
		pointEnd.y = 0.f;
	}

	wall.SetTwoSided(pointStart, pointEnd);

	body->CreateFixture(&wall, 10.f);
}

void GameObject::updateObjectPosition(b2Vec2 offset)
{
	float physicWidth = physicProp->width;
	float physicHeight = physicProp->height;

	// top right
	vertices[0] = body->GetWorldCenter().x - physicWidth + offset.x;
	vertices[1] = body->GetWorldCenter().y + physicHeight + offset.y;// - offset;
	// bottom right
	vertices[8] = body->GetWorldCenter().x - physicWidth + offset.x;
	vertices[9] = body->GetWorldCenter().y - physicHeight + offset.y;
	// bottom left
	vertices[16] = body->GetWorldCenter().x + physicWidth + offset.x;// - offset;
	vertices[17] = body->GetWorldCenter().y - physicHeight + offset.y;
	// top left
	vertices[24] = body->GetWorldCenter().x + physicWidth + offset.x;// - offset;
	vertices[25] = body->GetWorldCenter().y + physicHeight + offset.y;// - offset;

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GameObject::updateObjectUV()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
