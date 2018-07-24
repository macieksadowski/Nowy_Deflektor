#include "Wektor2D.h"


Wektor2D::Wektor2D(float _x, float _y) : x(_x), y(_y)
{
}

Wektor2D Wektor2D::operator+(Wektor2D const &w)
{
	return Wektor2D(x+w.x,y+w.y);
}

Wektor2D Wektor2D::operator-(Wektor2D const &w)
{
	return Wektor2D(x-w.x,y-w.y);
}

float Wektor2D::operator*(Wektor2D const &w)
{
	return (x*w.x+y*w.y);
}

Wektor2D Wektor2D::operator*(float liczba)
{
	return Wektor2D(x*liczba,y*liczba);
}

Wektor2D operator*(float s, Wektor2D const &w)
{
	return Wektor2D(s*w.x, s*w.y);
}

float Wektor2D::modul()
{
	return sqrtf((*this)*(*this));
}

void Wektor2D::normuj()
{
	float d = modul();
	if (d) {
		(*this) = (*this) * (1.f / d);
	}
}

Wektor2D::~Wektor2D()
{
}
