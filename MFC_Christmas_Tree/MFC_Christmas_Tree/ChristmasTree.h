#pragma once
#include <stack>

class ChristmasTree
{
//Atributs
private:
	int light_counter, light_offset, no_frames_drawn;
	int old_graphics_mode;
	XFORM old_transform;
	std::stack<XFORM> transform_stack;
	CDC* pDC;

//Methods
public:
	ChristmasTree(void);
	void SetDC(CDC* pDc);
	void DrawChristmasTree(int client_rect_width, int client_rect_height);
	~ChristmasTree(void);

private:
	void DrawBranches(int length, int branch_factor);
	float DrawBranch(int length);
	void DrawWood(float height, int length);
	//Methods for world_transformation
	float toRad(float angle);
	void PushWorldTransform(XFORM world_transform);
	void PopAndLoadWorldTransform();
	void PrepareForTransform();
	void RestoreTransform();
	void Rotate(float angle);
	void Translate(int x, int y);
};

