#define SCORE_MANAGER_CPP
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
#include "ScoreManager.h"
#include "score.h"
//#include "Score.h"

ScoreManagerC* ScoreManagerC::sInstance=NULL;


ScoreManagerC *ScoreManagerC::CreateInstance()
{
	if(sInstance!=NULL)return sInstance;
	else

	sInstance = new ScoreManagerC();
	return sInstance;
}

void ScoreManagerC::init()
{
	mGameOver = NOT_OVER;
	mScore1Ptr = new ScoreC(1, SCORE_WIDTH, SCORE_HEIGHT, 14 * SCALE_SIZE, -10 * SCALE_SIZE, false);
	mScore2Ptr = new ScoreC(2, SCORE_WIDTH, SCORE_HEIGHT, 14 * SCALE_SIZE, 10 * SCALE_SIZE, true);
	curLevel = 1;
}

void ScoreManagerC::reset(bool ignoreLevel)
{
	mGameOver = NOT_OVER;
	if (!ignoreLevel) {
		mScore1Ptr->reset();
		mScore2Ptr->reset();
		curLevel = 1;
	}
}

ScoreC *ScoreManagerC::getScorePtr(int player)
{
	if (player == 1) {
		return mScore1Ptr;
	}
	if (player == 2) {
		return mScore2Ptr;
	}
	return nullptr;
}

ScoreC *ScoreManagerC::getScore1Ptr()
{
	return mScore1Ptr;
}

ScoreC *ScoreManagerC::getScore2Ptr()
{
	return mScore2Ptr;
}

void ScoreManagerC::renderScore()
{
	mScore1Ptr->render();
	mScore2Ptr->render();
}

void ScoreManagerC::shutdown()
{
	delete mScore1Ptr;
	delete mScore2Ptr;
}

ScoreManagerC::GameOverState ScoreManagerC::updateScores(DWORD milliseconds)
{
	mScore1Ptr->update(milliseconds);
	mScore2Ptr->update(milliseconds);
	return mGameOver;
}

bool ScoreManagerC::isRedHigher() {
	return mScore1Ptr->getScore() > mScore2Ptr->getScore();
}

void ScoreManagerC::incrementLevel()
{
	curLevel++;
	mGameOver = NEXT_LEVEL;
	if (curLevel > LEVEL_COUNT) {
		if (mScore1Ptr->getScore() > mScore2Ptr->getScore()) {
			mGameOver = RED_WON;
		} else {
			mGameOver = BLUE_WON;
		}
	}
}
