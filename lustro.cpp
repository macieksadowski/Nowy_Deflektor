#include "lustro.h"


lustro::lustro(sf::RenderWindow &av_Window) : element(av_Window)
{
	window_x = sf::VideoMode::getDesktopMode().width*0.53;
	window_y = 0.75 * window_x;
	Sprite _ruchomy;
	Sprite _obiekt;
	Texture _tekstura_tla;
	Texture _tekstura_lustra;
	Texture _tekstura_aktywnego;
	_tekstura_tla.loadFromFile("tekstury/lustro_0.png");
	
	_tekstura_lustra.loadFromFile("tekstury/lustro_1.png");
	_tekstura_aktywnego.loadFromFile("tekstury/lustro_2.png");
	_tekstury.push_back(_tekstura_tla);
	_tekstury.push_back(_tekstura_lustra);
	_tekstury.push_back(_tekstura_aktywnego);
	_obiekt.setTexture(_tekstury[0]);
	_obiekt.setScale(window_x / 1024.0, window_y / 768.0);
	_ruchomy.setTexture(_tekstury[1]);
	_ruchomy.setScale(window_x / 1024.0, window_y / 768.0);
	_obiekty.push_back(_obiekt);
	_obiekty.push_back(_ruchomy);
	_obiekty[0].setPosition(_polozenie);
	_obiekty[1].move(32.f*window_x / 1024.f, 32.f*window_x / 1024.f);
	_obiekty[1].setOrigin(_obiekty[1].getLocalBounds().width / 2.f, _obiekty[1].getLocalBounds().height / 2.f);
	_obrot = 0.f;
	float cosinus = cosf(_obrot * 0.01745);
	cosinus = round(cosinus * 1000.0) / 1000.0;
	float sinus = sinf(_obrot * 0.01745);
	sinus = round(sinus * 1000.0) / 1000.0;
	x_p = _obiekty[1].getPosition().x -_obiekty[1].getGlobalBounds().width *0.5f* cosinus;
	y_p = _obiekty[1].getPosition().y -_obiekty[1].getGlobalBounds().height*0.5f * sinus;
	x_k = _obiekty[1].getPosition().x + _obiekty[1].getGlobalBounds().width *0.5f* cosinus;
	y_k = _obiekty[1].getPosition().y + _obiekty[1].getGlobalBounds().height *0.5f* sinus;
	x_p2 = _obiekty[1].getPosition().x - _obiekty[1].getGlobalBounds().width *0.5f* cosinus;
	y_p2 = _obiekty[1].getPosition().y - _obiekty[1].getGlobalBounds().height*0.5f * sinus;
	x_k2 = _obiekty[1].getPosition().x + _obiekty[1].getGlobalBounds().width *0.5f* cosinus;
	y_k2 = _obiekty[1].getPosition().y + _obiekty[1].getGlobalBounds().height *0.5f* sinus;
	_aktywny = false;
	_obrotowe = false;
}

void lustro::rysuj(sf::RenderWindow & av_Window)
{
		av_Window.draw(_obiekty[1]);
}

void lustro::aktywuj()
{
	_aktywny = true;
	_obiekty[1].setTexture(_tekstury[2]);
}

void lustro::automatyczne()
{
	_obrotowe = true;
}

void lustro::aktualizuj()
{
	if (_obrotowe)
	{
		float obrot = _obiekty[1].getRotation();
		zmien_polozenie(obrot + 1.f);
	}
}

void lustro::dezaktywuj()
{
	_aktywny = false;
	_obiekty[1].setTexture(_tekstury[1]);
}

void lustro::ustaw_na_planszy(int x, int y, sf::RenderWindow &av_Window)
{
	_polozenie_na_planszy_x = x;
	if (_polozenie_na_planszy_x > 14) _polozenie_na_planszy_x = 14;
	else if (_polozenie_na_planszy_x < 0) _polozenie_na_planszy_x = 0;
	_polozenie_na_planszy_y = y;
	if (_polozenie_na_planszy_y > 8) _polozenie_na_planszy_x = 8;
	else if (_polozenie_na_planszy_y < 0) _polozenie_na_planszy_y = 0;
	_polozenie.x = 32.f * window_x / 1024.f + _polozenie_na_planszy_x*64.f*window_x / 1024.f;
	_polozenie.y = 32.f * window_x / 1024.f + _polozenie_na_planszy_y*64.f*window_x / 1024.f;
	setPosition(_polozenie.x, _polozenie.y);
	float cosinus = cosf(_obrot * 0.01745);
	cosinus = round(cosinus * 1000.0) / 1000.0;
	float sinus = sinf(_obrot * 0.01745);
	sinus = round(sinus * 1000.0) / 1000.0;
	x_p = _obiekty[1].getPosition().x - _obiekty[1].getGlobalBounds().width *0.5f* cosinus;
	y_p = _obiekty[1].getPosition().y - _obiekty[1].getGlobalBounds().height*0.5f * sinus;
	x_k = _obiekty[1].getPosition().x + _obiekty[1].getGlobalBounds().width *0.5f* cosinus;
	y_k = _obiekty[1].getPosition().y + _obiekty[1].getGlobalBounds().height *0.5f* sinus;
	x_p2 = _obiekty[1].getPosition().x - _obiekty[1].getGlobalBounds().width *0.5f* cosinus;
	y_p2 = _obiekty[1].getPosition().y - _obiekty[1].getGlobalBounds().height*0.5f * sinus;
	x_k2 = _obiekty[1].getPosition().x + _obiekty[1].getGlobalBounds().width *0.5f* cosinus;
	y_k2 = _obiekty[1].getPosition().y + _obiekty[1].getGlobalBounds().height *0.5f* sinus;
}

void lustro::zmien_polozenie(float kat)
{
	_obrot = kat;
	if (_obrot == 360.0) {
		_obrot = 0.0;
	}
	_obiekty[1].setRotation(kat);
	float cosinus = cosf(_obrot * 0.01745);
	cosinus = round(cosinus * 1000.0) / 1000.0;
	float sinus = sinf(_obrot * 0.01745);
	sinus = round(sinus * 1000.0) / 1000.0;
	x_p = _obiekty[1].getPosition().x - _obiekty[1].getGlobalBounds().width *0.5f* cosinus;
	y_p = _obiekty[1].getPosition().y - _obiekty[1].getGlobalBounds().height*0.5f * sinus;
	x_k = _obiekty[1].getPosition().x + _obiekty[1].getGlobalBounds().width *0.5f* cosinus;
	y_k = _obiekty[1].getPosition().y + _obiekty[1].getGlobalBounds().height *0.5f* sinus;
	x_p2 = _obiekty[1].getPosition().x - _obiekty[1].getGlobalBounds().width *0.5f* cosinus;
	y_p2 = _obiekty[1].getPosition().y - _obiekty[1].getGlobalBounds().height*0.5f * sinus;
	x_k2 = _obiekty[1].getPosition().x + _obiekty[1].getGlobalBounds().width *0.5f* cosinus;
	y_k2 = _obiekty[1].getPosition().y + _obiekty[1].getGlobalBounds().height *0.5f* sinus;
}

lustro::~lustro()
{
}

