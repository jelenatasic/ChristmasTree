#pragma once

struct SNOWFLAKE{
	int x; //position on screen
	int y;
};

class Snow
{
//Atributes
private:
	int count_flakes;
	SNOWFLAKE* snow;  //array that keeps track of position of every snowflake
	int screen_width, screen_height;

//Operations
public:
	Snow(int no_snowflakes);
	~Snow(void);
	void Move(void);
	void Initial(int rect_width, int rect_height);
	void Show(CDC* pDC);
};

