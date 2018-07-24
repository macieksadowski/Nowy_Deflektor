#include "odbiornik.h"



odbiornik::odbiornik(sf::RenderWindow &av_Window) : element("tekstury/odbiornik.png", av_Window)
{
	_odblokowany = false;
	float cosinus = cosf(_obrot * 0.01745);
	cosinus = round(cosinus * 1000.0) / 1000.0;
	float sinus = sinf(_obrot * 0.01745);
	sinus = round(sinus * 1000.0) / 1000.0;
	x_p = _obiekty[0].getPosition().x - _obiekty[0].getGlobalBounds().width *0.1f* sinus;
	y_p = _obiekty[0].getPosition().y - _obiekty[0].getGlobalBounds().height*0.1f * cosinus;
	x_k = _obiekty[0].getPosition().x + _obiekty[0].getGlobalBounds().width *0.1f* sinus;
	y_k = _obiekty[0].getPosition().y + _obiekty[0].getGlobalBounds().height *0.1f* cosinus;
	x_p2 = _obiekty[0].getPosition().x - _obiekty[0].getGlobalBounds().width *0.1f* sinus;
	y_p2 = _obiekty[0].getPosition().y - _obiekty[0].getGlobalBounds().height*0.1f * cosinus;
	x_k2 = _obiekty[0].getPosition().x + _obiekty[0].getGlobalBounds().width *0.1f* sinus;
	y_k2 = _obiekty[0].getPosition().y + _obiekty[0].getGlobalBounds().height *0.1f* cosinus;
}

void odbiornik::aktualizuj()
{
	float cosinus = cosf(_obrot * 0.01745);
	cosinus = round(cosinus * 1000.0) / 1000.0;
	float sinus = sinf(_obrot * 0.01745);
	sinus = round(sinus * 1000.0) / 1000.0;
	x_p = _obiekty[0].getGlobalBounds().width /2.f + _obiekty[0].getPosition().x - _obiekty[0].getGlobalBounds().width *0.1f* sinus;
	y_p = _obiekty[0].getGlobalBounds().height / 2.f + _obiekty[0].getPosition().y - _obiekty[0].getGlobalBounds().height*0.1f * cosinus;
	x_k = _obiekty[0].getGlobalBounds().width / 2.f + _obiekty[0].getPosition().x + _obiekty[0].getGlobalBounds().width *0.1f* sinus;
	y_k = _obiekty[0].getGlobalBounds().height / 2.f + _obiekty[0].getPosition().y + _obiekty[0].getGlobalBounds().height *0.1f* cosinus;
	x_p2 = _obiekty[0].getGlobalBounds().width / 2.f + _obiekty[0].getPosition().x - _obiekty[0].getGlobalBounds().width *0.1f* sinus;
	y_p2 = _obiekty[0].getGlobalBounds().height / 2.f + _obiekty[0].getPosition().y - _obiekty[0].getGlobalBounds().height*0.1f * cosinus;
	x_k2 = _obiekty[0].getGlobalBounds().width / 2.f + _obiekty[0].getPosition().x + _obiekty[0].getGlobalBounds().width *0.1f* sinus;
	y_k2 = _obiekty[0].getGlobalBounds().height / 2.f + _obiekty[0].getPosition().y + _obiekty[0].getGlobalBounds().height *0.1f* cosinus;
}

void odbiornik::odblokuj()
{
	_odblokowany = true;
	
}


odbiornik::~odbiornik()
{
}
