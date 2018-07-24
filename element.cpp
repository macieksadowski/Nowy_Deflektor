#include "element.h"

element::element(const String & sciezka_tekstury, sf::RenderWindow &av_Window)
{
	Sprite _obiekt;
	Texture _tekstura;
	window_x = sf::VideoMode::getDesktopMode().width*0.53;
	window_y = sf::VideoMode::getDesktopMode().width*0.5625* 0.71;
	_tekstura.loadFromFile(sciezka_tekstury);
	_tekstury.push_back(_tekstura);
	_obiekt.setTexture(_tekstury[0]);
	_polozenie.x = 0.f;
	_polozenie.x = 0.f;
	_polozenie_na_planszy_x = 0;
	_polozenie_na_planszy_y = 0;
	_obrot = 0.f;
	_obiekt.setScale(window_x / 1024.0, window_y / 768.0);
	_obiekty.push_back(_obiekt);
	//ustaw_na_planszy(_polozenie_na_planszy_x, _polozenie_na_planszy_y, av_Window);
	
	//for (auto itr = _obiekty.begin(); itr != _obiekty.end(); itr++) {
	//	itr->setOrigin(_obiekty[0].getGlobalBounds().width / 2.f, _obiekty[0].getGlobalBounds().height / 2.f);
	//	itr->setPosition(_obiekty[0].getGlobalBounds().width / 2.f, _obiekty[0].getGlobalBounds().height / 2.f);
	//	itr->setRotation(_obrot);	
	//}
	

	x_p = getPosition().x;
	y_p = getPosition().y;
	x_k = getPosition().x + _obiekty[0].getGlobalBounds().width;
	y_k = getPosition().y + _obiekty[0].getGlobalBounds().height;
	x_p2 = getPosition().x + _obiekty[0].getGlobalBounds().width;
	y_p2 = getPosition().y;
	x_k2 = getPosition().x;
	y_k2 = getPosition().y + _obiekty[0].getGlobalBounds().height;
	_polozenie = _obiekty[0].getPosition();
	
	
}

element::element(sf::RenderWindow &av_Window)
{
	window_x = sf::VideoMode::getDesktopMode().width*0.53;
	window_y = sf::VideoMode::getDesktopMode().width*0.5625* 0.71;
	_polozenie.x = 0.f;
	_polozenie.y = 0.f;
	_polozenie_na_planszy_x = 0;
	_polozenie_na_planszy_y = 0;
	_obrot = 0.f;
}

void element::setPosition(float x, float y)
{
	for (auto itr = _obiekty.begin(); itr != _obiekty.end(); itr++) {
		itr->setPosition(itr->getPosition().x + x, itr->getPosition().y + y);
	}
	_polozenie.x = x;
	_polozenie.y = y;
}

void element::setPosition(const Vector2f & position)
{
	for (auto itr = _obiekty.begin(); itr != _obiekty.end(); itr++) {
		Vector2f tmp;
		tmp.x = position.x + itr->getPosition().x;
		tmp.y = position.y + itr->getPosition().y;
		itr->setPosition(tmp);
	}
	_polozenie = position;
}

void element::setRotation(float angle)
{
	for (auto itr = _obiekty.begin(); itr != _obiekty.end(); itr++) {
		itr->setRotation(angle);
	}
}

void element::setScale(float factorX, float factorY)
{
	for (auto itr = _obiekty.begin(); itr != _obiekty.end(); itr++) {
		itr->setScale(factorX, factorY);
	}
}

void element::setScale(const Vector2f & factors)
{
	for (auto itr = _obiekty.begin(); itr != _obiekty.end(); itr++) {
		itr->setScale(factors.x, factors.y);
	}
}

void element::setOrigin(float x, float y)
{
	for (auto itr = _obiekty.begin(); itr != _obiekty.end(); itr++) {
		itr->setOrigin(x, y);
	}
}

void element::setOrigin(const Vector2f & origin)
{
	for (auto itr = _obiekty.begin(); itr != _obiekty.end(); itr++) {
		Vector2f tmp;
		tmp.x = origin.x + itr->getOrigin().x;
		tmp.y = origin.y + itr->getOrigin().y;
		itr->setOrigin(tmp);
	}
}

