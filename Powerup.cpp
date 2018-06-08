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
#include "Powerup.h"
#include "field.h"
#include "fieldmanager.h"
#include "gamedefs.h"
#include "gameobjects.h"
#include "random.h"
#include "stateManager.h"
#include "inputmanager.h"
#include "TextureMapManager.h"


PowerupC::PowerupC(int id, float width, float height, float startX, float startY, bool moveDown, bool forceDisrupt)
{
    mEnabled = true;
    mCollInfo.shape = CollInfoC::SHAPE_RECTANGLE;
	mWidth = width;
	mHeight = height;
	mPosition.x = startX;
	mPosition.y = startY;
	mVelocity.x = 10;
	mVelocity.y = 10;
	if (!moveDown) {
		mVelocity.y *= -1;
	}

	int randomNum = rand() % 5;
	mPowerupType = (PowerupType)randomNum;
	if (forceDisrupt) {
		mPowerupType = PowerupC::DISRUPTION;
	}

	switch (mPowerupType)
	{
	case PowerupC::SPEED_DOWN:
		mSpriteSheet = new SpriteSheetC( TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::POWERUP_SLOW_MAP), 6, width, height, 100);
		break;
	case PowerupC::CATCH:
		mSpriteSheet = new SpriteSheetC( TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::POWERUP_CATCH_MAP), 6, width, height, 100);
		break;
	case PowerupC::EXPAND:
		mSpriteSheet = new SpriteSheetC( TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::POWERUP_EXPAND_MAP), 6, width, height, 100);
		break;
	case PowerupC::DISRUPTION:
		mSpriteSheet = new SpriteSheetC( TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::POWERUP_DISRUPT_MAP), 6, width, height, 100);
		break;
	case PowerupC::LASER:
		mSpriteSheet = new SpriteSheetC( TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::POWERUP_LASER_MAP), 6, width, height, 100);
		break;
	default:
		break;
	}
};

PowerupC::~PowerupC()
{
};

void PowerupC::update(DWORD milliseconds)
{
	mSpriteSheet->update(milliseconds);
	mPosition.y += mVelocity.y*milliseconds/10;
	DoCollisions();
}
void PowerupC::DoCollisions()
{
	CollideField();
}

void PowerupC::CollideField(void)
{
	FieldC *field = FieldManagerC::GetInstance()->getFieldPtr();

	float_t rightSide = field->getPosition()->x+((float_t)field->getWidth()/2.0f);
	float_t leftSide = field->getPosition()->x-((float_t)field->getWidth()/2.0f);
	float_t topSide = field->getPosition()->y+((float_t)field->getHeight()/2.0f);
	float_t bottomSide = field->getPosition()->y-((float_t)field->getHeight()/2.0f);
	float halfHeight = mHeight / 2.0f;
	
	if((mPosition.y - halfHeight <= bottomSide) || (mPosition.y + halfHeight >= topSide))
	{
		disable();
	}
};

void PowerupC::render()
{
	if (!mEnabled) {
		return;
	}
	mSpriteSheet->render(mPosition);
	return;
	char8_t red = (char8_t)((mPowerupColor>>16)& 0xFF);
	char8_t green = (char8_t)((mPowerupColor>>8) & 0xFF);
	char8_t blue = (char8_t)((mPowerupColor>>0) & 0xFF);
	bool filledVal;

	float halfWidth = mWidth / 2.0f;
	float halfHeight = mHeight / 2.0f;
	DrawRect(mPosition.x - halfWidth, mPosition.y - halfHeight, mPosition.x + halfWidth, mPosition.y + halfHeight, 0x88, 0x88, 0x88, false);
	printf("DRAWING");

	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, 2);
	glBegin (GL_QUADS);

	glColor4ub(0xFF, 0xFF, 0xFF,0xFF);
	glTexCoord2f (0, 0);
	glVertex3f (mPosition.x - halfWidth, mPosition.y - halfHeight, 0.0);
	glTexCoord2f (1, 0);
	glVertex3f (mPosition.x + halfWidth, mPosition.y - halfHeight, 0.0);
	glTexCoord2f (1, 1);
	glVertex3f (mPosition.x + halfWidth, mPosition.y + halfHeight, 0.0);
	glTexCoord2f (0, 1);
	glVertex3f (mPosition.x - halfWidth, mPosition.y + halfHeight, 0.0);
	glEnd ();
}
