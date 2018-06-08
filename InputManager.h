#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#define VK_A 0x41
#define VK_W 0x57
#define VK_S 0x53
#define VK_D 0x44

class InputManagerC
{
public:
	static InputManagerC	*CreateInstance();
	static InputManagerC	*GetInstance() {return sInstance;};
	void					init(){};
	void					update();
//checkout gameframework.cpp
	Coord2D*					getCurrentMousePosition(){};
	//keyboard interface?
	bool isMovingLeft(int player);
	bool isMovingRight(int player);
	bool isPressingActive(int player);
	bool isPressingEnter();
	bool isPressingBackspace();
	//bool isPressingUp(int player);

private:
	InputManagerC(){};

	static InputManagerC *sInstance;
	bool movingRight[2];
	bool movingLeft[2];
	bool active[2];
	bool enter;
	bool backspace;
};
#endif