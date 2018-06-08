#pragma once
#include "SpriteSheet.h"
#include "texturemapmanager.h"
#define SILVER_HEALTH 3

class BlockC : public ObjectC
{
public:
	enum Color {

	};
    BlockC(int id, float width, float height, float startX, float startY, TextureMapEnum textMapEnum);
    ~BlockC();
	void setType(TextureMapEnum textMapEnum);
	void setBlockColor(long color) {mBlockColor = color;};
    long getBlockColor() {return mBlockColor;};
    void update(DWORD milliseconds);
    virtual void render();
    void disable();
    void enable() {mEnabled = true;};
	float getWidth() { return mWidth; };
	float getHeight() { return mHeight; };
	bool isEnabled();
	void setRandomColor();
	bool applyDamage();
	bool getInvincible() { return invincible; }
private:
	long mBlockColor;
    bool mEnabled;
    float mWidth;
    float mHeight;
	bool mHealth;
	int curHealth;
	bool invincible;
	SpriteSheetC mBlockSprite;
};
