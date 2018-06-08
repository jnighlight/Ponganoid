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
#include "Block.h"
#include "field.h"
#include "fieldmanager.h"
#include "gamedefs.h"
#include "gameobjects.h"
#include "random.h"
#include "stateManager.h"
#include "inputmanager.h"
#include "SoundManager.h"


BlockC::BlockC(int id, float width, float height, float startX, float startY, TextureMapEnum textMapEnum)
	:mHealth(false)
	,curHealth(SILVER_HEALTH)
	,invincible(false)
{
    mEnabled = true;
    mCollInfo.shape = CollInfoC::SHAPE_RECTANGLE;
	mID = id;
	mWidth = width;
	mHeight = height;
	mPosition.x = startX;
	mPosition.y = startY;
	mBlockSprite.setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(textMapEnum), 1, mWidth, mHeight);
	if (textMapEnum == TextureMapEnum::BLOCK_SILVER_MAP) {
		invincible = false;
		mHealth = true;
		mBlockSprite.setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(textMapEnum), 6, mWidth, mHeight);
	}
	if (textMapEnum == TextureMapEnum::BLOCK_GOLD_MAP) {
		invincible = true;
		mHealth = false;
		mBlockSprite.setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(textMapEnum), 6, mWidth, mHeight);
	}
};

void BlockC::setType(TextureMapEnum textMapEnum)
{
	if (textMapEnum == TextureMapEnum::BLOCK_SILVER_MAP) {
		invincible = false;
		mHealth = true;
		curHealth = SILVER_HEALTH;
		mBlockSprite.setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(textMapEnum), 6, mWidth, mHeight);
	} else if (textMapEnum == TextureMapEnum::BLOCK_GOLD_MAP) {
		invincible = true;
		mHealth = false;
		mBlockSprite.setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(textMapEnum), 6, mWidth, mHeight);
	} else {
		invincible = false;
		mHealth = false;
		mBlockSprite.setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(textMapEnum), 1, mWidth, mHeight);
	}
}

BlockC::~BlockC()
{
};

void BlockC::update(DWORD milliseconds)
{
	mBlockSprite.update(milliseconds);
}

void BlockC::disable()
{
	mEnabled = false;
}

bool BlockC::isEnabled()
{
	return mEnabled;
}

void BlockC::render()
{
	mBlockSprite.render(mPosition);
}

void BlockC::setRandomColor()
{
	mBlockColor = getRangedRandom(0,256);
	mBlockColor += getRangedRandom(0,256) << 8;
	mBlockColor += getRangedRandom(0,256) << 16;
}

bool BlockC::applyDamage()
{
	if (invincible) {
		SoundManagerC::GetInstance()->playSound(SoundEnum::BLOCK_METALLIC_SOUND);
		return false;
	}
	if (mHealth) {
		--curHealth;
		if (curHealth <= 0) {
			disable();
			SoundManagerC::GetInstance()->playSound(SoundEnum::BLOCK_DESTROYED_SOUND);
			return true;
		}
		else
		{
			SoundManagerC::GetInstance()->playSound(SoundEnum::BLOCK_METALLIC_SOUND);
		}
	}
	else
	{
		disable();
		SoundManagerC::GetInstance()->playSound(SoundEnum::BLOCK_DESTROYED_SOUND);
		return true;
	}
	return false;
}
