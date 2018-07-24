#pragma once
#include "element.h"
class odbiornik :
	public element
{
public:
	
	odbiornik(sf::RenderWindow &av_Window);
	void aktualizuj();
	void odblokuj();
	~odbiornik();
};

