#include <windows.h>											// Header File For Windows
#include "baseTypes.h"
#include "InputManager.h"

InputManagerC* InputManagerC::sInstance = NULL;

InputManagerC *InputManagerC::CreateInstance()
{
	if(sInstance!=NULL)return sInstance;
	else

	sInstance = new InputManagerC();
	return sInstance;
}

void InputManagerC::update()
{
	movingRight[0] = GetAsyncKeyState(VK_D);
	movingLeft[0] = GetAsyncKeyState(VK_A);
	active[0] = GetAsyncKeyState(VK_W);

	movingRight[1] = GetAsyncKeyState(VK_RIGHT);
	movingLeft[1] = GetAsyncKeyState(VK_LEFT);
	active[1] = GetAsyncKeyState(VK_UP);

	enter = GetAsyncKeyState(VK_RETURN);
	backspace = GetAsyncKeyState(VK_BACK);
}

bool InputManagerC::isMovingRight(int player)
{
	return movingRight[player - 1];
}

bool InputManagerC::isMovingLeft(int player)
{
	return movingLeft[player - 1];
}

bool InputManagerC::isPressingActive(int player)
{
	return active[player - 1];
}

bool InputManagerC::isPressingEnter()
{
	return enter;
}

bool InputManagerC::isPressingBackspace()
{
	return backspace;
}

/*
bool InputManagerC::isPressingUp(int player)
{
	return up;
}
*/
