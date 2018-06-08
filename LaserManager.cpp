#define LASER_MANAGER_CPP
#include <assert.h>
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>	// Header File For Variable Argument Routines
#include <math.h>	// Header File For Math Operations
#include <gl\gl.h>	// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "collinfo.h"
#include "object.h"
#include "Laser.h"
#include "LaserManager.h"
#include "random.h"


LaserManagerC* LaserManagerC::sInstance=NULL;


LaserManagerC *LaserManagerC::CreateInstance()
{
	assert(sInstance==NULL);
	sInstance = new LaserManagerC();
	return sInstance;
}

void LaserManagerC::init()
{
	printf("Hey initing the ball manager!\n");
	for (int i = 0; i < LASERS_AVAIL; i++) {
		player1Lasers[i].disable();
		player1Lasers[i].setRadius(5.0f);
	}
	for (int i = 0; i < LASERS_AVAIL; i++) {
		player2Lasers[i].disable();
		player2Lasers[i].setRadius(5.0f);
	}
}

void LaserManagerC::reset()
{
	for (int i = 0; i < LASERS_AVAIL; i++) {
		player1Lasers[i].disable();
	}
	for (int i = 0; i < LASERS_AVAIL; i++) {
		player2Lasers[i].disable();
	}
}

void LaserManagerC::updateLasers(DWORD milliseconds)
{
	for (int i = 0; i < LASERS_AVAIL; i++) {
		if (player1Lasers[i].isEnabled()) {
			player1Lasers[i].update(milliseconds);
		}
	}
	for (int i = 0; i < LASERS_AVAIL; i++) {
		if (player2Lasers[i].isEnabled()) {
			player2Lasers[i].update(milliseconds);
		}
	}
}

void LaserManagerC::renderLasers()
{
	for (int i = 0; i < LASERS_AVAIL; i++) {
		if (player1Lasers[i].isEnabled()) {
			player1Lasers[i].render();
		}
	}
	for (int i = 0; i < LASERS_AVAIL; i++) {
		if (player2Lasers[i].isEnabled()) {
			player2Lasers[i].render();
		}
	}
}

void LaserManagerC::addLaser(float_t originX, float_t originY, int playerWhoCreated)
{
	float distance = 100.0f;

	if (playerWhoCreated == 1) {
		originY += 50.0f;
		for (int i = 0; i < LASERS_AVAIL; i += 2) {
			if (!player1Lasers[i].isEnabled() && !player1Lasers[i + 1].isEnabled()) {
				player1Lasers[i].setPosition(originX - distance, originY);
				player1Lasers[i].setPlayerCreator(playerWhoCreated);
				player1Lasers[i].enable();
				player1Lasers[i + 1].setPosition(originX + distance, originY);
				player1Lasers[i + 1].setPlayerCreator(playerWhoCreated);
				player1Lasers[i + 1].enable();
				break;
			}
		}
	} else {
		originY -= 50.0f;
		for (int i = 0; i < LASERS_AVAIL; i += 2) {
			if (!player2Lasers[i].isEnabled() && !player2Lasers[i + 1].isEnabled()) {
				player2Lasers[i].setPosition(originX - distance, originY);
				player2Lasers[i].setPlayerCreator(playerWhoCreated);
				player2Lasers[i].enable();
				player2Lasers[i + 1].setPosition(originX + distance, originY);
				player2Lasers[i + 1].setPlayerCreator(playerWhoCreated);
				player2Lasers[i + 1].enable();
				break;
			}
		}
	}
}

