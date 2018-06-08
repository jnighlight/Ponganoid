#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "ShapeDraw.h"
#include "collInfo.h"
#include "object.h"
//#include "inputmapper.h"
#include "Score.h"
#include "gamedefs.h"
#include "gameobjects.h"
#include "random.h"
#include "inputmanager.h"
#include "SoundManager.h"
#include "ScoreManager.h"
#include "TextureMapManager.h"
#include "SoundManager.h"


ScoreC::ScoreC(int id, float width, float height, float startX, float startY, bool blue)
	:mId(id)
	,mScore(0)
{
    mEnabled = true;
	mWidth = width;
	mHeight = height;
	mPosition.x = startX;
	mPosition.y = startY;
	mLabelSpriteSheet.setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::TEXT_SCORE_MAP), 1, mWidth, mHeight);
	if (blue) {
		mColorSpriteSheet.setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::TEXT_BLUE_MAP), 1, mWidth / 1.5, mHeight);
	} else {
		mColorSpriteSheet.setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::TEXT_RED_MAP), 1, mWidth / 2, mHeight);
	}
	mNumberSpriteSheets[0].setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::TEXT_0_MAP), 1, 75.0f, 75.0f);
	mNumberSpriteSheets[1].setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::TEXT_1_MAP), 1, 75.0f, 75.0f);
	mNumberSpriteSheets[2].setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::TEXT_2_MAP), 1, 75.0f, 75.0f);
	mNumberSpriteSheets[3].setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::TEXT_3_MAP), 1, 75.0f, 75.0f);
	mNumberSpriteSheets[4].setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::TEXT_4_MAP), 1, 75.0f, 75.0f);
	mNumberSpriteSheets[5].setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::TEXT_5_MAP), 1, 75.0f, 75.0f);
	mNumberSpriteSheets[6].setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::TEXT_6_MAP), 1, 75.0f, 75.0f);
	mNumberSpriteSheets[7].setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::TEXT_7_MAP), 1, 75.0f, 75.0f);
	mNumberSpriteSheets[8].setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::TEXT_8_MAP), 1, 75.0f, 75.0f);
	mNumberSpriteSheets[9].setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::TEXT_9_MAP), 1, 75.0f, 75.0f);
};

void ScoreC::reset()
{
	mScore = 0;
}

ScoreC::~ScoreC()
{
};

void ScoreC::update(DWORD milliseconds)
{
}

void ScoreC::render()
{
	mPosition.y += SCALE_SIZE;
	mColorSpriteSheet.render(mPosition);
	mPosition.y -= SCALE_SIZE;
	mLabelSpriteSheet.render(mPosition);

    Coord2D mScorePos;
	mScorePos.x = mPosition.x - 35.0f;
	mScorePos.y = mPosition.y - SCALE_SIZE;
	int tensPlace = mScore / 10;
	mNumberSpriteSheets[tensPlace].render(mScorePos);
	mScorePos.x += 70.0f;
	int onesPlace = mScore % 10;
	mNumberSpriteSheets[onesPlace].render(mScorePos);
}

void ScoreC::incrementScore()
{
	mScore++;
	if (mScore >= (POINTS_BETWEEN_LEVELS * ScoreManagerC::GetInstance()->getCurrentLevel())) {
		SoundManagerC::GetInstance()->playSound(SoundEnum::DEATH_SOUND);
		ScoreManagerC::GetInstance()->incrementLevel();
	}
	else
	{
		SoundManagerC::GetInstance()->playSound(SoundEnum::ENEMY_DESTROYED_SOUND);
	}
}
