#pragma once
#include "laser.h"
#define LASERS_AVAIL 6
class LaserManagerC
{
public:
	static LaserManagerC	*CreateInstance();
	static LaserManagerC	*GetInstance() {return sInstance;};
	~LaserManagerC(){};

	int32_t	getNumLasers() {return NUM_LASERS;};
	void	init();
	void	reset();
	void	updateLasers(DWORD milliseconds);
	void	renderLasers();
	void addLaser(float_t initPosX, float_t initPosY, int playerWhoCreated);
private:
	LaserC player1Lasers[LASERS_AVAIL];
	LaserC player2Lasers[LASERS_AVAIL];
	static LaserManagerC *sInstance;
	static const int32_t NUM_LASERS = 500;
	LaserManagerC(){};
	int lastLaser;
};
