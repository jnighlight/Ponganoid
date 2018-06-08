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
#include "powerupmanager.h"
#include "ballmanager.h"
#include "texturemapmanager.h"
#include "SoundManager.h"
#include "ScoreManager.h"
#include "Score.h"


BallC::BallC(float initPosX,float initPosY,float initVelX,float initVelY,int id, int ownedById, PlayerC* ownedBy/* = nullptr*/)
	:mCaught(false)
	,mCaughtBy(ownedBy)
	,mCaughtOffset(0.0f)
	,mVelocityMult(MIN_VEL)
	,mHitBlocks(0)
	,mBallState(NORMAL)
	,mPlayerOwner(ownedById)
{
	//Choose the sprite sheet that matches our character
	if (ownedById == 1) {
		mBallSprite = new SpriteSheetC(TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::BALL_RED_MAP), 1, 10.0f, 10.0f);	//gonna edit height/width later
	} else {
		mBallSprite = new SpriteSheetC(TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::BALL_BLUE_MAP), 1, 10.0f, 10.0f);
	}
	mPosition.x = initPosX;
	mPosition.y = initPosY;
	mVelocity.x = initVelX;
	mVelocity.y = initVelY;

	//If the ball is attached to a player, place our location relative to the attached player
	if (mCaughtBy != nullptr) {
		mBallState = START;
		mPosition.x = mCaughtBy->getPosition()->x;
		if (ownedById == 1) {
			mPosition.y = mCaughtBy->getPosition()->y + (mCaughtBy->getHeight() / 2.0f) + (RADIUS);
		} else {
			mPosition.y = mCaughtBy->getPosition()->y - (mCaughtBy->getHeight() / 2.0f) - (RADIUS);
		}
	}
}

BallC::BallC()
{
    mEnabled = true;
    mCollInfo.shape = CollInfoC::SHAPE_CIRCLE;
};

BallC::~BallC()
{
};

//Main update thread for ball
void BallC::update(DWORD milliseconds)
{
	//If we're not in play, no reason to do anything
	if (!mEnabled) {
		return;
	}

	//Start mode is very similar to catch mode. We keep our position relative until the action button is pressed
	if (mBallState == START) {
		InputManagerC* inputMan = InputManagerC::GetInstance();
		if (InputManagerC::GetInstance()->isPressingActive(mCaughtBy->getId())) {
			mBallState = NORMAL;
			release();
		} else {
			mPosition.x = mCaughtBy->getPosition()->x;
			//We want to be on top of the bottom paddle, and under the top paddle
			if (mCaughtBy->getId() == 1) {
				mPosition.y = mCaughtBy->getPosition()->y + (mCaughtBy->getHeight() / 2.0f) + (mRadius);
			} else {
				mPosition.y = mCaughtBy->getPosition()->y - (mCaughtBy->getHeight() / 2.0f) - (mRadius);
			}
			return;
		}
	}
	//If the player caught the ball and the player hits active, this ball is not caught
	if (mCaught && (InputManagerC::GetInstance()->isPressingActive(mCaughtBy->getId()) || mCaughtBy->getState() != PlayerC::CATCH_STATE)) {
		release();
	}
	//...otherwise keep our position relative
	if (mCaught) {
		mPosition.x = mCaughtBy->getPosition()->x - mCaughtOffset;
	} else {
		//If we're a free ball, move based on our velocity and check for collisions
		mPosition.x += mVelocity.x*milliseconds/10 * mVelocityMult;
		mPosition.y += mVelocity.y*milliseconds/10 * mVelocityMult;

		DoCollisions();
	}
}

void BallC::DoCollisions()
{
	CollideField();
	newCollideBlocks();
	newCollidePlayer(PlayerManagerC::GetInstance()->getPlayer1Ptr());
	CollideDeadZone(PlayerManagerC::GetInstance()->getPlayer1Ptr(), false);
	newCollidePlayer(PlayerManagerC::GetInstance()->getPlayer2Ptr());
	CollideDeadZone(PlayerManagerC::GetInstance()->getPlayer2Ptr(), true);
}

