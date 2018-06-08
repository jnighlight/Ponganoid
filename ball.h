#pragma once

/*
Ball.H
This file contains the logical update and collision functions for the "balls" that are batted around by
	the bats in arkanoid and pong
*/
#include "SpriteSheet.h"
#define PLAYER_DEAD_ZONE_DIST 1 * SIZE_SCALE	//Distance below the player paddle that the dead-zone begins
#define MAX_VEL 20.0f							//Ball max velocity
#define MIN_VEL 14.0f
#define RADIUS 0.5f								//Ball's default radius if it hasn't been set

class BallC : public ObjectC
{
public:
	//Ball stat differentiating between normal play and attachment to the paddle at the start of the game
	enum BallState {
		NORMAL,
		START
	};

	//Default constructor
    BallC();
	/**
	*	initPosX,initPosY:  Ball starting location
	*	initVelX,initVelY:  Ball starting velocity
	*	id:					Ball ID
	*	ownedById:			The ID of the player that owns the ball
	*	ownedBy:			The (optional) player pointer that owns the ball
	*/
	BallC(float_t initPosX, float_t initPosY, float_t initVelX, float_t initVelY,int id, int ownedById, PlayerC* ownedBy = nullptr);
    ~BallC();

	//Main update function that handles collisions and state changes. This is where most of the work is done
    void update(DWORD milliseconds);
	//OpenGL render function
    virtual void render();

	//Helper function for organizing collision functions
	void DoCollisions();

	//Functions for enabling and disabling the ball for updates and rendering
    void disable() {mEnabled = false;};
    void enable() {mEnabled = true;};
	bool isEnabled() { return mEnabled;};

	//Function for setting the radius of the ball after creation
	void setRadius(float radius) { mCollInfo.param1 = radius; mRadius = radius; mBallSprite->setSpriteSize(radius * 2, radius * 2); };

	//Function for setting the velocity of the ball after creation
	void setVelocityMult(float velMult) { mVelocityMult = velMult; };

	//Function for slowing down the ball, usually called from the "slow" powerup
	void slowdown();
	//Function for splitting the ball into 3 balls, usually called from the "disruptor" powerup
	void splitBall();

	int getPlayerOwner() { return mPlayerOwner; };

	//Function for setting the "Caught" state of the ball and binding the ball to a player, usually called by a player with the "Caught" powerup
	void setCaught(PlayerC* caughtBy);
	//Releases ball from a player with the "caught" powerup, or that is attached to a player for start
	void release();
private:
	//Calculates collision with the outer bounding walls of the play area
	void CollideField();

	//Calculates collision players. The new implies that there was an older, worse one
	void newCollidePlayer(PlayerC* player);

	//Calculates collision with blocks. The new implies that there was an older, worse one
	void newCollideBlocks();

	//Calculates collision with the ball-killing dead zone.
	void CollideDeadZone(PlayerC* player, bool above);

	//Updates the ball's directional velocity based on the x collision location with the included player
	void updateVelocityBasedOnPlayerCollide(PlayerC* player);

    bool mEnabled;			//If the ball is in play or not
    float mRadius;			//radius of the ball

	//Information for the ball if it's attached to a player
	bool mCaught;
	PlayerC* mCaughtBy;
	float mCaughtOffset;

	//Sprite to draw for the ball
	SpriteSheetC* mBallSprite;

	//Speed modifier
	float mVelocityMult;

	//Number of blocks the ball has hit for speed calculations
	int mHitBlocks;

	//Ball state for behavior changes
	BallState mBallState;

	//The player that owns this ball
	int mPlayerOwner;
};