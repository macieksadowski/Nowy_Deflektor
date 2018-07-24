#include "funkcje_pomocnicze.h"


bool czyWcisnieto(sf::Sprite &av_Sprite, sf::RenderWindow &av_Window)
{
	sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(av_Window);
	if (av_Sprite.getGlobalBounds().contains(mousePos)) return true;
	return false;
}

float odleglosc(point p1, point p2)
{
	float d;
	d = sqrtf(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	return d;
}

point przeciecie(point p1, point p2, point p3, point p4)
{
	point wynik = { 0.f,0.f };
	float t = ((p3.x - p1.x)*(p4.y - p3.y) - (p3.y - p1.y)* (p4.x - p3.x)) / ((p2.x - p1.x)*(p4.y - p3.y) - (p2.y - p1.y)*(p4.x - p3.x));
	wynik.x = p1.x + t * (p2.x - p1.x);
	wynik.y = p1.y + t * (p2.y - p1.y);
	return wynik;
}

bool lezy_miedzy(point p1, point p2, point p3)
{
	if (fmin(p1.x, p2.x) <= p3.x <= fmax(p1.x, p2.x))
		return true;
	else return false;
}

float iloczyn(point p1, point p2, point p3)
{
	float wynik = ((p2.x - p1.x)*(p3.y - p1.y) - (p3.x - p1.x)*(p2.y - p1.y));
	if (wynik == -0.0) wynik = 0.0;
	return wynik;

}

bool przecinaja_sie(point p1, point p2, point p3, point p4)
{
	float S1 = iloczyn(p1, p3, p2);
	float S2 = iloczyn(p1, p4, p2);
	float S3 = iloczyn(p3, p1, p4);
	float S4 = iloczyn(p3, p2, p4);
	if (((S1 > 0.0 && S2 < 0.0) || (S1 < 0.0 && S2>0.0)) && ((S3 < 0.0 && S4 > 0.0) || (S3 > 0.0 && S4 < 0.0)))
		return true;
	else if (S1 == 0.0 && lezy_miedzy(p1, p2, p3)) return true;
	else if (S2 == 0.0 && lezy_miedzy(p1, p2, p4)) return true;
	else if (S3 == 0.0 && lezy_miedzy(p3, p4, p1)) return true;
	else if (S4 == 0.0 && lezy_miedzy(p3, p4, p2)) return true;
	else return false;
}