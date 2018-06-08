#pragma once

class BallC;
class FieldC;
class PlayerC;
class BlockC;
class PowerupC;
class LaserC;
class ScoreC;

class ObjectC
{
    friend class BallC;
	friend class FieldC;
	friend class PlayerC;
	friend class BlockC;
	friend class PowerupC;
	friend class LaserC;
	friend class ScoreC;
public:
    ObjectC(float initPosX, float initPosY, float initVelX, float initVelY);
    ObjectC();
    ~ObjectC();
    void setPosition(Coord2D *posToSet) {mPosition.x = posToSet->x;mPosition.y = posToSet->y;};
    Coord2D *getPosition() {return &mPosition;};
    void setVelocity(Coord2D *velToSet) {mVelocity.x = velToSet->x;mVelocity.y = velToSet->y;};
    void setVelocity(float x, float y) {mVelocity.x = x;mVelocity.y = y;};
    Coord2D *getVelocity() {return &mVelocity;};
    void setCollInfo(CollInfoC *collInfoToSet) {mCollInfo = *collInfoToSet;};
    CollInfoC *getCollInfo() {return &mCollInfo;};
	int32_t getID() {return mID;};
	void setID(int32_t id) {mID = id;};
	virtual void render()=0;
private:
    Coord2D mPosition;
    Coord2D mVelocity;
    CollInfoC mCollInfo;
	int32_t mID;
};

bool rectanglesCollide(float rect1Left, float rect1Top, float rect1Right, float reft1Bottom, float rect2Left, float rect2Top, float rect2Right, float rect2Bottom);
double deg2rad(double degrees);

#define SCALE_SIZE 125

