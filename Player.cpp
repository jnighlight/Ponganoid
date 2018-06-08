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
#include "Player.h"
#include "field.h"
#include "fieldmanager.h"
#include "gamedefs.h"
#include "gameobjects.h"
#include "random.h"
#include "stateManager.h"
#include "inputmanager.h"
#include "SoundManager.h"
#include "TextureMapManager.h"
#include "ballmanager.h"
#include "powerupmanager.h"
#include "powerup.h"
#include "lasermanager.h"


PlayerC::PlayerC(int id, float width, float height, float startX, float startY)
	:mTimeSinceLastShot(0)
	,mId(id)
	,mStunned(false)
{
    mEnabled = true;
    mCollInfo.shape = CollInfoC::SHAPE_RECTANGLE;
	mWidth = width;
	mOriginalWidth = width;
	mHeight = height;
	mOriginalHeight = height;
	mPosition.x = startX;
	mPosition.y = startY;
	mVelocity.x = PLAYER_MOVE_SPEED;
	mVelocity.y = PLAYER_MOVE_SPEED;
	if (mId == 1) {
		mNormalSpriteSheet = new SpriteSheetC( TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::VAUS_DEFAULT_MAP), 1, mOriginalWidth, height);
		mExtendSpriteSheet = new SpriteSheetC( TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::VAUS_EXPAND_MAP), 1, mOriginalWidth * EXTEND_LENGTH, height);
		mLaserSpriteSheet = new SpriteSheetC( TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::VAUS_LASER_MAP), 1, mOriginalWidth, height);
	} else {
		mNormalSpriteSheet = new SpriteSheetC( TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::VAUS_DEFAULT_2_MAP), 1, mOriginalWidth, height);
		mExtendSpriteSheet = new SpriteSheetC( TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::VAUS_EXPAND_2_MAP), 1, mOriginalWidth * EXTEND_LENGTH, height);
		mLaserSpriteSheet = new SpriteSheetC( TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::VAUS_LASER_2_MAP), 1, mOriginalWidth, height);
	}
	mPlayerState = NORMAL_STATE;
};

void PlayerC::reset()
{
	mTimeSinceLastShot = 0;
	mStunned = false;
	mPosition.x = 0;
	mPlayerState = NORMAL_STATE;
};

PlayerC::~PlayerC()
{
};

void PlayerC::update(DWORD milliseconds)
{
	mTimeSinceLastShot += milliseconds;
	if (mPlayerState == EXPAND_STATE) {
		mWidth = mOriginalWidth * EXTEND_LENGTH;
	} else {
		mWidth = mOriginalWidth;
	}

	if (mStunned) {
		mTimeSinceStunned += milliseconds;
		if ((mTimeSinceStunned / 1000) >= LASER_STUN_TIME) {
			mStunned = false;
		}
	} else {
		InputManagerC *inputManager = InputManagerC::GetInstance();
		if (inputManager->isMovingLeft(mId)) {
			mPosition.x -= mVelocity.x*milliseconds/10;
		}
		else if (inputManager->isMovingRight(mId)) {
			mPosition.x += mVelocity.x*milliseconds/10;
		}
		if (mPlayerState == LASER_STATE && inputManager->isPressingActive(mId)) {
			attemptToSpawnBullets();
		}
	}
	DoCollisions();
}

void PlayerC::attemptToSpawnBullets() {
	if (mTimeSinceLastShot > millisecondsBetweenBullets) {
		LaserManagerC::GetInstance()->addLaser(mPosition.x, mPosition.y, mId);
		SoundManagerC::GetInstance()->playSound(SoundEnum::LASER_SOUND);
		mTimeSinceLastShot = 0;
	}
}

void PlayerC::DoCollisions()
{
	CollideField();
	CollidePowerup(PowerupManagerC::GetInstance()->getPowerup());
	CollidePowerup(PowerupManagerC::GetInstance()->getPowerup2());
}

void PlayerC::CollideField(void)
{
	FieldC *field = FieldManagerC::GetInstance()->getFieldPtr();


	float_t rightSide = field->getPosition()->x+((float_t)field->getWidth()/2.0f);
	float_t leftSide = field->getPosition()->x-((float_t)field->getWidth()/2.0f);
	float_t topSide = field->getPosition()->y+((float_t)field->getHeight()/2.0f);
	float_t bottomSide = field->getPosition()->y-((float_t)field->getHeight()/2.0f);

	float halfWidth = mWidth / 2.0f;
	
	if(mPosition.x - halfWidth <= leftSide  )
	{
		mPosition.x = leftSide + halfWidth;
	}
	if(mPosition.x + halfWidth >= rightSide  )
	{
		mPosition.x = rightSide - halfWidth;
	}
};

void PlayerC::CollidePowerup(PowerupC* powerup)
{
	if (powerup == nullptr) {
		return;
	}

	float_t rightSide = mPosition.x + (mWidth/2.0f);
	float_t leftSide = mPosition.x - (mWidth/2.0f);
	float_t topSide = mPosition.y + (mHeight/2.0f);
	float_t bottomSide = mPosition.y - (mHeight/2.0f);

	float_t powerupRightSide = powerup->getPosition()->x  + ((float_t)powerup->getWidth()/2.0f);
	float_t powerupLeftSide = powerup->getPosition()->x   - ((float_t)powerup->getWidth()/2.0f);
	float_t powerupTopSide = powerup->getPosition()->y    + ((float_t)powerup->getHeight()/2.0f);
	float_t powerupBottomSide = powerup->getPosition()->y - ((float_t)powerup->getHeight()/2.0f);

	bool collision = rectanglesCollide(leftSide, topSide, rightSide, bottomSide, powerupLeftSide, powerupTopSide, powerupRightSide, powerupBottomSide); 

	if (collision) {
		switch (powerup->getType())
		{
		case PowerupC::SPEED_DOWN:
			BallManagerC::GetInstance()->slowdownBalls();
			mPlayerState = NORMAL_STATE;
			break;
		case PowerupC::EXPAND:
			if (mPlayerState != EXPAND_STATE)
			{
				mPlayerState = EXPAND_STATE;
				SoundManagerC::GetInstance()->playSound(SoundEnum::VAUS_EXPAND_SOUND);
			}
			break;
		case PowerupC::DISRUPTION:
			BallManagerC::GetInstance()->multiplyBalls(mId);
			mPlayerState = NORMAL_STATE;
			break;
		case PowerupC::CATCH:
			mPlayerState = CATCH_STATE;
			break;
		case PowerupC::LASER:
			mPlayerState = LASER_STATE;
			break;
		default:
			break;
		}
		powerup->disable();
	}
};

void PlayerC::render()
{
	switch (mPlayerState)
	{
		case PlayerC::EXPAND_STATE:
			mExtendSpriteSheet->render(mPosition);
			break;
		case PlayerC::LASER_STATE:
			mLaserSpriteSheet->render(mPosition);
			break;
		default:
			mNormalSpriteSheet->render(mPosition);
			break;
	}
}

void PlayerC::stun() {
	mStunned = true;
	mTimeSinceStunned = 0;
}
