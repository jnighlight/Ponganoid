#pragma once

#define POWERUP_WIDTH 2 * SCALE_SIZE
#define POWERUP_HEIGHT 1 * SCALE_SIZE
#define SECONDS_IN_DEATHMODE 5

class PowerupManagerC
{
public:
	static PowerupManagerC	*CreateInstance();
	static PowerupManagerC	*GetInstance() { return sInstance; };
	~PowerupManagerC() {};

	void init();
	void reset();
	void renderPowerup();
	void shutdown();
	void updatePowerups(DWORD milliseconds);
	PowerupC* getPowerup();
	PowerupC* getPowerup2();
	int getMaxPowerups();
	void setDeathMode(bool deathMode) { mDeathMode = deathMode; };
	void possiblySpawnPowerup(float x, float y, int playerDirection);
private:
	static PowerupManagerC *sInstance;
	PowerupManagerC(){};
	static const int MAX_BLOCKS = 100;

	
	//PowerupC** mPowerupArray;
	PowerupC* mPowerup;
	PowerupC* mPowerup2;

	bool mDeathMode;
	float timeSinceDrop;
};
