#include "stdafx.h"
#include "Snow.h"


Snow::Snow(int no_snowflakes)
{
	count_flakes = no_snowflakes;
	snow = new SNOWFLAKE[no_snowflakes];
}

Snow::~Snow(void)
{
	delete snow;
}

void Snow::Move(void)
{
	for(int i=0; i<count_flakes; i++)
	{
		//flake will move on screen between 0-20 pixels in x and y direction 
		snow[i].x += rand() % 20;
		snow[i].y += rand() % 20;

		//when flake goes off screen, position should be reseted
		if(snow[i].x> screen_width)
			snow[i].x = rand() % 20;
		if(snow[i].y> screen_height)
			snow[i].y = rand() % 20;
	}
}

void Snow::Initial(int cliet_rect_width, int cliet_rect_height)
{
	//setting initial positions of snowflakes
	//snowflake can be anywhere on screen initially
	screen_width = cliet_rect_width;
	screen_height = cliet_rect_height;

	for(int i=0; i<count_flakes; i++)
	{
		snow[i].x= rand() % screen_width;
		snow[i].y= rand() % screen_height;
	}
}


void Snow::Show(CDC* pDC)
{
	//new font for snowflake represented by *
	CFont font;
	LPCTSTR fontStyle = (LPCTSTR)"Courier";
	//font_height=30 pixels, font_width=15 pixels
	font.CreateFont(20, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, fontStyle);
	CFont *oldFont = pDC->SelectObject(&font);
	int old_bk_mode= pDC->SetBkMode(TRANSPARENT);
	COLORREF old_text_color = pDC->SetTextColor(RGB(230,230,230));
	CString flake =  (CString)"*";
	pDC->SetTextAlign(TA_CENTER);

	for(int i = 0; i<count_flakes; i++)
	{
		pDC->TextOut(snow[i].x, snow[i].y,  flake);
	}

	//selecting old font, deleting new one
	pDC->SelectObject(oldFont);
	font.DeleteObject();
	//restoring default
	pDC->SetBkMode(old_bk_mode);
	pDC->SetTextColor(old_text_color);
}
