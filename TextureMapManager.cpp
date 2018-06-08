#define TEXTURE_MAP_MANAGER_CPP

#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "SOIL.h"

#include "TextureMapManager.h"

TextureMapManagerC *TextureMapManagerC::sInstance = NULL;

TextureMapManagerC *TextureMapManagerC::CreateInstance()
{
	if (sInstance != NULL)return sInstance;
	else

		sInstance = new TextureMapManagerC();
	return sInstance;
}

void TextureMapManagerC::init()
{
	// allocate space for the texture map array
	textureMaps = (GLuint *)malloc(TextureMapEnum::MAX_MAP * sizeof(GLuint));

	// load all spritesheets as OpenGL textures
	textureMaps[TextureMapEnum::BALL_MAP] = SOIL_load_OGL_texture("Sprites/ball.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::BALL_BLUE_MAP] = SOIL_load_OGL_texture("Sprites/ballBlue.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::BALL_RED_MAP] = SOIL_load_OGL_texture("Sprites/ballRed.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::BLOCK_BLUE_MAP] = SOIL_load_OGL_texture("Sprites/blockBlue.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::BLOCK_GOLD_MAP] = SOIL_load_OGL_texture("Sprites/blockGold.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::BLOCK_GREEN_MAP] = SOIL_load_OGL_texture("Sprites/blockGreen.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::BLOCK_LIGHT_BLUE_MAP] = SOIL_load_OGL_texture("Sprites/blockLightBlue.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::BLOCK_LIGHT_RED_MAP] = SOIL_load_OGL_texture("Sprites/blockLightRed.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::BLOCK_ORANGE_MAP] = SOIL_load_OGL_texture("Sprites/blockOrange.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::BLOCK_PINK_MAP] = SOIL_load_OGL_texture("Sprites/blockPink.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::BLOCK_RED_MAP] = SOIL_load_OGL_texture("Sprites/blockRed.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::BLOCK_SILVER_MAP] = SOIL_load_OGL_texture("Sprites/blockSilver.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::BLOCK_WHITE_MAP] = SOIL_load_OGL_texture("Sprites/blockWhite.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::FIELD1_MAP] = SOIL_load_OGL_texture("Sprites/field1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::FIELD2_MAP] = SOIL_load_OGL_texture("Sprites/field2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::FIELD3_MAP] = SOIL_load_OGL_texture("Sprites/field3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::FIELD4_MAP] = SOIL_load_OGL_texture("Sprites/field4.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::FIELD5_MAP] = SOIL_load_OGL_texture("Sprites/field5.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::LASER_MAP] = SOIL_load_OGL_texture("Sprites/laser.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::LASER_PAIR_MAP] = SOIL_load_OGL_texture("Sprites/laserPair.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::POWERUP_BEE_MAP] = SOIL_load_OGL_texture("Sprites/powerupBee.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::POWERUP_BREAK_MAP] = SOIL_load_OGL_texture("Sprites/powerupBreak.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::POWERUP_CATCH_MAP] = SOIL_load_OGL_texture("Sprites/powerupCatch.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::POWERUP_DISRUPT_MAP] = SOIL_load_OGL_texture("Sprites/powerupDisrupt.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::POWERUP_EXPAND_MAP] = SOIL_load_OGL_texture("Sprites/powerupExpand.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::POWERUP_LASER_MAP] = SOIL_load_OGL_texture("Sprites/powerupLaser.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::POWERUP_PLAYER_MAP] = SOIL_load_OGL_texture("Sprites/powerupPlayer.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::POWERUP_SLOW_MAP] = SOIL_load_OGL_texture("Sprites/powerupSlow.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::TEXT_0_MAP] = SOIL_load_OGL_texture("Sprites/text0.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::TEXT_1_MAP] = SOIL_load_OGL_texture("Sprites/text1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::TEXT_2_MAP] = SOIL_load_OGL_texture("Sprites/text2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::TEXT_3_MAP] = SOIL_load_OGL_texture("Sprites/text3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::TEXT_4_MAP] = SOIL_load_OGL_texture("Sprites/text4.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::TEXT_5_MAP] = SOIL_load_OGL_texture("Sprites/text5.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::TEXT_6_MAP] = SOIL_load_OGL_texture("Sprites/text6.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::TEXT_7_MAP] = SOIL_load_OGL_texture("Sprites/text7.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::TEXT_8_MAP] = SOIL_load_OGL_texture("Sprites/text8.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::TEXT_9_MAP] = SOIL_load_OGL_texture("Sprites/text9.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::TEXT_BLUE_MAP] = SOIL_load_OGL_texture("Sprites/textBlue.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::TEXT_RED_MAP] = SOIL_load_OGL_texture("Sprites/textRed.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::TEXT_SCORE_MAP] = SOIL_load_OGL_texture("Sprites/textScore.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::VAUS_DEFAULT_MAP] = SOIL_load_OGL_texture("Sprites/vausDefault.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::VAUS_DEFAULT_2_MAP] = SOIL_load_OGL_texture("Sprites/vausDefault2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::VAUS_EXPAND_MAP] = SOIL_load_OGL_texture("Sprites/vausExpand.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::VAUS_EXPAND_2_MAP] = SOIL_load_OGL_texture("Sprites/vausExpand2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::VAUS_LASER_MAP] = SOIL_load_OGL_texture("Sprites/vausLaser.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::VAUS_LASER_2_MAP] = SOIL_load_OGL_texture("Sprites/vausLaser2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::START_SCREEN] = SOIL_load_OGL_texture("Sprites/startScreen.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::END_SCREEN] = SOIL_load_OGL_texture("Sprites/endScreen.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::END_SCREEN_BLUE] = SOIL_load_OGL_texture("Sprites/endScreenBlue.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::END_SCREEN_RED] = SOIL_load_OGL_texture("Sprites/endScreenRed.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::BLUE_AHEAD] = SOIL_load_OGL_texture("Sprites/blueWinMessage.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	textureMaps[TextureMapEnum::RED_AHEAD] = SOIL_load_OGL_texture("Sprites/redWinMessage.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}

void TextureMapManagerC::shutdown()
{
	// free the memory taken by the texture map array
	free(textureMaps);
}

GLuint TextureMapManagerC::getTextureMap(unsigned int mapEnumID)
{
	// return the appropriate texture map ID
	if (mapEnumID >= TextureMapEnum::MAX_MAP)
	{
		return 0;
	}

	return textureMaps[mapEnumID];
}