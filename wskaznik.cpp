#include "wskaznik.h"

wskaznik::wskaznik(float procent, sf::RenderWindow &av_Window)
{
	_procent = procent;
	wierzcholki.setPrimitiveType(sf::Quads);
	wierzcholki.resize(4);
	Tobwoluty.loadFromFile("tekstury/wskaznik.png");
	obwoluta.setTexture(Tobwoluty);
	obwoluta.setPosition(getPosition().x - 12.f, getPosition().y - 12.f);

	window_x = sf::VideoMode::getDesktopMode().width*0.53;
	window_y = 0.75 * window_x;
	obwoluta.setScale(window_x / 1024.0, window_y / 768.f);
}

int wskaznik::stan()
{
	return _procent;
}


void wskaznik::aktualizuj(float procent)
{
	_procent = procent;
	float dlugosc = 200 * window_x / 1024.0 * (_procent * 0.01f);
	if (_procent < 0.f) dlugosc = 0.f;
	if (_procent > 100.f) dlugosc = 200.f;
	sf::Color kolor;
	if (_procent > 80) kolor = sf::Color::Green;
	else if (_procent > 50) kolor = sf::Color::Yellow;
	else if (_procent > 30) kolor = sf::Color(253, 106, 2);
	else kolor = sf::Color::Red;

	wierzcholki[0] = sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Color::Red);
	wierzcholki[1] = sf::Vertex(sf::Vector2f(0.f, 40.f* window_y / 768.0), sf::Color::Red);
	wierzcholki[2] = sf::Vertex(sf::Vector2f(dlugosc, 40.f* window_y / 768.0), kolor);
	wierzcholki[3] = sf::Vertex(sf::Vector2f(dlugosc, 0.f), kolor);
	obwoluta.setPosition(getPosition().x - 12.f* window_x / 1024.0,getPosition().y - 12.f* window_y / 768.0);
}

void wskaznik::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(obwoluta);
	states.transform *= getTransform(); 
	target.draw(wierzcholki, states);
	
}
