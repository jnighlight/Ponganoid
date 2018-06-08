#define GAME_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <time.h>												
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "collInfo.h"
#include "object.h"
#include "ball.h"
#include "field.h"
#include "random.h"
#include "gameObjects.h"
#include "openGLStuff.h"
#include "game.h"
#include "StateManager.h"
#include "BallManager.h"
#include "FieldManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "TextureMapManager.h"
#include "SpriteDemoManager.h"
#include "PlayerManager.h"
#include "BlockManager.h"
#include "PowerupManager.h"
#include "LaserManager.h"
#include "ScoreManager.h"

// Declarations
const char8_t CGame::mGameTitle[]="Framework1";
CGame* CGame::sInstance=NULL;
SpriteSheetC mStartScreen;
SpriteSheetC mEndScreen;
SpriteSheetC mBlueWin;
SpriteSheetC mRedWin;
bool mEndScreenSoundPlayed = false;

enum GameState {
	START,
	PLAYING,
	END
};
GameState curGameState = START;

BOOL Initialize (GL_Window* window, Keys* keys)					// Any OpenGL Initialization Goes Here
{
	srand(time(NULL));
	initOpenGLDrawing(window,keys,0.0f, 0.0f, 0.0f);
	CGame::CreateInstance();
	CGame::GetInstance()->init();
	return TRUE;						
}

void CGame::init()
{
	bDeathTimer = false;
	fDeathTimer = 0;
	BallManagerC::CreateInstance();
	StateManagerC::CreateInstance();
	FieldManagerC::CreateInstance();
	InputManagerC::CreateInstance();
	SoundManagerC::CreateInstance();
	TextureMapManagerC::CreateInstance();
	SpriteDemoManagerC::CreateInstance();
	PlayerManagerC::CreateInstance();
	BlockManagerC::CreateInstance();
	PowerupManagerC::CreateInstance();
	LaserManagerC::CreateInstance();
	ScoreManagerC::CreateInstance();

	SoundManagerC::GetInstance()->init();
	TextureMapManagerC::GetInstance()->init();
	InputManagerC::GetInstance()->init();
	PlayerManagerC::GetInstance()->init();
	BallManagerC::GetInstance()->init();
	StateManagerC::GetInstance()->setState(StateManagerC::HALF_BALLS_FILLED);
	FieldManagerC::GetInstance()->init();
	BlockManagerC::GetInstance()->init();
	PowerupManagerC::GetInstance()->init();
	LaserManagerC::GetInstance()->init();
	ScoreManagerC::GetInstance()->init();
	SpriteDemoManagerC::GetInstance()->init(5,5);
	mStartScreen.setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::START_SCREEN), 2, 3000, 3000, 7000);
	mEndScreen.setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::END_SCREEN), 1, 3000, 3000);
	mBlueWin.setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::BLUE_AHEAD), 1, 1000, 1000);
	mRedWin.setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::RED_AHEAD), 1, 1000, 1000);
}
void CGame::UpdateFrame(DWORD milliseconds)			
{
	keyProcess();
	mStartScreen.update(milliseconds);
	InputManagerC::GetInstance()->update();
	if (curGameState == START) {
		if (InputManagerC::GetInstance()->isPressingEnter()) {
			curGameState = PLAYING;
			PlayerManagerC::GetInstance()->reset();
			BallManagerC::GetInstance()->resetBalls();
			LaserManagerC::GetInstance()->reset();
			PowerupManagerC::GetInstance()->reset();
			ScoreManagerC::GetInstance()->reset();
			BlockManagerC::GetInstance()->reset(1);
		}
	} else if (curGameState == END) {
		fDeathTimer += milliseconds;
		if (fDeathTimer / 1000 > DEATH_TIME) {
			bDeathTimer = false;
		}
		if (InputManagerC::GetInstance()->isPressingBackspace()) {
			curGameState = START;
			mEndScreenSoundPlayed = false;
		}
	} else {
		if (bDeathTimer) {
			fDeathTimer += milliseconds;
			if (fDeathTimer / 1000 > DEATH_TIME) {
				bDeathTimer = false;
				PlayerManagerC::GetInstance()->reset();
				BallManagerC::GetInstance()->resetBalls();
				LaserManagerC::GetInstance()->reset();
				PowerupManagerC::GetInstance()->reset();
				ScoreManagerC::GetInstance()->reset(true);
				BlockManagerC::GetInstance()->reset(ScoreManagerC::GetInstance()->getCurrentLevel());
				ScoreManagerC::GetInstance()->setGameOver(ScoreManagerC::NOT_OVER);
			}
		} else {
			PlayerManagerC::GetInstance()->updatePlayers(milliseconds);
			LaserManagerC::GetInstance()->updateLasers(milliseconds);
			BallManagerC::GetInstance()->updateBalls(milliseconds);
			PowerupManagerC::GetInstance()->updatePowerups(milliseconds);
			BlockManagerC::GetInstance()->updateBlocks(milliseconds);

			ScoreManagerC::GameOverState gameOverState = ScoreManagerC::GetInstance()->updateScores(milliseconds);
			if (gameOverState != ScoreManagerC::NOT_OVER && gameOverState != ScoreManagerC::NEXT_LEVEL) {
				if (gameOverState == ScoreManagerC::BLUE_WON) {
					mEndScreen.setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::END_SCREEN_BLUE), 1, 3000, 3000);
				} else {
					mEndScreen.setSpriteSheet(TextureMapManagerC::GetInstance()->getTextureMap(TextureMapEnum::END_SCREEN_RED), 1, 3000, 3000);
				}
				curGameState = END;
				bDeathTimer = true;
				fDeathTimer = 0;
			}
			if (gameOverState == ScoreManagerC::NEXT_LEVEL) {
				bDeathTimer = true;
				fDeathTimer = 0;
			}
		}
	}
}

