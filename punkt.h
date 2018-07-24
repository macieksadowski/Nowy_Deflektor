#pragma once
#include "element.h"
class punkt :
	public element
{
	int i;
public:
	punkt(sf::RenderWindow &av_Window);
	void zestrzel();
	void aktywuj();  //zestrzeliwuje punkt
	void resetuj();
	void aktualizuj();
	~punkt();
};

