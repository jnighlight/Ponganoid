#pragma once

#include <fmod.hpp>

enum SoundEnum
{
	INVALID_SOUND,
	VAUS_CATCH_SOUND,
	ENEMY_DESTROYED_SOUND,
	LASER_SOUND,
	VAUS_EXPAND_SOUND,
	VAUS_REFLECT_BALL_SOUND,
	BLOCK_DESTROYED_SOUND,
	BLOCK_METALLIC_SOUND,
	PLAYER_EXTEND_SOUND,
	DEATH_SOUND,
	MAX_SOUND
};

class SoundManagerC
{
public:
	static SoundManagerC *CreateInstance();
	static SoundManagerC *GetInstance() { return sInstance; };
	~SoundManagerC() {};

	void init();
	void shutdown();
	void playSound(unsigned int soundID);

private:
	static SoundManagerC *sInstance;
	SoundManagerC() {};

	FMOD::System *mSystem;
	FMOD::Sound **mSounds;
};