#pragma once
#include "element.h"


class lustro : public element
{
	//std::vector<Texture> tekstury;  lepiej stworzyc lustro jako dwa oddzielne elementy, czy zmieniac teksture co klikniecie?
	//int aktywna_tekstura;
	bool _aktywny;
	bool _obrotowe;
public:
	
	lustro(sf::RenderWindow &av_Window);
	void rysuj(sf::RenderWindow & av_Window);
	void zmien_polozenie(float kat);
	void aktywuj();
	void automatyczne();
	void aktualizuj();
	void dezaktywuj();
	void ustaw_na_planszy(int x, int y, sf::RenderWindow & av_Window);
	~lustro();
};

