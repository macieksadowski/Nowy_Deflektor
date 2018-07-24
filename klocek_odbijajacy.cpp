#include "klocek_odbijajacy.h"



klocek_odbijajacy::klocek_odbijajacy(sf::RenderWindow &av_Window) : element("tekstury/klocek_odbijajacy.png", av_Window)
{
	i = -1;
	Texture _tekstura_wybuch;
	_tekstura_wybuch.loadFromFile("tekstury/eksplozja.png");
	_tekstury.push_back(_tekstura_wybuch);
	_obiekty[0].setTexture(_tekstury[0]);
	
}

void klocek_odbijajacy::zestrzel()
{
	if (i == -1) i = 0;
}

void klocek_odbijajacy::resetuj()
{
	_zdobyty = false;
	_obiekty[0].setTexture(_tekstury[0]);
	//_obiekty[0].setTextureRect(sf::IntRect(0, 0, 32, 32));
}

int klocek_odbijajacy::stan()
{
	if (i > 7) return 1;
	else return 0;
}

void klocek_odbijajacy::aktualizuj()
{
	if (i>-1 && i<8)
	{
		_obiekty[0].setTexture(_tekstury[1]);
		_obiekty[0].setTextureRect(sf::IntRect(i * 64, 0, 64, 64));
		_obiekty[0].setScale(window_x / 1024.f, window_y / 768.f);
		i++;
	}
	
	//if (_zdobyty == true) _obiekty[0].setTexture(_tekstury[1]);
}

klocek_odbijajacy::~klocek_odbijajacy()
{
}
