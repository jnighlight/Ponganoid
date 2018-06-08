#pragma once
#define PLAYER_WIDTH 4 * SCALE_SIZE
#define PLAYER_HEIGHT 1 * SCALE_SIZE
class PlayerManagerC
{
public:
	static PlayerManagerC	*CreateInstance();
	static PlayerManagerC	*GetInstance() {return sInstance;};
	~PlayerManagerC(){};

	PlayerC* getPlayer1Ptr();
	PlayerC* getPlayer2Ptr();
	PlayerC* getPlayerPtr(int player);
	void init();
	void reset();
	void renderPlayer();
	void shutdown();
	void updatePlayers(DWORD milliseconds);
private:
	static PlayerManagerC *sInstance;
	PlayerManagerC(){};
	
	PlayerC *mPlayer1Ptr;
	PlayerC *mPlayer2Ptr;
};
