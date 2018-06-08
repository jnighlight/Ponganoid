#pragma once

#include "SpriteSheet.h"
#define EXTEND_LENGTH 1.5
#define PLAYER_MOVE_SPEED 15
#define LASER_STUN_TIME 0.25f

class PlayerC : public ObjectC
{
public:
	enum PlayerState {
		NORMAL_STATE,
		CATCH_STATE,
		EXPAND_STATE,
		LASER_STATE
	};

    PlayerC(int id, float width, float height, float startX, float startY);
    ~PlayerC();
    void reset();
    void update(DWORD milliseconds);
    virtual void render();
	void DoCollisions();
    void disable() {mEnabled = false;};
    void enable() {mEnabled = true;};
	float getWidth() { return mWidth; };
	float getHeight() { return mHeight; };
	float getId() { return mId; };
	PlayerState getState() { return mPlayerState; };
	void stun();
private:
	void CollideField();
	void CollidePowerup(PowerupC* powerup);
	void attemptToSpawnBullets();

    int mId;
    bool mEnabled;
    float mWidth;
    float mOriginalWidth;
    float mHeight;
	SpriteSheetC *mNormalSpriteSheet;
	SpriteSheetC *mExtendSpriteSheet;
	SpriteSheetC *mLaserSpriteSheet;
    float mOriginalHeight;
	PlayerState mPlayerState;

	float mTimeSinceLastShot;

	bool mStunned;
	float mTimeSinceStunned;

	const int millisecondsBetweenBullets = 500;
};