//Checks for collisions with the play field
void BallC::CollideField(void)
{
	FieldC *field = FieldManagerC::GetInstance()->getFieldPtr();

	//Grabbing the x and y stats for the field
	float_t rightSide = field->getPosition()->x+((float_t)field->getWidth()/2.0f);
	float_t leftSide = field->getPosition()->x-((float_t)field->getWidth()/2.0f);
	float_t topSide = field->getPosition()->y+((float_t)field->getHeight()/2.0f);
	float_t bottomSide = field->getPosition()->y-((float_t)field->getHeight()/2.0f);
	
	//If we're outside of the field, scootch us back into the field
	if(mPosition.x- mRadius <= leftSide  )
	{
		mVelocity.x = -mVelocity.x;
		mPosition.x = leftSide + mRadius;
	}
	if(mPosition.x+ mRadius >= rightSide  )
	{
		mVelocity.x = -mVelocity.x;
		mPosition.x = rightSide - mRadius;
	}
	if(mPosition.y- mRadius <= bottomSide  )
	{
		mVelocity.y = -mVelocity.y;
		mPosition.y = bottomSide + mRadius;
	}
	if(mPosition.y+ mRadius >= topSide  )
	{
		mVelocity.y = -mVelocity.y;
		mPosition.y = topSide - mRadius;
	}
};

void BallC::newCollidePlayer(PlayerC* player)
{
	//Grabbing data about our ball
	float_t rightSide = mPosition.x + mRadius;
	float_t leftSide = mPosition.x - mRadius;
	float_t topSide = mPosition.y + mRadius;
	float_t bottomSide = mPosition.y - mRadius;

	//Grabbing x,y data about our player
	float_t playerRightSide = player->getPosition()->x  + ((float_t)player->getWidth()/2.0f);
	float_t playerLeftSide = player->getPosition()->x   - ((float_t)player->getWidth()/2.0f);
	float_t playerTopSide = player->getPosition()->y    + ((float_t)player->getHeight()/2.0f);
	float_t playerBottomSide = player->getPosition()->y - ((float_t)player->getHeight()/2.0f);

	//Rectangle collision helper. We're treating the ball as a rect for all intents and purposes
	bool collision = rectanglesCollide(leftSide, topSide, rightSide, bottomSide, playerLeftSide, playerTopSide, playerRightSide, playerBottomSide); 

	if (collision) {
		//Find out if we're hitting top, bottom, left or right
		bool bTopCollision = mPosition.y > player->getPosition()->y;
		bool bLeftCollision = mPosition.x < player->getPosition()->x;

		float yCorner;
		float xCorner;
		//Figure out what corner we're closer to
		if (bTopCollision) {
			yCorner = playerTopSide;
		} else {
			yCorner = playerBottomSide;
		}

		if (bLeftCollision) {
			xCorner = playerLeftSide;
		} else {
			xCorner = playerRightSide;
		}

		//Get the distance between our x/y and the nearest corner's x/y
		float xDist = fabs(mPosition.x - xCorner);
		float yDist = fabs(mPosition.y - yCorner);
		//Reflect off the corner thats _least_ deep into our rectangle
		bool reflectY = xDist > yDist;
		//...However, we won't run into the left side of something if we're moving left. Remove such false positivis
		if ((bLeftCollision && mVelocity.x < 0) || (!bLeftCollision && mVelocity.x > 0)) {
			reflectY = true;
		}
		if ((bTopCollision && mVelocity.y > 0) || (!bTopCollision && mVelocity.y < 0)) {
			reflectY = false;
		}

		//If it's an up/down bounce, we bounce up or down, depending on our relative location
		if (reflectY) {
			mVelocity.y = -mVelocity.y;
			if (bTopCollision) {
				mPosition.y = topSide + mRadius;
			} else {
				mPosition.y = bottomSide - mRadius;
			if ((bLeftCollision && mVelocity.x < 0) || (!bLeftCollision && mVelocity.x > 0)) {
				reflectY = true;
			}
			if ((bTopCollision && mVelocity.y > 0) || (!bTopCollision && mVelocity.y < 0)) {
				reflectY = false;
			}
			}
		} else {
			//If it's an right/left bounce, we bounce right or left, depending on our relative location
			mVelocity.x = -mVelocity.x;
			//And update our location to outside of the collision area
			if (mPosition.x < player->getPosition()->x)
			{
				mPosition.x = leftSide - mRadius;
			} else {
				mPosition.x = rightSide + mRadius;
			}
		}
		updateVelocityBasedOnPlayerCollide(player);
		//This is a speed calculator. The more arkanoid balls bounce around, the faster they go
		mHitBlocks++;
		if (mHitBlocks >= 3) {
			mVelocityMult += 2.5f;
			mVelocityMult = min(mVelocityMult, MAX_VEL);
			mVelocityMult = max(mVelocityMult, MIN_VEL);
			mHitBlocks = 0;
		}
		//If we hit a player with the "caught" powerup, and he own's us...we're caught!
		if (player->getState() == PlayerC::CATCH_STATE && player->getId() == mPlayerOwner) {
			setCaught(player);
			return;
		}
		else
		{
			SoundManagerC::GetInstance()->playSound(SoundEnum::VAUS_REFLECT_BALL_SOUND);
		}
	}
};

