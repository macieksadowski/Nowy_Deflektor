#include "laser.h"

	laser::laser() :
		 thickness(11.f)
	{
		texture.loadFromFile("tekstury/laser.png");
		
	}

	void laser::aktualizuj(const std::vector<sf::Vertex> &punkty_P)
	{
		for (auto itr = punkty_P.begin(); itr != punkty_P.end()--; itr++)
		{
			sf::Vector2f point1 = (*itr).position;
			sf::Vector2f point2 = (*itr++).position;
			sf::Vector2f direction = point2 - point1;
			sf::Vector2f unitDirection = direction / std::sqrt(direction.x*direction.x + direction.y*direction.y);
			sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

			sf::Vector2f offset = (thickness / 2.f)*unitPerpendicular;

			vertices[0].position = point1 + offset;
			vertices[1].position = point2 + offset;
			vertices[2].position = point2 - offset;
			vertices[3].position = point1 - offset;
			//segments.push_back(sf::ConvexShape
		}
	}

	void laser::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(vertices, 4, sf::Quads);
	}
	