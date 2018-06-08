#define SOUND_MANAGER_CPP

#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include "baseTypes.h"

#include "SoundManager.h"

SoundManagerC *SoundManagerC::sInstance = NULL;

SoundManagerC *SoundManagerC::CreateInstance()
{
	if (sInstance != NULL)return sInstance;
	else

		sInstance = new SoundManagerC();
	return sInstance;
}

void SoundManagerC::init()
{
	// create the main system object
	if (FMOD::System_Create(&mSystem) != FMOD_OK)
	{
		return;
	}
	// Check if the PC has a sound driver
	int driverCount = 0;
	mSystem->getNumDrivers(&driverCount);
	if (driverCount == 0)
	{
		return;
	}
	// Initialize an instance with 12 channels
	mSystem->init(12, FMOD_INIT_NORMAL, nullptr);

	// allocate space for the sound array
	mSounds = (FMOD::Sound **)malloc(SoundEnum::MAX_SOUND * sizeof(FMOD::Sound *));

	// create all sounds
	mSystem->createSound("Sounds/vausCatch.wav", FMOD_DEFAULT, NULL, &mSounds[SoundEnum::VAUS_CATCH_SOUND]);
	mSystem->createSound("Sounds/enemyDestroyed.wav", FMOD_DEFAULT, NULL, &mSounds[SoundEnum::ENEMY_DESTROYED_SOUND]);
	mSystem->createSound("Sounds/laser.wav", FMOD_DEFAULT, NULL, &mSounds[SoundEnum::LASER_SOUND]);
	mSystem->createSound("Sounds/vausExpand.wav", FMOD_DEFAULT, NULL, &mSounds[SoundEnum::VAUS_EXPAND_SOUND]);
	mSystem->createSound("Sounds/vausReflectBall.wav", FMOD_DEFAULT, NULL, &mSounds[SoundEnum::VAUS_REFLECT_BALL_SOUND]);
	mSystem->createSound("Sounds/blockDestroyed.wav", FMOD_DEFAULT, NULL, &mSounds[SoundEnum::BLOCK_DESTROYED_SOUND]);
	mSystem->createSound("Sounds/blockMetallic.wav", FMOD_DEFAULT, NULL, &mSounds[SoundEnum::BLOCK_METALLIC_SOUND]);
	mSystem->createSound("Sounds/playerExtend.wav", FMOD_DEFAULT, NULL, &mSounds[SoundEnum::PLAYER_EXTEND_SOUND]);
	mSystem->createSound("Sounds/death.wav", FMOD_DEFAULT, NULL, &mSounds[SoundEnum::DEATH_SOUND]);
}

void SoundManagerC::shutdown()
{
	// free the space taken up by the sounds
	for (int i = 1; i < SoundEnum::MAX_SOUND; ++i)
	{
		mSounds[i]->release();
	}
	free(mSounds);
}

void SoundManagerC::playSound(unsigned int soundID)
{
	if (soundID == 0 || soundID >= SoundEnum::MAX_SOUND)
	{
		return;
	}

	mSystem->playSound(mSounds[soundID], NULL, false, NULL);
}