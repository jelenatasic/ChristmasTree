#include "stdafx.h"
#include "ChristmasTree.h"


#define FONT_HEIGHT 10
#define FONT_WIDTH 10
#define NO_COLOR_OF_LIGHT 3
//currently timer for redrawing is set to go off every 1/8 s, ==> 8fps
//so light color will change twice a seccond
#define MAX_FRAME_COUNTER 10

ChristmasTree::ChristmasTree(void)
{
	no_frames_drawn = light_counter = 0;
	light_offset = rand() % NO_COLOR_OF_LIGHT; 
	old_graphics_mode = GM_COMPATIBLE; //default mode
	pDC = NULL;
}

ChristmasTree::~ChristmasTree(void)
{
	delete pDC;
}

void ChristmasTree::SetDC(CDC* pDC)
{
	this->pDC = pDC;
}

void ChristmasTree::DrawChristmasTree(int client_rect_width, int client_rect_height)
{
	if(pDC == NULL)
		return;

	PrepareForTransform();
	//position of lower part of the tree
	Translate(client_rect_width*0.5, client_rect_height*0.9);

	//creating and selecting new font that is used for drawing the tree
	CFont font;
	LPCTSTR fontStyle = (LPCTSTR)"Courier";
	font.CreateFont(FONT_HEIGHT, FONT_WIDTH, 0, 0, FW_HEAVY, 0, 0, 0, 0, 0, 0, 0, 0, fontStyle);
	CFont *oldFont = pDC->SelectObject(&font);
	//saving old values
	int old_bk_mode = pDC->SetBkMode(TRANSPARENT);
	COLORREF old_text_color = pDC->GetTextColor();

	//6 levels of branches
	for(int i = 0; i<7; i++)
	{
		//draws a part of wood below current level of branches
		DrawWood(60.0, 7-i);
		//anlge between wood and current level of branches
		float angle = -20.0-i*10.0;
		Rotate(angle);
		//branch level will determine branch_factor
		//lower level branh will contain more subbranches
		int no_branches = 2;
		if(i>=3)
			no_branches = 1;
		//higher level branches are shorter
		DrawBranches(15-i, no_branches);
		//draws new branch symmetrically relative to wood
		Rotate(180.0-2*angle);
		DrawBranches(15-i, no_branches);
		Rotate(-(180.0-angle));
		//offset for next level of branches
		//as levels get higher, they become closer
		Translate(0, -60-i);
	}
	
	//reset light_counter
	light_counter=0;
	//1 christmas tree is drawn per frame
	no_frames_drawn++;
	
	//time to differently assign light colors
	//for this purpose offset is used 
	if(no_frames_drawn==MAX_FRAME_COUNTER)
	{
		no_frames_drawn=0;
		light_offset = (light_offset + 1) % NO_COLOR_OF_LIGHT; 
	}

	//restoring defaults and deleting used font
	pDC->SelectObject(oldFont);
	pDC->SetTextColor(old_text_color);
	font.DeleteObject();
	RestoreTransform();
}

float ChristmasTree::DrawBranch(int length)
{	
	//green color for bristles
	pDC->SetTextColor(RGB(65, 120, 65));
	CString string_1("");
	CString string_2("");
	CString string_3("O");

	//strings containing bristles
	for(int i=0; i<length; i++)
	{
		string_1+="\\\\\\";
		string_2+="///";
	}

	pDC->SetTextAlign(TA_TOP);
	pDC->TextOut(0, 0,  string_1);

	//txt_metric contains font parameters
	TEXTMETRIC txt_metric;
	GetTextMetrics(pDC->m_hDC, &txt_metric);
	pDC->SetTextAlign(TA_BOTTOM);
	//text should have y-offset so that there is no space between '/' and '\' char 
	pDC->TextOut(0, txt_metric.tmExternalLeading + txt_metric.tmInternalLeading + txt_metric.tmDescent,  string_2);


	pDC->SetTextAlign(TA_LEFT);
	
	//choosing light color
	//light_counter is increased every time a light is drawn
	//so the next time different color of light will be selected
	int x = (light_offset + light_counter) % 3; 
	switch(x){
	case 0:
		pDC->SetTextColor(RGB(220, 0, 0)); //red
		break;
	case 1:
		pDC->SetTextColor(RGB(0, 128, 255)); //blue
		break;
	case 2:
		pDC->SetTextColor(RGB(255,215,0)); //yellow
		break;
	}
	light_counter++;

	int branch_length = pDC->GetTextExtent(string_2).cx;
	//draw light on the end of branch
	pDC->TextOut(branch_length, -txt_metric.tmDescent, string_3);

	return branch_length;
}


