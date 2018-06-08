#define PLAYER_MANAGER_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "collinfo.h"
#include "object.h"
#include "field.h"
#include "PlayerManager.h"
#include "Player.h"

PlayerManagerC* PlayerManagerC::sInstance=NULL;


PlayerManagerC *PlayerManagerC::CreateInstance()
{
	if(sInstance!=NULL)return sInstance;
	else

	sInstance = new PlayerManagerC();
	return sInstance;
}

void PlayerManagerC::init()
{
	mPlayer1Ptr = new PlayerC(1, PLAYER_WIDTH, PLAYER_HEIGHT, 0, -12 * SCALE_SIZE);
	mPlayer2Ptr = new PlayerC(2, PLAYER_WIDTH, PLAYER_HEIGHT, 0, 12 * SCALE_SIZE);
}

void PlayerManagerC::reset()
{
	mPlayer1Ptr->reset();
	mPlayer2Ptr->reset();
}

PlayerC *PlayerManagerC::getPlayerPtr(int player)
{
	if (player == 1) {
		return mPlayer1Ptr;
	}
	if (player == 2) {
		return mPlayer2Ptr;
	}
	return nullptr;
}

PlayerC *PlayerManagerC::getPlayer1Ptr()
{
	return mPlayer1Ptr;
}

PlayerC *PlayerManagerC::getPlayer2Ptr()
{
	return mPlayer2Ptr;
}

void PlayerManagerC::renderPlayer()
{
	mPlayer1Ptr->render();
	mPlayer2Ptr->render();
}

void PlayerManagerC::shutdown()
{
	delete mPlayer1Ptr;
	delete mPlayer2Ptr;
}

void PlayerManagerC::updatePlayers(DWORD milliseconds)
{
	mPlayer1Ptr->update(milliseconds);
	mPlayer2Ptr->update(milliseconds);
}
