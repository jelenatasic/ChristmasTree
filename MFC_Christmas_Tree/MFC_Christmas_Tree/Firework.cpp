#include "stdafx.h"
#include "math.h"
#include "Firework.h"

#define DROP_FACTOR 7

Firework::Firework(int expansionRate, int startRadius, bool circleHollow, int particleCount)
{
	current_drop_factor = current_expansion_rate = 0;
	start_radius = startRadius;
	circle_hollow = circleHollow;
	no_particles = particleCount;

	if(expansionRate < 3)
		expansion_rate = 3;
	else
		expansion_rate = expansionRate;

	particles = new CPoint[no_particles];
}


void Firework::SetPositionsRandomCircular(void)
{
	//positions firework particles inside circle, radius = start_radius

	for(int i = 0; i<no_particles; i++)
	{
		//calculate position inside squre start_radius*start_radius with centar in firework_centar
		particles[i].x = rand() % (2*start_radius) + (firework_centar.x - start_radius);
		particles[i].y = rand() % (2*start_radius) + (firework_centar.y - start_radius);

		//circle equation
		//is particle positioned inside circle with radius = start_radius?
		while(!(pow((float)(particles[i].x-firework_centar.x), 2) + pow((float)(particles[i].y-firework_centar.y), 2) < pow((float)start_radius, 2)))
		{
			//if particle is not yet inside the circle, it should be moved closer to firework_centar, until it is inside the circle
			if (particles[i].x > firework_centar.x)
				particles[i].x-=2;
			else
				particles[i].x+=2;

			if (particles[i].y > firework_centar.y)
				particles[i].y-=2;
			else
				particles[i].y+=2;
		}
	}
}

void Firework::SetPositionsCircular(void)
{
	//choose positions for particles, in circular pattern, r = start_radius
	for(int i = 0; i<no_particles; i++)
	{
		float angle = 2* i * 3.141592 / no_particles;
		particles[i].x = firework_centar.x + cos(angle)*start_radius;
		particles[i].y = firework_centar.y + sin(angle)*start_radius;
	}
}

void Firework::CalculateNewPositons(void)
{
	//calculates position of particle after explosion, away from centar of firework
	for(int i = 0; i<no_particles; i++)
	{
		float k = 1.2;

		if(particles[i].x>firework_centar.x)
			particles[i].x += (abs(particles[i].x - firework_centar.x)) *k;
		else
			particles[i].x -= (abs(particles[i].x - firework_centar.x)) *k;

		if(particles[i].y>firework_centar.y)
			particles[i].y +=(abs(particles[i].y - firework_centar.y)) *k;
		else
			particles[i].y -=(abs(particles[i].y - firework_centar.y)) *k;
	}
}
void Firework::PrepareFirework(CPoint center, COLORREF firework_color)
{
	//setting firework_centar and firework_color
	firework_centar = center;
	this->firework_color = firework_color;
}


Firework::~Firework(void)
{
	delete particles;
}


void Firework::DrawFirework(CDC* pDC)
{
	//center isn't set, method PrepareFireWork has not been called
	if (firework_centar.x == 0 && firework_centar.y == 0)
		return;

	if(current_expansion_rate == 0)
	{
		//initial positions of particles, depending on firework shape
		if(circle_hollow)
			SetPositionsCircular();
		else
			SetPositionsRandomCircular();
		current_expansion_rate++;
	}
	else
	{
		if(current_expansion_rate < expansion_rate)
		{
			//calculates new positions for particles, away from firework_center, simulating firework explosion
			current_expansion_rate++;
			CalculateNewPositons();
		}
		else
		{
			if(current_drop_factor < DROP_FACTOR)
			{
				//after explosion, firework particles are falling towards ground
				current_drop_factor+=1;
				for(int i = 0; i<no_particles; i++)
				{
					particles[i].y += start_radius;
				}
			}
			else
				//and then firework is reset, and cycle starts again
				current_drop_factor = current_expansion_rate = 0;
		}
	}

	//new font for firework_particle represented by "
	CFont font;
	LPCTSTR fontStyle = (LPCTSTR)"Courier";
	//font_height=30 pixels, font_width=15 pixels
	font.CreateFont(30, 15, 0, FW_ULTRABOLD, 0, 0, 0, 0, 0, 0, 0, 0, 0, fontStyle);
	CFont *oldFont = pDC->SelectObject(&font);
	int old_bk_mode= pDC->SetBkMode(TRANSPARENT);
	COLORREF old_text_color = pDC->SetTextColor(firework_color);
	CString firework_particle =  (CString)"'*'";
	pDC->SetTextAlign(TA_CENTER);

	for(int i = 0; i<no_particles; i++)
	{
		pDC->TextOut(particles[i].x, particles[i].y,  firework_particle);
	}

	//selecting old font, deleting new one
	pDC->SelectObject(oldFont);
	font.DeleteObject();
	//restoring default
	pDC->SetBkMode(old_bk_mode);
	pDC->SetTextColor(old_text_color);

}

void Firework::ResetPositions(void)
{
	// when screen is resized, firework_center is changed, and new positions for particles must be calculated
	if(circle_hollow)
		SetPositionsCircular();
	else
		SetPositionsRandomCircular();
	current_drop_factor = current_expansion_rate = 0;
}
