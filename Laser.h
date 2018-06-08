#pragma once
class LaserC : public ObjectC
{
public:
    LaserC();
	LaserC(float initPosX, float initPosY, int playerWhoCreated);
    ~LaserC();
	void setLaserColor(long color) {mLaserColor = color;};
    long getLaserColor() {return mLaserColor;};
    void update(DWORD milliseconds);
    virtual void render();
	void DoCollisions();
    void disable() {mEnabled = false;};
    void enable() {mEnabled = true;};
	bool isEnabled() { return mEnabled; };
    void setRadius(float radius) {mCollInfo.param1 = radius;mRadius = radius;};
	void setPosition(float x, float y) { mPosition.x = x; mPosition.y = y; };
	void setPlayerCreator(int player) { playerCreator = player; }
	void moveUp();

private:
	void CollideField();
	void CollidePlayer(PlayerC* player);
	void CollideBlocks();

	long mLaserColor;
    bool mEnabled;
    float mRadius;
	const float bulletSpeed = 10.0f;
	int playerCreator;
};
