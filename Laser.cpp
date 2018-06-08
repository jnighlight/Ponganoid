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
#include "ball.h"
#include "field.h"
#include "fieldmanager.h"
#include "gamedefs.h"
#include "gameobjects.h"
#include "random.h"
#include "stateManager.h"
#include "inputmanager.h"
#include "playermanager.h"
#include "player.h"
#include "blockmanager.h"
#include "block.h"
#include "laser.h"
#include "powerupmanager.h"

void LaserC::moveUp()
{
	int x;
	x=5;
}

LaserC::LaserC(float initPosX,float initPosY, int playerWhoCreated)
	:playerCreator(playerWhoCreated)
{
	mEnabled = true;
	mPosition.x = initPosX;
	mPosition.y = initPosY;
}
LaserC::LaserC()
{
    mEnabled = true;
    mCollInfo.shape = CollInfoC::SHAPE_CIRCLE;

};
LaserC::~LaserC()
{
};

void LaserC::update(DWORD milliseconds)
{
	if (mEnabled) {
		if (playerCreator == 1) {
			mPosition.y += bulletSpeed * milliseconds / 10;
		} else {
			mPosition.y -= bulletSpeed * milliseconds / 10;
		}
		DoCollisions();
	}
}

void LaserC::DoCollisions()
{
	CollideField();
	CollideBlocks();
	CollidePlayer(PlayerManagerC::GetInstance()->getPlayer1Ptr());
	CollidePlayer(PlayerManagerC::GetInstance()->getPlayer2Ptr());
}

void LaserC::CollideField(void)
{
	FieldC *field = FieldManagerC::GetInstance()->getFieldPtr();

	float_t rightSide = field->getPosition()->x+((float_t)field->getWidth()/2.0f);
	float_t leftSide = field->getPosition()->x-((float_t)field->getWidth()/2.0f);
	float_t topSide = field->getPosition()->y+((float_t)field->getHeight()/2.0f);
	float_t bottomSide = field->getPosition()->y-((float_t)field->getHeight()/2.0f);
	
	if ((mPosition.x - mRadius <= leftSide) || (mPosition.x + mRadius >= rightSide) || (mPosition.y - mRadius <= bottomSide) || (mPosition.y + mRadius >= topSide)) {
		mEnabled = false;
	}
};

void LaserC::CollidePlayer(PlayerC* player)
{
	float_t rightSide = player->getPosition()->x+((float_t)player->getWidth()/2.0f);
	float_t leftSide = player->getPosition()->x-((float_t)player->getWidth()/2.0f);
	float_t topSide = player->getPosition()->y+((float_t)player->getHeight()/2.0f);
	float_t bottomSide = player->getPosition()->y-((float_t)player->getHeight()/2.0f);

	if (mPosition.x <= rightSide && mPosition.x >= leftSide && mPosition.y >= bottomSide && mPosition.y <= topSide) {
		player->stun();
		disable();
	}
};

void LaserC::CollideBlocks()
{
	BlockC** blockArray = BlockManagerC::GetInstance()->getBlocks();

	for (int i = 0; i < BlockManagerC::GetInstance()->getMaxBlocks(); i++) {
		BlockC* curBlock = blockArray[i];
		if (curBlock == nullptr) {
			return;
		}
		if (!curBlock->isEnabled()) {
			continue;
		}

		float_t rightSide = mPosition.x + (mRadius);
		float_t leftSide = mPosition.x - (mRadius);
		float_t topSide = mPosition.y + (mRadius);
		float_t bottomSide = mPosition.y - (mRadius);

		float_t blockRightSide = curBlock->getPosition()->x + ((float_t)curBlock->getWidth()/2.0f);
		float_t blockLeftSide = curBlock->getPosition()->x - ((float_t)curBlock->getWidth()/2.0f);
		float_t blockTopSide = curBlock->getPosition()->y + ((float_t)curBlock->getHeight()/2.0f);
		float_t blockBottomSide = curBlock->getPosition()->y - ((float_t)curBlock->getHeight()/2.0f);

		bool collision = rectanglesCollide(leftSide, topSide, rightSide, bottomSide, blockLeftSide, blockTopSide, blockRightSide, blockBottomSide); 


		if (collision) {
			if (curBlock->applyDamage()) {
				PowerupManagerC::GetInstance()->possiblySpawnPowerup(curBlock->getPosition()->x, curBlock->getPosition()->y, playerCreator);
			}
			mEnabled = false;
		}
	}
};

void LaserC::render()
{
	if (mEnabled) {
		DrawCircle(mRadius,mPosition.x,mPosition.y,0xFF,0x00,0x00,false);
	}
}