//Checking if we've gone past a player
void BallC::CollideDeadZone(PlayerC* player, bool above)
{
	//Checking if we're looking if we're too high or too low
	if (above) {
		//Get the closest edge to the dead zone
		float playerDeadZoneStart = player->getPosition()->y + ((float_t)player->getHeight() / 2.0f);
		//Give the player some buffer room. The ball should be definitely dead before we cull it
		playerDeadZoneStart += 1 * player->getHeight();
		float ballDeadZoneStart = mPosition.y - mRadius;
		//If we hit, then the ball is no longer in play and the enemy gets a point
		if (ballDeadZoneStart > playerDeadZoneStart) {
			disable();
			ScoreManagerC::GetInstance()->getScore1Ptr()->incrementScore();
			return;
		}
	} else {
		float playerDeadZoneStart = player->getPosition()->y - ((float_t)player->getHeight() / 2.0f);
		playerDeadZoneStart -= 1 * player->getHeight();
		float ballDeadZoneStart = mPosition.y + mRadius;
		if (ballDeadZoneStart < playerDeadZoneStart) {
			disable();
			ScoreManagerC::GetInstance()->getScore2Ptr()->incrementScore();
			return;
		}
	}
};

//Updating direction based on the part of the player we hit
void BallC::updateVelocityBasedOnPlayerCollide(PlayerC* inPlayer) {
	//Calculating our dist from the center of the paddle
	bool left = mPosition.x < inPlayer->getPosition()->x;
	float distanceFromCenter = inPlayer->getPosition()->x - mPosition.x;
	distanceFromCenter = fabs(distanceFromCenter);
	float maxDist = inPlayer->getWidth() / 2.0f;

	//If we're in the middle 50%, we go more up than right
	if (distanceFromCenter < (maxDist * 0.5f)) {
		mVelocity.x = 1.0f / 3.0f;
		mVelocity.y = 2.0f / 3.0f;
	//If we're between 50% and 75%, we go exactly diagonal
	} else if (distanceFromCenter < (maxDist * 0.75f)) {
		mVelocity.x = 0.5f;
		mVelocity.y = 0.5f;
	//If we're past 75%, we go more right than up
	} else {
		mVelocity.x = 2.0f / 3.0f;
		mVelocity.y = 1.0f / 3.0f;
	}
	//Correct for if we need to go left instead of right
	if (left) {
		mVelocity.x = -mVelocity.x;
	}
	//Correct for if we need to go down instead of up
	if (inPlayer->getId() == 2) {
		mVelocity.y = -mVelocity.y;
	}
}


//Checking for block collision
void BallC::newCollideBlocks()
{
	BlockC** blockArray = BlockManagerC::GetInstance()->getBlocks();
	float_t rightSide = mPosition.x + mRadius;
	float_t leftSide = mPosition.x - mRadius;
	float_t topSide = mPosition.y + mRadius;
	float_t bottomSide = mPosition.y - mRadius;

	//Iterating through all possible blocks
	for (int i = 0; i < BlockManagerC::GetInstance()->getMaxBlocks(); i++) {
		BlockC* curBlock = blockArray[i];
		//If we haven't instantiated past here, there are no more blocks. Here there be junk memory
		if (curBlock == nullptr) {
			break;
		}
		//If it's not enabled, no reason to calc
		if (!curBlock->isEnabled()) {
			continue;
		}

		//Grabbing information unique to this block
		float_t blockRightSide = curBlock->getPosition()->x  + ((float_t)curBlock->getWidth()/2.0f);
		float_t blockLeftSide = curBlock->getPosition()->x   - ((float_t)curBlock->getWidth()/2.0f);
		float_t blockTopSide = curBlock->getPosition()->y    + ((float_t)curBlock->getHeight()/2.0f);
		float_t blockBottomSide = curBlock->getPosition()->y - ((float_t)curBlock->getHeight()/2.0f);

		//Treating our ball collision as a rectangle
		bool collision = rectanglesCollide(leftSide, topSide, rightSide, bottomSide, blockLeftSide, blockTopSide, blockRightSide, blockBottomSide); 

		//If we collide, we calculate where we go
		if (collision) {
			bool bTopCollision = mPosition.y > curBlock->getPosition()->y;
			bool bLeftCollision = mPosition.x < curBlock->getPosition()->x;

			//Very similar to the collision for players. Find out the nearest corner, and push the ball out in that direction
			float yCorner;
			float xCorner;
			if (bTopCollision) {
				yCorner = blockTopSide;
			} else {
				yCorner = blockBottomSide;
			}

			if (bLeftCollision) {
				xCorner = blockLeftSide;
			} else {
				xCorner = blockRightSide;
			}

			float xDist = fabs(mPosition.x - xCorner);
			float yDist = fabs(mPosition.y - yCorner);
			bool reflectY = xDist > yDist;
			if ((bLeftCollision && mVelocity.x < 0) || (!bLeftCollision && mVelocity.x > 0)) {
				reflectY = true;
			}
			if ((bTopCollision && mVelocity.y > 0) || (!bTopCollision && mVelocity.y < 0)) {
				reflectY = false;
			}

			//Making sure we reflect the correct direction
			if (reflectY) {
				mVelocity.y = -mVelocity.y;
				if (bTopCollision) {
					mPosition.y = topSide + mRadius;
				}
				else {
					mPosition.y = bottomSide - mRadius;
				}
			}
			else {
				mVelocity.x = -mVelocity.x;
				if (bLeftCollision)
				{
					mPosition.x = leftSide - mRadius;
				}
				else {
					mPosition.x = rightSide + mRadius;
				}
			}
			//We apply damage to the block, and see if we've killed it
			if (curBlock->applyDamage()) {
				//If we've killed it, it may spawn a powerup
				PowerupManagerC::GetInstance()->possiblySpawnPowerup(curBlock->getPosition()->x, curBlock->getPosition()->y, mPlayerOwner);
			}
			//Taking the collision into account for ball speed
			mHitBlocks++;
			if (mHitBlocks >= 3) {
				mVelocityMult += 2.5f;
				mVelocityMult = min(mVelocityMult, MAX_VEL);
				mVelocityMult = max(mVelocityMult, MIN_VEL);
				mHitBlocks = 0;
			}
			return;
		}
	}
};

