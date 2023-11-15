#include "MenuScreen.h"

MenuScreen::MenuScreen() : Screen()
{
	menuRes = new Resource(RES_PATH + "menu.png", true);
}

MenuScreen::~MenuScreen()
{
}
