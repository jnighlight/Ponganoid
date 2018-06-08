#pragma once

enum TextureMapEnum
{
	INVALID_MAP,
	BALL_MAP,
	BALL_BLUE_MAP,
	BALL_RED_MAP,
	BLOCK_BLUE_MAP,
	BLOCK_GOLD_MAP,
	BLOCK_GREEN_MAP,
	BLOCK_LIGHT_BLUE_MAP,
	BLOCK_LIGHT_RED_MAP,
	BLOCK_ORANGE_MAP,
	BLOCK_PINK_MAP,
	BLOCK_RED_MAP,
	BLOCK_SILVER_MAP,
	BLOCK_WHITE_MAP,
	FIELD1_MAP,
	FIELD2_MAP,
	FIELD3_MAP,
	FIELD4_MAP,
	FIELD5_MAP,
	LASER_MAP,
	LASER_PAIR_MAP,
	POWERUP_BEE_MAP,
	POWERUP_BREAK_MAP,
	POWERUP_CATCH_MAP,
	POWERUP_DISRUPT_MAP,
	POWERUP_EXPAND_MAP,
	POWERUP_LASER_MAP,
	POWERUP_PLAYER_MAP,
	POWERUP_SLOW_MAP,
	TEXT_0_MAP,
	TEXT_1_MAP,
	TEXT_2_MAP,
	TEXT_3_MAP,
	TEXT_4_MAP,
	TEXT_5_MAP,
	TEXT_6_MAP,
	TEXT_7_MAP,
	TEXT_8_MAP,
	TEXT_9_MAP,
	TEXT_BLUE_MAP,
	TEXT_RED_MAP,
	TEXT_SCORE_MAP,
	VAUS_DEFAULT_MAP,
	VAUS_DEFAULT_2_MAP,
	VAUS_EXPAND_MAP,
	VAUS_EXPAND_2_MAP,
	VAUS_LASER_MAP,
	VAUS_LASER_2_MAP,
	START_SCREEN,
	END_SCREEN,
	END_SCREEN_RED,
	END_SCREEN_BLUE,
	BLUE_AHEAD,
	RED_AHEAD,
	MAX_MAP
};

class TextureMapManagerC
{
public:
	static TextureMapManagerC *CreateInstance();
	static TextureMapManagerC *GetInstance() { return sInstance; };
	~TextureMapManagerC() {};

	void init();
	void shutdown();
	GLuint getTextureMap(unsigned int mapEnumID);

private:
	static TextureMapManagerC *sInstance;
	TextureMapManagerC() {};

	GLuint *textureMaps;
};