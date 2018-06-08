#define BLOCK_MANAGER_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "collinfo.h"
#include "object.h"
#include "field.h"
#include "BlockManager.h"
#include "Block.h"
#include "PowerupManager.h"

BlockManagerC* BlockManagerC::sInstance=NULL;

BlockManagerC *BlockManagerC::CreateInstance()
{
	if(sInstance!=NULL)return sInstance;
	else

	sInstance = new BlockManagerC();
	return sInstance;
}

void BlockManagerC::init()
{
	printf("Hey initing the ball manager!\n");
	mBlockArray = (BlockC**)calloc(MAX_BLOCKS, sizeof(BlockC*));
	int xStart = -1250;
	int yStart = -1187;
	for(uint32_t i = 0; i < MAX_BLOCKS; ++i)
    {
		int yLoc = i / BLOCK_COLUMNS;
		yLoc *= BLOCK_HEIGHT;
		yLoc += yStart;

		int xLoc = i % BLOCK_COLUMNS;
		xLoc *= BLOCK_WIDTH;
		xLoc += xStart;

		TextureMapEnum texMap = TextureMapEnum::BLOCK_BLUE_MAP;
		if ((i % BLOCK_COLUMNS) == 2 || (i % BLOCK_COLUMNS) == 3) {
			texMap = TextureMapEnum::BLOCK_SILVER_MAP;
		}
		if ((i % BLOCK_COLUMNS) == 4) {
			texMap = TextureMapEnum::BLOCK_GOLD_MAP;
		}
		mBlockArray[i] = new BlockC(i, BLOCK_WIDTH, BLOCK_HEIGHT, xLoc, yLoc,texMap);
		mBlockArray[i]->setRandomColor();
    }
	mCurLevel = 2;
}

void BlockManagerC::loadLevel(int level) {
	int row = 0;
	int col = 0;
	int curBlock = 0;
	for (int i = 0; i < MAX_BLOCKS; i++) {
		row = i / BLOCK_COLUMNS;
		col = i % BLOCK_COLUMNS;
		if (level == 1) {
			curBlock = level1[row][col];
		} else if (level == 2) {
			curBlock = level2[row][col];
		} else if (level == 3) {
			curBlock = level3[row][col];
		}
		mBlockArray[i]->enable();
		if (curBlock == 0) {
			mBlockArray[i]->disable();
		} else if (curBlock == 1) {
			mBlockArray[i]->setType(TextureMapEnum::BLOCK_LIGHT_BLUE_MAP);
		} else if (curBlock == 2) {
			mBlockArray[i]->setType(TextureMapEnum::BLOCK_BLUE_MAP);
		} else if (curBlock == 3) {
			mBlockArray[i]->setType(TextureMapEnum::BLOCK_GREEN_MAP);
		} else if (curBlock == 4) {
			mBlockArray[i]->setType(TextureMapEnum::BLOCK_ORANGE_MAP);
		} else if (curBlock == 5) {
			mBlockArray[i]->setType(TextureMapEnum::BLOCK_PINK_MAP);
		} else if (curBlock == 6) {
			mBlockArray[i]->setType(TextureMapEnum::BLOCK_LIGHT_RED_MAP);
		} else if (curBlock == 7) {
			mBlockArray[i]->setType(TextureMapEnum::BLOCK_RED_MAP);
		} else if (curBlock == 8) {
			mBlockArray[i]->setType(TextureMapEnum::BLOCK_WHITE_MAP);
		} else if (curBlock == 9) {
			mBlockArray[i]->setType(TextureMapEnum::BLOCK_SILVER_MAP);
		} else if (curBlock == 10) {
			mBlockArray[i]->setType(TextureMapEnum::BLOCK_GOLD_MAP);
		}
	}
}

void BlockManagerC::reset(int level)
{
	for(uint32_t i = 0; i < MAX_BLOCKS; ++i)
    {
		mBlockArray[i]->enable();
    }
	loadLevel(level);
}

BlockC *BlockManagerC::getBlockPtr()
{
	return nullptr;
}

BlockC** BlockManagerC::getBlocks()
{
	return mBlockArray;
}

int BlockManagerC::getMaxBlocks() {
	return MAX_BLOCKS;
}
void BlockManagerC::renderBlock()
{
	for(uint32_t i=0;i<MAX_BLOCKS;++i)
    {
		BlockC* curBlock = mBlockArray[i];
		if (curBlock == nullptr) {
			break;
		}
		if (curBlock->isEnabled()) {
			curBlock->render();
		}
    }
}

void BlockManagerC::shutdown()
{
	for(uint32_t i=0;i<MAX_BLOCKS;++i)
    {
		if (mBlockArray[i] == nullptr) {
			break;
		}
		delete mBlockArray[i];
	}
	free(mBlockArray);
}

void BlockManagerC::updateBlocks(DWORD milliseconds)
{
	bool anyEnabled = false;
	for(uint32_t i=0;i<MAX_BLOCKS;++i)
    {
		BlockC* curBlock = mBlockArray[i];
		if (curBlock == nullptr) {
			break;
		}
		if (curBlock->isEnabled()) {
			curBlock->update(milliseconds);
			if (!curBlock->getInvincible()) {
				anyEnabled = true;
			}
		}
    }
	if (!anyEnabled) {
		PowerupManagerC::GetInstance()->setDeathMode(true);
	}
}
