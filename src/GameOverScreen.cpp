#include "GameOverScreen.h"

GameOverScreen::GameOverScreen() : Screen()
{
	menuRes = new Resource(RES_PATH + "gameover.png", true);
}

GameOverScreen::~GameOverScreen()
{
}

