#pragma once

#include "SpriteSheet.h"

class ScoreC : public ObjectC
{
public:
    ScoreC(int id, float width, float height, float startX, float startY, bool blue);
    ~ScoreC();
    void reset();
    void update(DWORD milliseconds);
    virtual void render();
    void disable() {mEnabled = false;};
    void enable() {mEnabled = true;};
	float getWidth() { return mWidth; };
	float getHeight() { return mHeight; };
	float getId() { return mId; };
	float getScore() { return mScore; };
	void incrementScore();
private:

    int mId;
	int mScore;
    bool mEnabled;
    float mWidth;
    float mHeight;
	SpriteSheetC mLabelSpriteSheet;
	SpriteSheetC mColorSpriteSheet;
	SpriteSheetC mNumberSpriteSheets[10];

	float mTimeSinceLastShot;

	const int millisecondsBetweenBullets = 500;
};
