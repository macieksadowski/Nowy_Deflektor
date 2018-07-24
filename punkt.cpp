#include "punkt.h"



punkt::punkt(sf::RenderWindow &av_Window) : element(av_Window)
{
	i = -1;
	_zdobyty = false;
	Sprite _obiekt;
	Texture _tekstura_norm;
	Texture _tekstura_zdob;
	Texture _tekstura_wybuch;
	_tekstura_wybuch.loadFromFile("tekstury/eksplozja.png");
	_tekstura_norm.loadFromFile("tekstury/punkt.png");
	_tekstura_zdob.loadFromFile("tekstury/punkt_zdobyty.png");
	_tekstury.push_back(_tekstura_norm);
	_tekstury.push_back(_tekstura_zdob);
	_tekstury.push_back(_tekstura_wybuch);
	_obiekt.setTexture(_tekstury[0]);
	_obiekty.push_back(_obiekt);
	_obiekty[0].setScale(window_x / 1024.f, window_y / 768.f);

}

void punkt::zestrzel()
{
	if(i==-1) i = 0;
}

void punkt::aktywuj()
{
	_zdobyty = true;
	_obiekty[0].setTexture(_tekstury[1]);
}

void punkt::resetuj()
{
	if (_zdobyty == true)
	{
		_zdobyty = false;
		_obiekty[0].setTexture(_tekstury[0]);
		_obiekty[0].setTextureRect(sf::IntRect(0, 0, 64, 64));
		i = -1;
	}
	
}

void punkt::aktualizuj()
{
	if (_zdobyty == false && i>-1 && i<8)
	{
		_obiekty[0].setTexture(_tekstury[2]);
		_obiekty[0].setTextureRect(sf::IntRect(i * 64, 0, 64, 64));
		i++;
	}
	if (i > 7)
	{
		_zdobyty = true;
		_obiekty[0].setTexture(_tekstury[1]);
	}
	if (_zdobyty == true)
	{
		_obiekty[0].setTexture(_tekstury[1]);
		_obiekty[0].setTextureRect(sf::IntRect(0, 0, 64, 64));
	}
}

punkt::~punkt()
{
}
