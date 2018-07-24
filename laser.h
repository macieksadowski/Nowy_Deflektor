#pragma once
#include<vector>
#include "SFML\Graphics.hpp"

class laser : public sf::Drawable

{
public:
	laser();
	void aktualizuj(const std::vector<sf::Vertex> &punkty_P);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	


private:
	std::vector<sf::Shape> segments;
	sf::Vertex vertices[4];
	sf::Texture texture;
	float thickness;
	sf::Color color;
};