#include <Input.h>

using namespace KitKat;

Input::Input(){}

Input::~Input(){}

// Public

void Input::processPosition(int x, int y)
{
	_inputPos = glm::vec2(x, y);
}

void Input::processClick(bool click)
{
	_click = click;
}

glm::vec2 Input::getPosition()
{
	return _inputPos;
}

bool Input::isClick()
{
	return _click;
}

// Private