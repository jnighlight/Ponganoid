#pragma once

#include "SpriteSheet.h"

class PowerupC : public ObjectC
{
public:
	enum PowerupType {
		SPEED_DOWN = 0,
		CATCH,
		EXPAND,
		DISRUPTION,
		LASER
	};
    PowerupC(int id, float width, float height, float startX, float startY, bool moveDown, bool forceDisrupt = false);
    ~PowerupC();
	void setPowerupColor(long color) {mPowerupColor = color;};
    long getPowerupColor() {return mPowerupColor;};
    void update(DWORD milliseconds);
    virtual void render();
	void DoCollisions();
    void disable() {mEnabled = false;};
    void enable() {mEnabled = true;};
	bool getEnabled() { return mEnabled; };
	float getWidth() { return mWidth; };
	float getHeight() { return mHeight; };
	PowerupType getType() { return mPowerupType; }
private:
	void CollideField();

	long mPowerupColor;
    bool mEnabled;
    float mWidth;
    float mHeight;
	SpriteSheetC *mSpriteSheet;
	PowerupType mPowerupType;
};