void ChristmasTree::DrawBranches(int length, int branch_factor)
{
	//draws a branch
	float branch_length = DrawBranch(length);
	//branch_factor defines recursion depth
	if (branch_factor>0)
	{
		for (int i= 0; i<branch_factor; i++)
		{
			//saves current world transform on stack
			//this is needed becouse of recursion
			XFORM trans;
			GetWorldTransform(pDC->m_hDC, &trans);
			PushWorldTransform(trans);

			//x determines offset from root of parent branch, the starting point for new branch  
			int x=branch_length*0.2 +i*branch_length*0.7/branch_factor;
			Translate(x, 0);
			//angle between new branch and parent branch
			Rotate(-20.0);
			//recursion, drawing smaller branches, until branch factor becomes 0
			DrawBranches((int)length/1.8, branch_factor-1);
			//double the angle in opposite direction for second branch
			Rotate(40.0);
			DrawBranches((int)length/1.8, branch_factor-1);
			//restoring transform from top of stack
			PopAndLoadWorldTransform();
		}
	}
}

void ChristmasTree::DrawWood(float height, int length)
{
	//brown color for wood
	pDC->SetTextColor(RGB(150,100,80));
	CString wood_string = (CString)"  ";

	for(int i=0; i<length; i++)
		wood_string+="|";

	pDC->SetTextAlign(TA_CENTER);
	for(int i = 0; height>0; i++)
	{
		pDC->TextOut(0, i*FONT_HEIGHT,  wood_string);
		height-= FONT_HEIGHT;
	}
}

void ChristmasTree::PrepareForTransform()
{
	//setting graphic mode to GM_ADVANCED, so that we can use world transformations
	old_graphics_mode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	//storing world transformation before any modifications
	GetWorldTransform(pDC->m_hDC, &old_transform);
}

void ChristmasTree::Rotate(float angle)
{
	XFORM xform_new;
	//values that are used to modify world transformation
	xform_new.eM11 = cos(toRad(angle));
	xform_new.eM12 = sin(toRad(angle));
	xform_new.eM21 = -sin(toRad(angle));
	xform_new.eM22 = cos(toRad(angle));
	xform_new.eDx = 0;
	xform_new.eDy = 0;

	//modification of world transform relative to loacal coordinate system
	ModifyWorldTransform(pDC->m_hDC, &xform_new, MWT_LEFTMULTIPLY);
}

void ChristmasTree::Translate(int x, int y)
{
	XFORM xform_new;

	xform_new.eM11 = 1;
	xform_new.eM12 = 0;
	xform_new.eM21 = 0;
	xform_new.eM22 = 1;
	xform_new.eDx = x;
	xform_new.eDy = y;

	ModifyWorldTransform(pDC->m_hDC, &xform_new, MWT_LEFTMULTIPLY);
}

void ChristmasTree::RestoreTransform()
{
	//restoring old world transformation before any modifications
	SetWorldTransform(pDC->m_hDC, &old_transform);
	//restoring graphic mode
	SetGraphicsMode(pDC->m_hDC, old_graphics_mode);
}

float ChristmasTree::toRad(float angle)
{
	return angle*3.141592/180;	
}

void ChristmasTree::PushWorldTransform(XFORM world_transform)
{
	//storing current world transformation on stack
	transform_stack.push(world_transform);
}

void ChristmasTree::PopAndLoadWorldTransform()
{
	//loading world transformation from top of the stack as current world transformation
	//in case stack is empty, world transformation before any transformations is set as current
	if(transform_stack.empty())
		SetWorldTransform(pDC->m_hDC, &old_transform);
	else
	{
		SetWorldTransform(pDC->m_hDC, &transform_stack.top());
		transform_stack.pop();
	}
}
