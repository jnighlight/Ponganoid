#define BALL_MANAGER_CPP
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
#include "Ball.h"
#include "BallManager.h"
#include "random.h"
#include "playermanager.h"


BallManagerC* BallManagerC::sInstance=NULL;


BallManagerC *BallManagerC::CreateInstance()
{
	assert(sInstance==NULL);
	sInstance = new BallManagerC();
	return sInstance;
}

void BallManagerC::init()
{
	printf("Hey initing the ball manager!\n");
	ballPtrs = (BallC**)calloc(NUM_BALLS,sizeof(BallC*));

	ballPtrs[0] = new BallC(0.0f, 0.0f, 0.5f, 0.5f, 0, 1, PlayerManagerC::GetInstance()->getPlayer1Ptr());
	ballPtrs[0]->setRadius(BALL_RADIUS * SCALE_SIZE);
	ballPtrs[0]->enable();
	ballPtrs[0]->setID(0);

	ballPtrs[1] = new BallC(0.0f, 0.0f, 0.5f, 0.5f, 1, 2, PlayerManagerC::GetInstance()->getPlayer2Ptr());
	ballPtrs[1]->setRadius(BALL_RADIUS * SCALE_SIZE);
	ballPtrs[1]->enable();
	ballPtrs[1]->setID(1);

	lastBall = 1;
}

void BallManagerC::givePlayersBalls()
{
	ballPtrs[lastBall] = new BallC(0.0f, 0.0f, 0.5f, 0.5f, 0, 1, PlayerManagerC::GetInstance()->getPlayer1Ptr());
	ballPtrs[lastBall]->setRadius(BALL_RADIUS * SCALE_SIZE);
	ballPtrs[lastBall]->enable();
	ballPtrs[lastBall]->setID(0);
	lastBall++;

	ballPtrs[lastBall] = new BallC(0.0f, 0.0f, 0.5f, 0.5f, 1, 2, PlayerManagerC::GetInstance()->getPlayer2Ptr());
	ballPtrs[lastBall]->setRadius(BALL_RADIUS * SCALE_SIZE);
	ballPtrs[lastBall]->enable();
	ballPtrs[lastBall]->setID(1);
}

void BallManagerC::resetBalls()
{
	for (int i = 0; i < NUM_BALLS; i++) {
		if (ballPtrs[i] != nullptr) {
			delete ballPtrs[i];
			ballPtrs[i] = nullptr;
		}
	}
	lastBall = 0;

	ballPtrs[lastBall] = new BallC(0.0f, 0.0f, 0.5f, 0.5f, 0, 1, PlayerManagerC::GetInstance()->getPlayer1Ptr());
	ballPtrs[lastBall]->setRadius(BALL_RADIUS * SCALE_SIZE);
	ballPtrs[lastBall]->enable();
	ballPtrs[lastBall]->setID(0);
	lastBall++;

	ballPtrs[lastBall] = new BallC(0.0f, 0.0f, 0.5f, 0.5f, 1, 2, PlayerManagerC::GetInstance()->getPlayer2Ptr());
	ballPtrs[lastBall]->setRadius(BALL_RADIUS * SCALE_SIZE);
	ballPtrs[lastBall]->enable();
	ballPtrs[lastBall]->setID(1);
}

void BallManagerC::updateBalls(DWORD milliseconds)
{
	int i = 0;
	bool player1HasBall = false;
	bool player2HasBall = false;
    //for(uint32_t i=0;i<NUM_BALLS;++i)
	while(ballPtrs[i] != nullptr)
    {
       ballPtrs[i]->update(milliseconds);
	   if (ballPtrs[i]->isEnabled()) {
		   if (ballPtrs[i]->getPlayerOwner() == 1) {
			   player1HasBall = true;
		   }
		   if (ballPtrs[i]->getPlayerOwner() == 2) {
			   player2HasBall = true;
		   }
	   }
	   i++;
    }
	if (!player1HasBall) {
		lastBall++;
		ballPtrs[lastBall] = new BallC(0.0f, 0.0f, 0.5f, 0.5f, 0, 1, PlayerManagerC::GetInstance()->getPlayer1Ptr());
		ballPtrs[lastBall]->setRadius(BALL_RADIUS * SCALE_SIZE);
		ballPtrs[lastBall]->enable();
		ballPtrs[lastBall]->setID(0);
	}
	if (!player2HasBall) {
		lastBall++;
		ballPtrs[lastBall] = new BallC(0.0f, 0.0f, 0.5f, 0.5f, 0, 2, PlayerManagerC::GetInstance()->getPlayer2Ptr());
		ballPtrs[lastBall]->setRadius(BALL_RADIUS * SCALE_SIZE);
		ballPtrs[lastBall]->enable();
		ballPtrs[lastBall]->setID(0);
	}
}

void BallManagerC::slowdownBalls()
{
	int i = 0;
    //for(uint32_t i=0;i<NUM_BALLS;++i)
	while(ballPtrs[i] != nullptr)
    {
       ballPtrs[i]->slowdown();
	   i++;
    }
}

BallC *BallManagerC::getBallPtr(int32_t index)
{
	return ballPtrs[index];
}
void BallManagerC::renderBalls()
{
	int i = 0;
    //for(uint32_t i=0;i<NUM_BALLS;++i)
	while(ballPtrs[i] != nullptr)
    {
       ballPtrs[i]->render();
	   i++;
    }
}
void BallManagerC::shutdown()
{
	int i = 0;
    //for(uint32_t i=0;i<NUM_BALLS;++i)
	while(ballPtrs[i] != nullptr)
    {
		delete ballPtrs[i];
	   i++;
	}
	free(ballPtrs);
}

void BallManagerC::addBall(float_t initPosX, float_t initPosY, float_t velX, float_t velY, int ownedBy, float velMult)
{
	lastBall++;
	if (lastBall >= NUM_BALLS - 1) {
		return;
	}
	ballPtrs[lastBall] = new BallC(initPosX, initPosY, velX,velY,lastBall, ownedBy);
	ballPtrs[lastBall]->setRadius(BALL_RADIUS * SCALE_SIZE);
	ballPtrs[lastBall]->enable();
	ballPtrs[lastBall]->enable();
	ballPtrs[lastBall]->setID(lastBall);
}

void BallManagerC::multiplyBalls(int id) {
	int ballCount = 0;
	while(ballPtrs[ballCount] != nullptr)
    {
	   ballCount++;
    }

    for(uint32_t i=0;i<ballCount;++i)
    {
	   if (ballPtrs[i]->getPlayerOwner() == id && ballPtrs[i]->isEnabled()) {
		   ballPtrs[i]->splitBall();
	   }
    }
}