void CGame::DrawScene(void)											
{
	startOpenGLDrawing();
	if (curGameState == START) {
		Coord2D bob;
		bob.x = 0;
		bob.y = 0;
		mStartScreen.render(bob);
	} else if (curGameState == END && !bDeathTimer) {
		Coord2D bob;
		bob.x = 0;
		bob.y = 0;
		mEndScreen.render(bob);

		// play a sound effect when the end screen is first shown
		if (!mEndScreenSoundPlayed)
		{
			SoundManagerC::GetInstance()->playSound(SoundEnum::PLAYER_EXTEND_SOUND);
			mEndScreenSoundPlayed = true;
		}
	} else {
		FieldManagerC::GetInstance()->renderField();
		BallManagerC::GetInstance()->renderBalls();
		LaserManagerC::GetInstance()->renderLasers();
		BlockManagerC::GetInstance()->renderBlock();
		PlayerManagerC::GetInstance()->renderPlayer();
		PowerupManagerC::GetInstance()->renderPowerup();
		ScoreManagerC::GetInstance()->renderScore();
		if (bDeathTimer) {
			Coord2D bob;
			bob.x = 0;
			bob.y = 0;
			if (ScoreManagerC::GetInstance()->isRedHigher()) {
				mRedWin.render(bob);
			} else {
				mBlueWin.render(bob);
			}
		}
	}
}


CGame *CGame::CreateInstance()
{
	sInstance = new CGame();
	return sInstance;
}
void CGame::shutdown()
{
	BallManagerC::GetInstance()->shutdown();
	StateManagerC::GetInstance()->shutdown();
	FieldManagerC::GetInstance()->shutdown();
	BlockManagerC::GetInstance()->shutdown();
	SoundManagerC::GetInstance()->shutdown();
	TextureMapManagerC::GetInstance()->shutdown();
	//SpriteDemoManagerC::GetInstance()->shutdown();
}
void CGame::DestroyGame(void)
{
	delete BallManagerC::GetInstance();	
	delete StateManagerC::GetInstance();	
	delete FieldManagerC::GetInstance();	
}