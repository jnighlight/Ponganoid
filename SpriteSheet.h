#pragma once

class SpriteSheetC
{
public:
	SpriteSheetC();
	SpriteSheetC(GLuint textureMapID, unsigned int spriteCount,
		float spriteWidth, float spriteHeight);
	SpriteSheetC(GLuint textureMapID, unsigned int spriteCount,
		float spriteWidth, float spriteHeight, DWORD millisecondsBetweenFrames);
	~SpriteSheetC() {};

	void setSpriteSheet(GLuint textureMapID, unsigned int spriteCount,
		float spriteWidth, float spriteHeight);
	void setSpriteSheet(GLuint textureMapID, unsigned int spriteCount,
		float spriteWidth, float spriteHeight, DWORD millisecondsBetweenFrames);
	void render(Coord2D position);
	void update(DWORD milliseconds);
	void setSpriteSize(float spriteWidth, float spriteHeight);

private:
	GLuint mTextureMapID;
	unsigned int mSpriteCount;
	unsigned int mCurrentSprite;
	float mSpriteWidth;
	float mSpriteHeight;
	DWORD mMillisecondsBetweenFrames;
	DWORD mAnimationTimer;
};