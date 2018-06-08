#pragma once
#define SCORE_WIDTH 4 * SCALE_SIZE
#define SCORE_HEIGHT 1 * SCALE_SIZE
#define POINTS_BETWEEN_LEVELS 10
#define LEVEL_COUNT 3
class ScoreManagerC
{
public:
	enum GameOverState {
		NOT_OVER,
		NEXT_LEVEL,
		RED_WON,
		BLUE_WON
	};
	static ScoreManagerC	*CreateInstance();
	static ScoreManagerC	*GetInstance() {return sInstance;};
	~ScoreManagerC(){};

	ScoreC* getScore1Ptr();
	ScoreC* getScore2Ptr();
	ScoreC* getScorePtr(int player);
	void init();
	void reset(bool ignoreLevel = false);
	void renderScore();
	void shutdown();
	GameOverState updateScores(DWORD milliseconds);
	void setGameOver(GameOverState state) { mGameOver = state; }
	void incrementLevel();
	int getCurrentLevel() { return curLevel; }
	bool isRedHigher();
private:
	static ScoreManagerC *sInstance;
	ScoreManagerC(){};
	
	GameOverState mGameOver;
	ScoreC *mScore1Ptr;
	ScoreC *mScore2Ptr;
	int curLevel;
};