const Vector2f & element::getPosition() const
{
	return _polozenie;
}

float element::getRotation() const
{
	return _obrot;
}

const Vector2f & element::getScale() const
{
	return _obiekty[0].getScale();
}

const Vector2f & element::getOrigin() const
{
	return _obiekty[0].getOrigin();
}

void element::move(float offsetX, float offsetY)
{
	for (auto itr = _obiekty.begin(); itr != _obiekty.end(); itr++) {
		itr->move(offsetX, offsetY);
	}
}

void element::move(const Vector2f & offset)
{
	for (auto itr = _obiekty.begin(); itr != _obiekty.end(); itr++) {
		itr->move(offset);
	}
}

void element::rotate(float angle)
{
	_obrot += angle;
	setRotation(_obrot);
}

void element::scale(float factorX, float factorY)
{
}

void element::scale(const Vector2f & factor)
{
}

void element::rysuj(sf::RenderWindow & av_Window)
{
	for (auto itr = _obiekty.begin(); itr != _obiekty.end(); itr++) {
		av_Window.draw(*itr);
	}
	
	//std::vector<sf::Vertex> punkty;
	//punkty.push_back(Vertex(Vector2f(x_p, y_p), Color::Green));
	//punkty.push_back(Vertex(Vector2f(x_k, y_k), Color::Green));
	//punkty.push_back(Vertex(Vector2f(x_p2, y_p2), Color::Green));
	//punkty.push_back(Vertex(Vector2f(x_k2, y_k2), Color::Green));
	//av_Window.draw(&punkty[0], punkty.size(), sf::LineStrip);
	
}

void element::ustaw_na_planszy(int x, int y, sf::RenderWindow &av_Window)
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
	x_p = getPosition().x;
	y_p = getPosition().y;
	x_k = getPosition().x + _obiekty[0].getGlobalBounds().width;
	y_k = getPosition().y + _obiekty[0].getGlobalBounds().height;
	x_p2 = getPosition().x + _obiekty[0].getGlobalBounds().width;
	y_p2 = getPosition().y;
	x_k2 = getPosition().x;
	y_k2 = getPosition().y + _obiekty[0].getGlobalBounds().height;
}

void element::przesun_na_planszy(int x, int y, sf::RenderWindow &av_Window)
{
	
	_polozenie_na_planszy_x += x;
	if (_polozenie_na_planszy_x > 14) x=0;
	else if (_polozenie_na_planszy_x < 0) x = 0;
	_polozenie_na_planszy_y += y;
	if (_polozenie_na_planszy_y > 8) y=0;
	else if (_polozenie_na_planszy_y < 0) y = 0;
	move(x*64.f*window_x / 1024.f,y*64*window_x / 1024.f);
	x_p = getPosition().x;
	y_p = getPosition().y;
	x_k = getPosition().x + _obiekty[0].getGlobalBounds().width;
	y_k = getPosition().y + _obiekty[0].getGlobalBounds().height;
	x_p2 = getPosition().x + _obiekty[0].getGlobalBounds().width;
	y_p2 = getPosition().y;
	x_k2 = getPosition().x;
	y_k2 = getPosition().y + _obiekty[0].getGlobalBounds().height;
}

void element::obroc_na_planszy(int obrot, sf::RenderWindow &av_Window)
{
	_obiekty[0].move(32.f*window_x / 1024.f, 32.f*window_x / 1024.f);
	_obiekty[0].setOrigin(32.f, 32.f);

	switch (obrot) {
	case 0:
		setRotation(0);
		_obrot = 0.0;
		break;
	case 1:
		setRotation(90);
		_obrot = 90.0;
		break;
	case 2:
		setRotation(180);
		_obrot = 180.0;
		break;
	case 3:
		setRotation(270);
		_obrot = 270.0;
		break;
	default:
		break;
	}
}

void element::zmien_polozenie(float kat)
{
}


void element::zestrzel()
{
}

int element::stan()
{
	return 0;
}

void element::aktywuj()
{
}

void element::resetuj()
{
}

void element::dezaktywuj()
{
}

void element::aktualizuj()
{
}

void element::automatyczne()
{
}

element::~element()
{
	
}
