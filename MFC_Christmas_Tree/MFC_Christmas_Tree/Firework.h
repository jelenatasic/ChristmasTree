#pragma once
class Firework
{
private:
	CPoint firework_centar;
	CPoint* particles; //particle positions
	int no_particles;
	int start_radius, expansion_rate, current_expansion_rate, current_drop_factor;

	//defines whether firework particles are positioned in hollow circle (true), or filled circle (false)
	bool circle_hollow; 
	COLORREF firework_color;
public:
	Firework(int expansionRate, int startRadius, bool circleHollow, int particleCount);
	~Firework(void);
	void DrawFirework(CDC* pDC);
	void SetPositionsRandomCircular(void);
	void SetPositionsCircular(void);
	void PrepareFirework(CPoint center, COLORREF firework_color);
	void CalculateNewPositons(void);

	void ResetPositions(void);
};

