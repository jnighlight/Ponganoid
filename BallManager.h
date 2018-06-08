#pragma once
#define BALL_RADIUS 0.25f
class BallManagerC
{
public:
	static BallManagerC	*CreateInstance();
	static BallManagerC	*GetInstance() {return sInstance;};
	~BallManagerC(){};

	int32_t	getNumBalls() {return NUM_BALLS;};
	void	init();
	void	shutdown();
	void	updateBalls(DWORD milliseconds);
	BallC *	getBallPtr(int32_t index);
	void	renderBalls();
	void slowdownBalls();
	void multiplyBalls(int id);
	void addBall(float_t initPosX, float_t initPosY, float_t velX, float_t velY, int ownedBy, float velMult);
	void resetBalls();
	void givePlayersBalls();
private:
	BallC **ballPtrs;
	static BallManagerC *sInstance;
	static const int32_t NUM_BALLS = 100;
	BallManagerC(){};
	int lastBall;
};