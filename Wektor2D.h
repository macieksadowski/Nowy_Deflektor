#pragma once
#include <cmath>

class Wektor2D
{
public:
	float x, y;
	Wektor2D(float _x,float _y);
	Wektor2D operator+(Wektor2D const &w);
	Wektor2D operator-(Wektor2D const &w);
	float operator*(Wektor2D const &w);
	Wektor2D operator*(float liczba);
	Wektor2D operator%(Wektor2D const &w);
	float modul();
	void normuj();
	~Wektor2D();
};

struct point
{
	float x;
	float y;
};
