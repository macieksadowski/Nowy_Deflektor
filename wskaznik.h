#pragma once
#include <SFML/Graphics.hpp>
class wskaznik :
	public sf::Drawable, public sf::Transformable
{
	float window_x;
	float window_y;
	float _procent;
	sf::Texture Tobwoluty;
	sf::Sprite obwoluta;
public:
	wskaznik(float procent, sf::RenderWindow &av_Window);
	int stan();
	void aktualizuj(float procent);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray wierzcholki;

};

