#include "Text.h"


Text::Text()
{
}

Text::Text(Resource *fontRes, b2Vec2 position, b2Vec2 textUV)
{
	this->fontRes = fontRes;

	// top right position
	vertices[0] = position.x + 0.05f; //0.75f;
	vertices[1] = position.y;
	vertices[2] = 0.0f;

	// bottom right position
	vertices[8] = position.x + 0.05f; //0.75f;
	vertices[9] = position.y - 0.08f; //-0.43f;
	vertices[10] = 0.0f;

	// bottom left position
	vertices[16] = position.x;
	vertices[17] = position.y - 0.08f; // -0.43f;
	vertices[18] = 0.0f;

	// top left position
	vertices[24] = position.x;
	vertices[25] = position.y;
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
	vertices[6] = textUV.x + 0.045f;
	vertices[7] = textUV.y - 0.1f;

	// bottom right texture coords
	vertices[14] = textUV.x + 0.045f;
	vertices[15] = textUV.y;

	// bottom left texture coords
	vertices[22] = textUV.x;
	vertices[23] = textUV.y;

	// top left texture coords
	vertices[30] = textUV.x;
	vertices[31] = textUV.y - 0.1f;
}

Text::~Text()
{
}

void Text::create(unsigned int shader)
{
	createBuffer();
	CreateTexture(fontRes);

	transformLoc = glGetUniformLocation(shader, "transform");
}

void Text::draw()
{
	if( getHide() )
		return;

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformGameObject));
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, tex);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Text::updateText(char text)
{
	switch( text ) {
	case '0':
		locateUV({ 1.077f, 0.23f });
		break;

	case '1':
		locateUV({ 1.13f, 0.23f });
		break;

	case '2':
		locateUV({ 1.21f, 0.23f });
		break;

	case '3':
		locateUV({ 1.28f, 0.23f });
		break;

	case '4':
		locateUV({ 1.34f, 0.23f });
		break;

	case '5':
		locateUV({ 1.41f, 0.23f });
		break;

	case '6':
		locateUV({ 1.47f, 0.23f });
		break;

	case '7':
		locateUV({ 1.54f, 0.23f });
		break;

	case '8':
		locateUV({ 1.61f, 0.23f });
		break;

	case '9':
		locateUV({ 1.67f, 0.23f });
		break;

	}

	updateObjectUV();
}

void Text::locateUV(b2Vec2 textUV)
{
	// top right texture coords
	vertices[6] = textUV.x + 0.055f;
	vertices[7] = textUV.y - 0.1f;

	// bottom right texture coords
	vertices[14] = textUV.x + 0.055f;
	vertices[15] = textUV.y;

	// bottom left texture coords
	vertices[22] = textUV.x;
	vertices[23] = textUV.y;

	// top left texture coords
	vertices[30] = textUV.x;
	vertices[31] = textUV.y - 0.1f;
}
