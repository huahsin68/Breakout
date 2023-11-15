/*
 * Score.cpp
 *
 *  Created on: Feb 28, 2023
 *      Author: kokhoe
 */
#include "Score.h"


Score::Score()
{
	fontRes = new Resource("../resources/font.png");

	float x = 0.f;
	float posY = 0.98f;
	textS = new Text(fontRes, { x, posY }, { 0.41f, 0.48f });
	textC = new Text(fontRes, { x = x + 0.055f, posY }, { 0.345f, 0.355f });
	textO = new Text(fontRes, { x = x + 0.055f, posY }, { 0.145f, 0.48f });
	textR = new Text(fontRes, { x = x + 0.055f, posY }, { 0.345f, 0.48f });
	textE = new Text(fontRes, { x = x + 0.055f, posY }, { 0.477f, 0.355f });
	textDotDot = new Text(fontRes, { x = x + 0.055f, posY }, { -1.245f, 0.23f });

	digit1 = new Text(fontRes, { x = x + 0.055f, posY }, { 1.077f, 0.23f });
	digit2 = new Text(fontRes, { x = x + 0.045f, posY }, { 1.13f, 0.23f });
	digit2->setHide(true);
}

Score::~Score()
{
}

void Score::create(unsigned int shader)
{
	textS->create(shader);
	textC->create(shader);
	textO->create(shader);
	textR->create(shader);
	textE->create(shader);
	textDotDot->create(shader);

	digit1->create(shader);
	digit2->create(shader);
}

void Score::draw()
{
	textS->draw();
	textC->draw();
	textO->draw();
	textR->draw();
	textE->draw();
	textDotDot->draw();

	digit1->draw();
	digit2->draw();
}

void Score::updateScore()
{
	int tmpScore = score;
	int n = log10(score) + 1;
	int i;
	char* numberArray = (char*)calloc(n, sizeof(char));

	for (i = n - 1; i >= 0; --i, tmpScore /= 10) {
		numberArray[i] = (tmpScore % 10) + '0';
	}

	if( score > 9 ) {
		digit1->updateText(numberArray[0]);

		digit2->setHide(false);
		digit2->updateText(numberArray[1]);
	}
	else
		digit1->updateText(numberArray[0]);
}