//Rendering the sprite at the ball's location
void BallC::render()
{
	if (mEnabled) {
		mBallSprite->render(mPosition);
	}
}

//Minimizing the ball's speed
void BallC::slowdown()
{
	mVelocityMult = MIN_VEL;
}

//Splitting the ball into 3 balls for the "disrupt" powerup
void BallC::splitBall()
{
	//Angle between the new balls
	int angle = 40;

	//Math to generate a new velocity vector
	float theta = deg2rad(angle);
	float cs = cos(theta);
	float sn = sin(theta);
	float finX = (mVelocity.x * cs) - (mVelocity.y * sn);
	float finY = (mVelocity.x * sn) + (mVelocity.y * cs);

	//Adding a ball with the new velocity vector
	BallManagerC::GetInstance()->addBall(mPosition.x, mPosition.y,finX,finY, mPlayerOwner, mVelocityMult);

	//...and now in the other direction
	theta = deg2rad(-angle);
	cs = cos(theta);
	sn = sin(theta);
	finX = (mVelocity.x * cs) - (mVelocity.y * sn);
	finY = (mVelocity.x * sn) + (mVelocity.y * cs);
	BallManagerC::GetInstance()->addBall(mPosition.x, mPosition.y,finX,finY, mPlayerOwner, mVelocityMult);
}

//Releasing the ball from any catch/start state it may be in
void BallC::release()
{
	mCaughtBy = nullptr;
	mCaught = false;
	mCaughtOffset = 0.0f;
	SoundManagerC::GetInstance()->playSound(SoundEnum::VAUS_REFLECT_BALL_SOUND);
}

//Setting status to "owned" by the incoming player
void BallC::setCaught(PlayerC* caughtBy) {
	mCaughtBy = caughtBy;
	mCaught = true;
	//Figuring out where on the player's x coord we are
	mCaughtOffset = caughtBy->getPosition()->x - mPosition.x;
	//Have to check if we're on the right or left side
	if (fabs(mCaughtOffset) > (caughtBy->getWidth() / 2.0f)) {
		int mult = 1;
		if (mCaughtOffset < 0) {
			mult = -1;
		}
		mCaughtOffset = caughtBy->getWidth() / 2.0f;
		mCaughtOffset *= mult;
	}
	//Have to check if we're on the top or bottom of the paddle
	if (caughtBy->getId() == 1) {
		mPosition.y = caughtBy->getPosition()->y + (caughtBy->getHeight() / 2.0f) + (mRadius);
	} else {
		mPosition.y = caughtBy->getPosition()->y - (caughtBy->getHeight() / 2.0f) - (mRadius);
	}

	SoundManagerC::GetInstance()->playSound(SoundEnum::VAUS_CATCH_SOUND);
}
