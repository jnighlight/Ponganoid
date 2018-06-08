#define POWERUP_MANAGER_CPP
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
#include "PowerupManager.h"
#include "Powerup.h"

PowerupManagerC* PowerupManagerC::sInstance=NULL;

PowerupManagerC *PowerupManagerC::CreateInstance()
{
	if(sInstance!=NULL)return sInstance;
	else

	sInstance = new PowerupManagerC();
	return sInstance;
}

void PowerupManagerC::init()
{
	mDeathMode = false;
	timeSinceDrop = 0;
	printf("Hey initing the ball manager!\n");
	mPowerup = nullptr;
	mPowerup2 = nullptr;
}

void PowerupManagerC::reset()
{
	if (mPowerup != nullptr) {
		delete mPowerup;
		mPowerup = nullptr;
	}
	if (mPowerup2 != nullptr) {
		delete mPowerup2;
		mPowerup2 = nullptr;
	}
	mDeathMode = false;
	timeSinceDrop = 0;
}

PowerupC* PowerupManagerC::getPowerup()
{
	return mPowerup;
}

PowerupC* PowerupManagerC::getPowerup2()
{
	return mPowerup2;
}

int PowerupManagerC::getMaxPowerups() {
	return MAX_BLOCKS;
}
void PowerupManagerC::renderPowerup()
{
	if (mPowerup != nullptr && mPowerup->getEnabled()) {
		mPowerup->render();
	}
	if (mPowerup2 != nullptr && mPowerup2->getEnabled()) {
		mPowerup2->render();
	}
}

void PowerupManagerC::possiblySpawnPowerup(float x, float y, int playerDirection)
{
	if (playerDirection == 1 && mPowerup == nullptr && rand() % 3 == 0) {
		mPowerup = new PowerupC(1, POWERUP_WIDTH, POWERUP_HEIGHT, x, y, false);
	}
	if (playerDirection == 2 && mPowerup2 == nullptr && rand() % 3 == 0) {
		mPowerup2 = new PowerupC(2, POWERUP_WIDTH, POWERUP_HEIGHT, x, y, true);
	}
}

void PowerupManagerC::updatePowerups(DWORD milliseconds)
{
	if (mDeathMode) {
		timeSinceDrop += milliseconds;
		if ((timeSinceDrop / 1000.0) > SECONDS_IN_DEATHMODE) {
			timeSinceDrop = 0;
			if (mPowerup == nullptr) {
				mPowerup = new PowerupC(1, POWERUP_WIDTH, POWERUP_HEIGHT, 0, 0, false, true);
			}
			if (mPowerup2 == nullptr) {
				mPowerup2 = new PowerupC(2, POWERUP_WIDTH, POWERUP_HEIGHT, 0, 0, true, true);
			}
		}
	}

	if (mPowerup != nullptr) {
		if (!mPowerup->getEnabled()) {
			delete mPowerup;
			mPowerup = nullptr;
		}
		else {
			mPowerup->update(milliseconds);
		}
	}

	if (mPowerup2 != nullptr) {
		if (!mPowerup2->getEnabled()) {
			delete mPowerup2;
			mPowerup2 = nullptr;
		}
		else {
			mPowerup2->update(milliseconds);
		}
	}
}
