#pragma once
#include "element.h"
class klocek_odbijajacy :
	public element
{
	int i;
public:
	klocek_odbijajacy(sf::RenderWindow &av_Window);
	void zestrzel();
	void resetuj();
	int stan();
	void aktualizuj();
	~klocek_odbijajacy();
};

