#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"

#include "SpriteSheet.h"

SpriteSheetC::SpriteSheetC()
{
	setSpriteSheet(0, 1, 0, 0, 0);
}

SpriteSheetC::SpriteSheetC(GLuint textureMapID, unsigned int spriteCount,
	float spriteWidth, float spriteHeight)
{
	setSpriteSheet(textureMapID, spriteCount, spriteWidth, spriteHeight, 0);
}

SpriteSheetC::SpriteSheetC(GLuint textureMapID, unsigned int spriteCount,
	float spriteWidth, float spriteHeight, DWORD millisecondsBetweenFrames)
{
	setSpriteSheet(textureMapID, spriteCount, spriteWidth, spriteHeight, millisecondsBetweenFrames);
}

void SpriteSheetC::setSpriteSheet(GLuint textureMapID, unsigned int spriteCount,
	float spriteWidth, float spriteHeight)
{
	setSpriteSheet(textureMapID, spriteCount, spriteWidth, spriteHeight, 0);
}

void SpriteSheetC::setSpriteSheet(GLuint textureMapID, unsigned int spriteCount,
	float spriteWidth, float spriteHeight, DWORD millisecondsBetweenFrames)
{
	mTextureMapID = textureMapID;
	mSpriteCount = max(spriteCount, 1);		// each sprite sheet must have at least one sprite
	mCurrentSprite = 0;
	mSpriteWidth = spriteWidth;
	mSpriteHeight = spriteHeight;
	mMillisecondsBetweenFrames = millisecondsBetweenFrames;
	mAnimationTimer = 0;
}

void SpriteSheetC::setSpriteSize(float spriteWidth, float spriteHeight)
{
	mSpriteWidth = spriteWidth;
	mSpriteHeight = spriteHeight;
}


void SpriteSheetC::render(Coord2D position)
{
	// calculate positional values
	GLfloat leftU = (float)mCurrentSprite / mSpriteCount;
	GLfloat rightU = (float)(mCurrentSprite + 1) / mSpriteCount;
	GLfloat halfWidth = mSpriteWidth / 2;
	GLfloat halfHeight = mSpriteHeight / 2;

	// render a quad with the proper sprite on it
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTextureMapID);
	glBegin(GL_QUADS);
	glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);

	glTexCoord2f(leftU, 0);
	glVertex3f(position.x - halfWidth, position.y - halfHeight, 0.0);

	glTexCoord2f(rightU, 0);
	glVertex3f(position.x + halfWidth, position.y - halfHeight, 0.0);

	glTexCoord2f(rightU, 1);
	glVertex3f(position.x + halfWidth, position.y + halfHeight, 0.0);

	glTexCoord2f(leftU, 1);
	glVertex3f(position.x - halfWidth, position.y + halfHeight, 0.0);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void SpriteSheetC::update(DWORD milliseconds)
{
	if (mMillisecondsBetweenFrames <= 0)
	{
		// this is the signal that the sprite should not be animated
		return;
	}

	mAnimationTimer += milliseconds;

	while (mAnimationTimer >= mMillisecondsBetweenFrames)
	{
		// advance to the next sprite
		mCurrentSprite = (mCurrentSprite + 1) % mSpriteCount;

		// subtract from the timer
		mAnimationTimer -= mMillisecondsBetweenFrames;
	}
}