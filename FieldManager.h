#pragma once
#define FIELD_WIDTH 24 * SCALE_SIZE
#define FIELD_HEIGHT 29 * SCALE_SIZE

class FieldManagerC
{
public:
	static FieldManagerC	*CreateInstance();
	static FieldManagerC	*GetInstance() {return sInstance;};
	~FieldManagerC(){};

	FieldC* getFieldPtr();
	void init();
	void renderField();
	void shutdown();
private:
	static FieldManagerC *sInstance;
	FieldManagerC(){};
	
	FieldC *mFieldPtr;
	//SpriteSheetC mBallSprite[5];
};