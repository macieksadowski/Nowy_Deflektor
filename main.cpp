#include "funkcje_pomocnicze.h"
#include "lustro.h"
#include "klocek_odbijajacy.h"
#include "punkt.h"
#include "emiter.h"
#include "odbiornik.h"
#include "wskaznik.h"
#include "puste_pole.h"
#include "resource.h"

std::vector<std::string> poziomy;
int predkosc_gry;
sf::Font czcionka;
std::vector<wskaznik*> wskazniki;
std::vector<sf::Sprite> przyciski;
std::vector<std::vector<element*>> plansza;
bool pauza = false;
element *emiter1;
element *odbiornik1;
std::vector<sf::Text> teksty;
sf::Sprite tlo;
sf::Texture tekstura_tla;
sf::Sprite plansza_koncowa;
sf::Texture plansza_ladowania;
sf::Texture przegrana;
sf::Texture wygrana;
sf::Texture jeszcze_raz;
sf::Texture _tekstura_wybuch;
sf::Texture tekstura_przycisku;
sf::Texture plansza_pauzy;
sf::Image icon;
float res_x = sf::VideoMode::getDesktopMode().width;
float res_y =  sf::VideoMode::getDesktopMode().height;
float prop_okna = 0.5625;
float window_x = res_x * 0.53;
float window_y = res_x*prop_okna * 0.71;
float window_r = sqrtf(window_x*window_x + window_y*window_y);

void dodawanieElementow(sf::RenderWindow & window, std::string plik_planszy)
{
	std::fstream file;
	file.open(plik_planszy, std::ios::in);
	if (file.is_open()) {
		std::string linia;
		
		while (std::getline(file, linia)) {
			std::vector<element*> wiersz;
			for (int i = 0; i < linia.size(); i++)
			{
				char znak = linia[i];
				switch (znak)
				{
				case 'L':
					wiersz.push_back(new lustro(window));
					break;
				case 'A':
					wiersz.push_back(new lustro(window));
					wiersz.back()->automatyczne();
					break;
				case 'P':
					wiersz.push_back(new punkt(window));
					break;
				case 'K':
					wiersz.push_back(new klocek_odbijajacy(window));
					break;
				//case 'B':
				//	wiersz.push_back(new bomba(window));
				//	break;
				case ' ':
					wiersz.push_back(new puste_pole(window));
					break;
				case 'E':
					wiersz.push_back(new emiter(window));
					break;
				case 'O':
					wiersz.push_back(new odbiornik(window));
					break;
					
				}
			}
			plansza.push_back(wiersz);
		}

		
	}
	file.close();
	for (int i = 0; i < plansza.size(); i++)
	{
		for (int j = 0; j < plansza[i].size(); j++)
		{
			plansza[i][j]->ustaw_na_planszy(j, i,window);
		}
	}
	bool zn = false;
	bool zn2 = false;
	for (auto itr = plansza.begin(); itr != plansza.end(); itr++)
	{
		
		for (auto itr2 = (*itr).begin(); itr2 != (*itr).end(); itr2++)
		{
			(*itr2)->setScale(window_x / 1024.0, window_y / 768.0);
			if (dynamic_cast<emiter*>(*itr2))
			{
				emiter1 = *itr2;
				zn = true;
			}
			if (dynamic_cast<odbiornik*>(*itr2))
			{
				odbiornik1 = *itr2;
				zn2 = true;
			}
			
		}
		if (zn && zn2) break;
	}
	emiter1->obroc_na_planszy(2, window);
	odbiornik1->aktualizuj();
	//plansza[2][2]->automatyczne();
}

void laduj_konfiguracje()
{
	std::fstream file;
	file.open("konfiguracja.ini", std::ios::in);
	if (file.is_open()) {
		std::string linia;
		std::getline(file, linia);
		size_t znaleziono_rownosc = linia.find('=');
		if (znaleziono_rownosc != std::string::npos)
			predkosc_gry = (std::stoi(linia.substr(znaleziono_rownosc+1)));
		while (std::getline(file, linia)) {
			poziomy.push_back(linia);
		}
	}
	file.close();

	icon.loadFromFile("tekstury/icon.png");
}

void rysuj_plansze(sf::RenderWindow & window,bool ladowanie,bool koniec_gry,bool sukces,bool & restart,std::vector<sf::Vertex> & punkty_P)
{
	window.clear(sf::Color::Green);
	window.draw(tlo);
	for (auto przycisk : przyciski) {
		window.draw(przycisk);
	}
	for (auto tekst : teksty) {
		tekst.setFont(czcionka);
		tekst.setColor(sf::Color::White);
		window.draw(tekst);
	}

	for (auto itr = plansza.begin(); itr != plansza.end(); itr++)
	{
		for (auto itr2 = (*itr).begin(); itr2 != (*itr).end(); itr2++)
		{
			if (dynamic_cast<lustro*>(*itr2))
				window.draw((*itr2)->_obiekty[0]);
			if (dynamic_cast<puste_pole*>(*itr2)) continue;
			if (dynamic_cast<emiter*>(*itr2)) continue;
			if (dynamic_cast<odbiornik*>(*itr2)) continue;
			if (dynamic_cast<klocek_odbijajacy*>(*itr2)) continue;
			else (*itr2)->rysuj(window);
		}
	}
	if (!pauza && !koniec_gry &&  !restart && !ladowanie) window.draw(&punkty_P[0], punkty_P.size(), sf::LineStrip);
	for (auto itr = plansza.begin(); itr != plansza.end(); itr++)
	{
		for (auto itr2 = (*itr).begin(); itr2 != (*itr).end(); itr2++)
		{
			//if (dynamic_cast<puste_pole*>(*itr2)) continue;
			if (dynamic_cast<klocek_odbijajacy*>(*itr2)) (*itr2)->rysuj(window);
			if (dynamic_cast<emiter*>(*itr2)) (*itr2)->rysuj(window);
			if (dynamic_cast<odbiornik*>(*itr2)) (*itr2)->rysuj(window);
			if (dynamic_cast<lustro*>(*itr2))
				window.draw((*itr2)->_obiekty[1]);
		}
	}
	
		for (auto itr = wskazniki.begin(); itr != wskazniki.end(); itr++)
		{
			window.draw(*(*itr));
		}
	plansza_koncowa.setScale(window_x / 1024.0, window_y / 768.0);
	plansza_koncowa.setPosition(200 * window_x / 1024.0, 200 * window_y / 768.0);
	if (koniec_gry)
	{
		plansza_koncowa.setTexture(przegrana);
		window.draw(plansza_koncowa);
	}
	if (ladowanie)
	{
		plansza_koncowa.setTexture(plansza_ladowania);
		window.draw(plansza_koncowa);
	}
	if (pauza)
	{
		plansza_koncowa.setTexture(plansza_pauzy);
		window.draw(plansza_koncowa);
	}
	if (sukces)
	{
		plansza_koncowa.setTexture(wygrana);
		window.draw(plansza_koncowa);
	}
	
	window.display();
	
}

void ustawienia_poczatkowe(sf::RenderWindow & window, int & max_liczba_punktow,int aktualny_poziom)
{
	tlo.setScale(window_x / 1024.0, window_y / 768.0);
	wskazniki.push_back(new wskaznik(0, window));
	wskazniki.push_back(new wskaznik(0, window));

	_tekstura_wybuch.loadFromFile("tekstury/eksplozja.png");
	czcionka.loadFromFile("tekstury/aliee13.ttf");
	
	std::vector<sf::String> napisy =
	{
		"Energia: ",
		"Punkty: ",
		"Restart",
		"Pauza"
	};
	napisy.push_back("Poziom  " + std::to_string(aktualny_poziom));
	for (auto napis : napisy)	//rysowanie napisów na ekranie
	{
		sf::Text tekst;
		tekst.setString(napis);
		tekst.setCharacterSize(30 * window_x / 1024.0);
		teksty.push_back(tekst);
	}
	
	tekstura_przycisku.loadFromFile("tekstury/przycisk.png");
	for (int i = 0; i < 5; i++) {
		przyciski.push_back(sf::Sprite(tekstura_przycisku));
		przyciski[i].setScale(window_x / 1024.0, window_y / 768.0);
	}

	wygrana.loadFromFile("tekstury/wygrana.png");
	przegrana.loadFromFile("tekstury/koniec_gry.png");
	jeszcze_raz.loadFromFile("tekstury/restart.png");
	plansza_ladowania.loadFromFile("tekstury/ladowanie.png");
	plansza_pauzy.loadFromFile("tekstury/pauza.png");
	tekstura_tla.loadFromFile("tekstury/plansza.png");
	tlo.setTexture(tekstura_tla);

	przyciski[0].setPosition(520* window_x / 1024.0, 620* window_y / 768.0);
	teksty[0].setPosition(przyciski[0].getPosition().x + 20.f* window_x / 1024.0, przyciski[0].getPosition().y + 10.f* window_y / 768.0);

	przyciski[1].setPosition(520 * window_x / 1024.0, 690 * window_y / 768.0);
	teksty[1].setPosition(przyciski[1].getPosition().x + 20.f* window_x / 1024.0, przyciski[1].getPosition().y + 10.f* window_y / 768.0);

	przyciski[2].setPosition(50 * window_x / 1024.0, 620 * window_y / 768.0);
	teksty[2].setPosition(przyciski[2].getPosition().x + 20.f* window_x / 1024.0, przyciski[2].getPosition().y + 10.f* window_y / 768.0);

	przyciski[3].setPosition(50 * window_x / 1024.0, 690 * window_y / 768.0);
	teksty[3].setPosition(przyciski[3].getPosition().x + 20.f* window_x / 1024.0, przyciski[3].getPosition().y + 10.f* window_y / 768.0);

	przyciski[4].setPosition(280 * window_x / 1024.0, 620 * window_y / 768.0);
	teksty[4].setPosition(przyciski[4].getPosition().x + 20.f* window_x / 1024.0, przyciski[4].getPosition().y + 10.f* window_y / 768.0);


	wskazniki[0]->setPosition(750 * window_x / 1024.0, 630 * window_y / 768.0);
	wskazniki[1]->setPosition(750 * window_x / 1024.0, 700 * window_y / 768.0);

}

bool aktualizuj(sf::RenderWindow & window, bool koniec_gry, bool sukces, bool & restart, std::vector<sf::Vertex> & punkty_P,int & liczba_punktow,int & max_liczba_punktow)
{
		/*zliczanie punktow*/
		liczba_punktow = 0;
		for (auto itr = plansza.begin(); itr != plansza.end(); itr++)
		{
			for (auto itr2 = (*itr).begin(); itr2 != (*itr).end(); itr2++)
			{
				if (dynamic_cast<punkt*>(*itr2))
				{
					if ((*itr2)->_zdobyty)
						liczba_punktow++;
				}
			}
		}

		/*animacje wybuchów*/
		for (auto itr = plansza.begin(); itr != plansza.end(); itr++)
		{
			for (auto itr2 = (*itr).begin(); itr2 != (*itr).end(); itr2++)
			{
				{
					(*itr2)->aktualizuj();
				}
			}
		}

		/*odbicia*/

		{
			element *aktualny_element;
			aktualny_element = emiter1;
			float cosinus = cosf(aktualny_element->_obrot * 3.14 / 180.0);
			cosinus = round(cosinus * 100.0) / 100.0;
			float sinus = sinf(aktualny_element->_obrot * 3.14 / 180.0);
			sinus = round(sinus * 100.0) / 100.0;
			Wektor2D d0(cosinus, sinus);
			point p1 = { aktualny_element->getPosition().x + aktualny_element->_obiekty[0].getGlobalBounds().width /2.f ,aktualny_element->getPosition().y + aktualny_element->_obiekty[0].getGlobalBounds().height /2.f };
			point p2 = { p1.x + d0.x * window_r, p1.y + d0.y * window_r };

			punkty_P.push_back(Vertex(Vector2f(p1.x, p1.y), Color::Red));
			bool znaleziono = false;
			bool znaleziono_klocek = false;
			int licznik = 0;

			for (auto itr = plansza.begin(); itr != plansza.end(); itr++)
			{
				for (auto itr2 = (*itr).begin(); itr2 != (*itr).end(); itr2++)
				{
					(*itr2)->dezaktywuj();
				}
			}
			while (licznik < 8)
			{


				while (1)
				{
					float d = window_r;

					// wektor d0 na osi y w górê (ujemny) - przeszukuj tylko pozycje od aktualnego elementu do 0
					if (d0.y < 0.f)
					{
						for (int i = (*aktualny_element)._polozenie_na_planszy_y; i > -1; i--)
						{
							// wektor d0 na osi x w lewo - przeszukuj tylko pozycje planszy na lewo od aktualnego obiektu
							if (d0.x < 0.f)
							{
								for (int j = (*aktualny_element)._polozenie_na_planszy_x; j > -1; j--)
								{
									//if (!sprawdzanie_przeciec(i, j, aktualny_element, p1, p2, punkty_P, d, znaleziono, znaleziono_klocek, sukces)) break;
									point l1 = { plansza[i][j]->x_p ,plansza[i][j]->y_p };
									point l2 = { plansza[i][j]->x_k ,plansza[i][j]->y_k };
									point l3 = { plansza[i][j]->x_p2 ,plansza[i][j]->y_p2 };
									point l4 = { plansza[i][j]->x_k2 ,plansza[i][j]->y_k2 };
									if (przecinaja_sie(l1, l2, p1, p2) && plansza[i][j] != aktualny_element)
									{

										if (dynamic_cast<lustro*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											point przec = przeciecie(p1, p2, l1, l2);
											punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
											plansza[i][j]->aktywuj();
											d = odleglosc(p1, l1);
											aktualny_element = plansza[i][j];
											znaleziono = true;
										}
										if (dynamic_cast<punkt*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											//wybuch(window, *plansza[i][j], _tekstura_wybuch, koniec_gry, sukces, punkty_P);
											plansza[i][j]->zestrzel();
											//punkty_P.push_back(Vertex((*itr2)->_obiekty[0].getPosition(), Color::Red));
											//znaleziono_klocek = true;
											d = odleglosc(p1, l1);
											//aktualny_element = plansza[i][j];
										}
										if (dynamic_cast<klocek_odbijajacy*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											point przec = przeciecie(p1, p2, l1, l2);
											punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
											//punkty_P.push_back(Vertex(plansza[i][j]->_obiekty[0].getPosition(), Color::Red));
											znaleziono_klocek = true;
											aktualny_element = plansza[i][j];
										}
										if (dynamic_cast<odbiornik*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											if (plansza[i][j]->_odblokowany)
											{
												point przec = przeciecie(p1, p2, l1, l2);
												punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
												sukces = true;
												znaleziono_klocek = true;
												aktualny_element = plansza[i][j];
											}	
										}
										if (znaleziono_klocek || znaleziono) break;


									}
									if (przecinaja_sie(l3, l4, p1, p2) && plansza[i][j] != aktualny_element)
									{
										if (dynamic_cast<punkt*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											//wybuch(window, *plansza[i][j], _tekstura_wybuch, koniec_gry, sukces, punkty_P);
											plansza[i][j]->zestrzel();

											//punkty_P.push_back(Vertex((*itr2)->_obiekty[0].getPosition(), Color::Red));
											//znaleziono_klocek = true;
											d = odleglosc(p1, l3);
											//aktualny_element = plansza[i][j];
										}
										if (dynamic_cast<klocek_odbijajacy*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											point przec = przeciecie(p1, p2, l3, l4);
											punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
											znaleziono_klocek = true;
											aktualny_element = plansza[i][j];
										}
										if (dynamic_cast<odbiornik*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											if (plansza[i][j]->_odblokowany)
											{
												point przec = przeciecie(p1, p2, l3, l4);
												punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
												sukces = true;
												znaleziono_klocek = true;
												aktualny_element = plansza[i][j];
											}
										}
										if (znaleziono_klocek || znaleziono) break;
									}
								}
							}
							// wspolrzedna x wektora d0 zerowa - przeszukuj tylko dla zadanej na sztywno wsp. x
							else if (d0.x == 0.f)
							{
								int j = (*aktualny_element)._polozenie_na_planszy_x;
								//if (!sprawdzanie_przeciec(i, j, aktualny_element, p1, p2, punkty_P, d, znaleziono, znaleziono_klocek, sukces)) break;

								point l1 = { plansza[i][j]->x_p ,plansza[i][j]->y_p };
								point l2 = { plansza[i][j]->x_k ,plansza[i][j]->y_k };
								point l3 = { plansza[i][j]->x_p2 ,plansza[i][j]->y_p2 };
								point l4 = { plansza[i][j]->x_k2 ,plansza[i][j]->y_k2 };
								if (przecinaja_sie(l1, l2, p1, p2) && plansza[i][j] != aktualny_element)
								{

									if (dynamic_cast<lustro*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										point przec = przeciecie(p1, p2, l1, l2);
										punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
										plansza[i][j]->aktywuj();
										d = odleglosc(p1, l1);
										aktualny_element = plansza[i][j];
										znaleziono = true;
									}
									if (dynamic_cast<punkt*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										//wybuch(window, *plansza[i][j], _tekstura_wybuch, koniec_gry, sukces, punkty_P);
										plansza[i][j]->zestrzel();
										//punkty_P.push_back(Vertex((*itr2)->_obiekty[0].getPosition(), Color::Red));
										//znaleziono_klocek = true;
										d = odleglosc(p1, l1);
										//aktualny_element = plansza[i][j];
									}
									if (dynamic_cast<klocek_odbijajacy*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										point przec = przeciecie(p1, p2, l1, l2);
										punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
										//punkty_P.push_back(Vertex(plansza[i][j]->_obiekty[0].getPosition(), Color::Red));
										znaleziono_klocek = true;
										aktualny_element = plansza[i][j];
									}
									if (dynamic_cast<odbiornik*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										if (plansza[i][j]->_odblokowany)
										{
											point przec = przeciecie(p1, p2, l1, l2);
											punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
											sukces = true;
											znaleziono_klocek = true;
											aktualny_element = plansza[i][j];
										}
									}
									if (znaleziono_klocek || znaleziono) break;


								}
								if (przecinaja_sie(l3, l4, p1, p2) && plansza[i][j] != aktualny_element)
								{
									if (dynamic_cast<punkt*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										//wybuch(window, *plansza[i][j], _tekstura_wybuch, koniec_gry, sukces, punkty_P);
										plansza[i][j]->zestrzel();

										//punkty_P.push_back(Vertex((*itr2)->_obiekty[0].getPosition(), Color::Red));
										//znaleziono_klocek = true;
										d = odleglosc(p1, l3);
										//aktualny_element = plansza[i][j];
									}
									if (dynamic_cast<klocek_odbijajacy*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										point przec = przeciecie(p1, p2, l3, l4);
										punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
										znaleziono_klocek = true;
										aktualny_element = plansza[i][j];
									}
									if (dynamic_cast<odbiornik*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										if (plansza[i][j]->_odblokowany)
										{
											point przec = przeciecie(p1, p2, l3, l4);
											punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
											sukces = true;
											znaleziono_klocek = true;
											aktualny_element = plansza[i][j];
										}
									}
									if (znaleziono_klocek || znaleziono) break;
								}
							}
							// wektor d0 na osi x w prawo - przeszukuj tylko pozycje planszy na prawo od aktualnego obiektu
							else
							{
								for (int j = (*aktualny_element)._polozenie_na_planszy_x; j < 15; j++)
								{
									//if (!sprawdzanie_przeciec(i, j, aktualny_element, p1, p2, punkty_P, d, znaleziono, znaleziono_klocek, sukces)) break;

									point l1 = { plansza[i][j]->x_p ,plansza[i][j]->y_p };
									point l2 = { plansza[i][j]->x_k ,plansza[i][j]->y_k };
									point l3 = { plansza[i][j]->x_p2 ,plansza[i][j]->y_p2 };
									point l4 = { plansza[i][j]->x_k2 ,plansza[i][j]->y_k2 };
									if (przecinaja_sie(l1, l2, p1, p2) && plansza[i][j] != aktualny_element)
									{

										if (dynamic_cast<lustro*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											point przec = przeciecie(p1, p2, l1, l2);
											punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
											plansza[i][j]->aktywuj();
											d = odleglosc(p1, l1);
											aktualny_element = plansza[i][j];
											znaleziono = true;
										}
										if (dynamic_cast<punkt*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											//wybuch(window, *plansza[i][j], _tekstura_wybuch, koniec_gry, sukces, punkty_P);
											plansza[i][j]->zestrzel();
											//punkty_P.push_back(Vertex((*itr2)->_obiekty[0].getPosition(), Color::Red));
											//znaleziono_klocek = true;
											d = odleglosc(p1, l1);
											//aktualny_element = plansza[i][j];
										}
										if (dynamic_cast<klocek_odbijajacy*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											point przec = przeciecie(p1, p2, l1, l2);
											punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
											//punkty_P.push_back(Vertex(plansza[i][j]->_obiekty[0].getPosition(), Color::Red));
											znaleziono_klocek = true;
											aktualny_element = plansza[i][j];
										}
										if (dynamic_cast<odbiornik*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											if (plansza[i][j]->_odblokowany)
											{
												point przec = przeciecie(p1, p2, l1, l2);
												punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
												sukces = true;
												znaleziono_klocek = true;
												aktualny_element = plansza[i][j];
											}
										}
										if (znaleziono_klocek || znaleziono) break;


									}
									if (przecinaja_sie(l3, l4, p1, p2) && plansza[i][j] != aktualny_element)
									{
										if (dynamic_cast<punkt*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											//wybuch(window, *plansza[i][j], _tekstura_wybuch, koniec_gry, sukces, punkty_P);
											plansza[i][j]->zestrzel();

											//punkty_P.push_back(Vertex((*itr2)->_obiekty[0].getPosition(), Color::Red));
											//znaleziono_klocek = true;
											d = odleglosc(p1, l3);
											//aktualny_element = plansza[i][j];
										}
										if (dynamic_cast<klocek_odbijajacy*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											point przec = przeciecie(p1, p2, l3, l4);
											punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
											znaleziono_klocek = true;
											aktualny_element = plansza[i][j];
										}
										if (dynamic_cast<odbiornik*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											if (plansza[i][j]->_odblokowany)
											{
												point przec = przeciecie(p1, p2, l3, l4);
												punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
												sukces = true;
												znaleziono_klocek = true;
												aktualny_element = plansza[i][j];
											}
										}
										if (znaleziono_klocek || znaleziono) break;
									}
								}
							}

							if (znaleziono_klocek || znaleziono) break;
						}

					}
					
					// wspolrzedna y wektora d0 zerowa- przeszukuj tylko lewo prawo dla zadanej na sztywno wsp. y
					else if (d0.y == 0.f)
					{
						int i = (*aktualny_element)._polozenie_na_planszy_y;
						// wektor d0 na osi x w lewo - przeszukuj tylko pozycje planszy na lewo od aktualnego obiektu
						if (d0.x < 0.f)
						{
							for (int j = (*aktualny_element)._polozenie_na_planszy_x; j > -1; j--)
							{
								//if (!sprawdzanie_przeciec(i, j, aktualny_element, p1, p2, punkty_P, d, znaleziono, znaleziono_klocek, sukces)) break;

								point l1 = { plansza[i][j]->x_p ,plansza[i][j]->y_p };
								point l2 = { plansza[i][j]->x_k ,plansza[i][j]->y_k };
								point l3 = { plansza[i][j]->x_p2 ,plansza[i][j]->y_p2 };
								point l4 = { plansza[i][j]->x_k2 ,plansza[i][j]->y_k2 };
								if (przecinaja_sie(l1, l2, p1, p2) && plansza[i][j] != aktualny_element)
								{

									if (dynamic_cast<lustro*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										point przec = przeciecie(p1, p2, l1, l2);
										punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
										plansza[i][j]->aktywuj();
										d = odleglosc(p1, l1);
										aktualny_element = plansza[i][j];
										znaleziono = true;
									}
									if (dynamic_cast<punkt*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										//wybuch(window, *plansza[i][j], _tekstura_wybuch, koniec_gry, sukces, punkty_P);
										plansza[i][j]->zestrzel();
										//punkty_P.push_back(Vertex((*itr2)->_obiekty[0].getPosition(), Color::Red));
										//znaleziono_klocek = true;
										d = odleglosc(p1, l1);
										//aktualny_element = plansza[i][j];
									}
									if (dynamic_cast<klocek_odbijajacy*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										point przec = przeciecie(p1, p2, l1, l2);
										punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
										//punkty_P.push_back(Vertex(plansza[i][j]->_obiekty[0].getPosition(), Color::Red));
										znaleziono_klocek = true;
										aktualny_element = plansza[i][j];
									}
									if (dynamic_cast<odbiornik*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										if (plansza[i][j]->_odblokowany)
										{
											point przec = przeciecie(p1, p2, l1, l2);
											punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
											sukces = true;
											znaleziono_klocek = true;
											aktualny_element = plansza[i][j];
										}
									}
									if (znaleziono_klocek || znaleziono) break;


								}
								if (przecinaja_sie(l3, l4, p1, p2) && plansza[i][j] != aktualny_element)
								{
									if (dynamic_cast<punkt*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										//wybuch(window, *plansza[i][j], _tekstura_wybuch, koniec_gry, sukces, punkty_P);
										plansza[i][j]->zestrzel();

										//punkty_P.push_back(Vertex((*itr2)->_obiekty[0].getPosition(), Color::Red));
										//znaleziono_klocek = true;
										d = odleglosc(p1, l3);
										//aktualny_element = plansza[i][j];
									}
									if (dynamic_cast<klocek_odbijajacy*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										point przec = przeciecie(p1, p2, l3, l4);
										punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
										znaleziono_klocek = true;
										aktualny_element = plansza[i][j];
									}
									if (dynamic_cast<odbiornik*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										if (plansza[i][j]->_odblokowany)
										{
											point przec = przeciecie(p1, p2, l3, l4);
											punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
											sukces = true;
											znaleziono_klocek = true;
											aktualny_element = plansza[i][j];
										}
									}
									if (znaleziono_klocek || znaleziono) break;
								}
							}
						}

						// wektor d0 na osi x w prawo - przeszukuj tylko pozycje planszy na prawo od aktualnego obiektu
						else
						{
							for (int j = (*aktualny_element)._polozenie_na_planszy_x; j < 15; j++)
							{
								//if (!sprawdzanie_przeciec(i, j, aktualny_element, p1, p2, punkty_P, d, znaleziono, znaleziono_klocek, sukces)) break;

								point l1 = { plansza[i][j]->x_p ,plansza[i][j]->y_p };
								point l2 = { plansza[i][j]->x_k ,plansza[i][j]->y_k };
								point l3 = { plansza[i][j]->x_p2 ,plansza[i][j]->y_p2 };
								point l4 = { plansza[i][j]->x_k2 ,plansza[i][j]->y_k2 };
								if (przecinaja_sie(l1, l2, p1, p2) && plansza[i][j] != aktualny_element)
								{

									if (dynamic_cast<lustro*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										point przec = przeciecie(p1, p2, l1, l2);
										punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
										plansza[i][j]->aktywuj();
										d = odleglosc(p1, l1);
										aktualny_element = plansza[i][j];
										znaleziono = true;
									}
									if (dynamic_cast<punkt*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										//wybuch(window, *plansza[i][j], _tekstura_wybuch, koniec_gry, sukces, punkty_P);
										plansza[i][j]->zestrzel();
										//punkty_P.push_back(Vertex((*itr2)->_obiekty[0].getPosition(), Color::Red));
										//znaleziono_klocek = true;
										d = odleglosc(p1, l1);
										//aktualny_element = plansza[i][j];
									}
									if (dynamic_cast<klocek_odbijajacy*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										point przec = przeciecie(p1, p2, l1, l2);
										punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
										//punkty_P.push_back(Vertex(plansza[i][j]->_obiekty[0].getPosition(), Color::Red));
										znaleziono_klocek = true;
										aktualny_element = plansza[i][j];
									}
									if (dynamic_cast<odbiornik*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										if (plansza[i][j]->_odblokowany)
										{
											point przec = przeciecie(p1, p2, l1, l2);
											punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
											sukces = true;
											znaleziono_klocek = true;
											aktualny_element = plansza[i][j];
										}
									}
									if (znaleziono_klocek || znaleziono) break;


								}
								if (przecinaja_sie(l3, l4, p1, p2) && plansza[i][j] != aktualny_element)
								{
									if (dynamic_cast<punkt*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										//wybuch(window, *plansza[i][j], _tekstura_wybuch, koniec_gry, sukces, punkty_P);
										plansza[i][j]->zestrzel();

										//punkty_P.push_back(Vertex((*itr2)->_obiekty[0].getPosition(), Color::Red));
										//znaleziono_klocek = true;
										d = odleglosc(p1, l3);
										//aktualny_element = plansza[i][j];
									}
									if (dynamic_cast<klocek_odbijajacy*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										point przec = przeciecie(p1, p2, l3, l4);
										punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
										znaleziono_klocek = true;
										aktualny_element = plansza[i][j];
									}
									if (dynamic_cast<odbiornik*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										if (plansza[i][j]->_odblokowany)
										{
											point przec = przeciecie(p1, p2, l3, l4);
											punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
											sukces = true;
											znaleziono_klocek = true;
											aktualny_element = plansza[i][j];
										}
									}
									if (znaleziono_klocek || znaleziono) break;
								}
							}
						}
						if (znaleziono_klocek || znaleziono) break;
					}
					
					// wektor d0 na osi y w dó³ (dodatni) - przeszukuj tylko pozycje od aktualnego elementu do 9
					else
					{
						for (int i = (*aktualny_element)._polozenie_na_planszy_y; i < 9; i++)
						{
							// wektor d0 na osi x w lewo - przeszukuj tylko pozycje planszy na lewo od aktualnego obiektu
							if (d0.x < 0.f)
							{
								for (int j = (*aktualny_element)._polozenie_na_planszy_x; j > -1; j--)
								{
									//if (!sprawdzanie_przeciec(i, j, aktualny_element, p1, p2, punkty_P, d, znaleziono, znaleziono_klocek, sukces)) break;

									point l1 = { plansza[i][j]->x_p ,plansza[i][j]->y_p };
									point l2 = { plansza[i][j]->x_k ,plansza[i][j]->y_k };
									point l3 = { plansza[i][j]->x_p2 ,plansza[i][j]->y_p2 };
									point l4 = { plansza[i][j]->x_k2 ,plansza[i][j]->y_k2 };
									if (przecinaja_sie(l1, l2, p1, p2) && plansza[i][j] != aktualny_element)
									{

										if (dynamic_cast<lustro*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											point przec = przeciecie(p1, p2, l1, l2);
											punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
											plansza[i][j]->aktywuj();
											d = odleglosc(p1, l1);
											aktualny_element = plansza[i][j];
											znaleziono = true;
										}
										if (dynamic_cast<punkt*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											//wybuch(window, *plansza[i][j], _tekstura_wybuch, koniec_gry, sukces, punkty_P);
											plansza[i][j]->zestrzel();
											//punkty_P.push_back(Vertex((*itr2)->_obiekty[0].getPosition(), Color::Red));
											//znaleziono_klocek = true;
											d = odleglosc(p1, l1);
											//aktualny_element = plansza[i][j];
										}
										if (dynamic_cast<klocek_odbijajacy*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											point przec = przeciecie(p1, p2, l1, l2);
											punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
											//punkty_P.push_back(Vertex(plansza[i][j]->_obiekty[0].getPosition(), Color::Red));
											znaleziono_klocek = true;
											aktualny_element = plansza[i][j];
										}
										if (dynamic_cast<odbiornik*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											if (plansza[i][j]->_odblokowany)
											{
												point przec = przeciecie(p1, p2, l1, l2);
												punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
												sukces = true;
												znaleziono_klocek = true;
												aktualny_element = plansza[i][j];
											}
										}
										if (znaleziono_klocek || znaleziono) break;


									}
									if (przecinaja_sie(l3, l4, p1, p2) && plansza[i][j] != aktualny_element)
									{
										if (dynamic_cast<punkt*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											//wybuch(window, *plansza[i][j], _tekstura_wybuch, koniec_gry, sukces, punkty_P);
											plansza[i][j]->zestrzel();

											//punkty_P.push_back(Vertex((*itr2)->_obiekty[0].getPosition(), Color::Red));
											//znaleziono_klocek = true;
											d = odleglosc(p1, l3);
											//aktualny_element = plansza[i][j];
										}
										if (dynamic_cast<klocek_odbijajacy*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											point przec = przeciecie(p1, p2, l3, l4);
											punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
											znaleziono_klocek = true;
											aktualny_element = plansza[i][j];
										}
										if (dynamic_cast<odbiornik*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											if (plansza[i][j]->_odblokowany)
											{
												point przec = przeciecie(p1, p2, l3, l4);
												punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
												sukces = true;
												znaleziono_klocek = true;
												aktualny_element = plansza[i][j];
											}
										}
										if (znaleziono_klocek || znaleziono) break;
									}
								}
							}
							else if (d0.x == 0.f)
							{
								int j = (*aktualny_element)._polozenie_na_planszy_x;
								//if (!sprawdzanie_przeciec(i, j, aktualny_element, p1, p2, punkty_P, d, znaleziono, znaleziono_klocek, sukces)) break;
								point l1 = { plansza[i][j]->x_p ,plansza[i][j]->y_p };
								point l2 = { plansza[i][j]->x_k ,plansza[i][j]->y_k };
								point l3 = { plansza[i][j]->x_p2 ,plansza[i][j]->y_p2 };
								point l4 = { plansza[i][j]->x_k2 ,plansza[i][j]->y_k2 };
								if (przecinaja_sie(l1, l2, p1, p2) && plansza[i][j] != aktualny_element)
								{

									if (dynamic_cast<lustro*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										point przec = przeciecie(p1, p2, l1, l2);
										punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
										plansza[i][j]->aktywuj();
										d = odleglosc(p1, l1);
										aktualny_element = plansza[i][j];
										znaleziono = true;
									}
									if (dynamic_cast<punkt*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										//wybuch(window, *plansza[i][j], _tekstura_wybuch, koniec_gry, sukces, punkty_P);
										plansza[i][j]->zestrzel();
										//punkty_P.push_back(Vertex((*itr2)->_obiekty[0].getPosition(), Color::Red));
										//znaleziono_klocek = true;
										d = odleglosc(p1, l1);
										//aktualny_element = plansza[i][j];
									}
									if (dynamic_cast<klocek_odbijajacy*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										point przec = przeciecie(p1, p2, l1, l2);
										punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
										//punkty_P.push_back(Vertex(plansza[i][j]->_obiekty[0].getPosition(), Color::Red));
										znaleziono_klocek = true;
										aktualny_element = plansza[i][j];
									}
									if (dynamic_cast<odbiornik*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										if (plansza[i][j]->_odblokowany)
										{
											point przec = przeciecie(p1, p2, l1, l2);
											punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
											sukces = true;
											znaleziono_klocek = true;
											aktualny_element = plansza[i][j];
										}
									}
									if (znaleziono_klocek || znaleziono) break;


								}
								if (przecinaja_sie(l3, l4, p1, p2) && plansza[i][j] != aktualny_element)
								{
									if (dynamic_cast<punkt*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										//wybuch(window, *plansza[i][j], _tekstura_wybuch, koniec_gry, sukces, punkty_P);
										plansza[i][j]->zestrzel();

										//punkty_P.push_back(Vertex((*itr2)->_obiekty[0].getPosition(), Color::Red));
										//znaleziono_klocek = true;
										d = odleglosc(p1, l3);
										//aktualny_element = plansza[i][j];
									}
									if (dynamic_cast<klocek_odbijajacy*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										point przec = przeciecie(p1, p2, l3, l4);
										punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
										znaleziono_klocek = true;
										aktualny_element = plansza[i][j];
									}
									if (dynamic_cast<odbiornik*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
									{
										if (plansza[i][j]->_odblokowany)
										{
											point przec = przeciecie(p1, p2, l3, l4);
											punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
											sukces = true;
											znaleziono_klocek = true;
											aktualny_element = plansza[i][j];
										}
									}
									if (znaleziono_klocek || znaleziono) break;
								}
							}
							else
							{
								for (int j = (*aktualny_element)._polozenie_na_planszy_x; j < 15; j++)
								{
									//if (!sprawdzanie_przeciec(i, j, aktualny_element, p1, p2, punkty_P, d, znaleziono, znaleziono_klocek, sukces)) break;

									point l1 = { plansza[i][j]->x_p ,plansza[i][j]->y_p };
									point l2 = { plansza[i][j]->x_k ,plansza[i][j]->y_k };
									point l3 = { plansza[i][j]->x_p2 ,plansza[i][j]->y_p2 };
									point l4 = { plansza[i][j]->x_k2 ,plansza[i][j]->y_k2 };
									if (przecinaja_sie(l1, l2, p1, p2) && plansza[i][j] != aktualny_element)
									{

										if (dynamic_cast<lustro*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											point przec = przeciecie(p1, p2, l1, l2);
											punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
											plansza[i][j]->aktywuj();
											d = odleglosc(p1, l1);
											aktualny_element = plansza[i][j];
											znaleziono = true;
										}
										if (dynamic_cast<punkt*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											//wybuch(window, *plansza[i][j], _tekstura_wybuch, koniec_gry, sukces, punkty_P);
											plansza[i][j]->zestrzel();
											//punkty_P.push_back(Vertex((*itr2)->_obiekty[0].getPosition(), Color::Red));
											//znaleziono_klocek = true;
											d = odleglosc(p1, l1);
											//aktualny_element = plansza[i][j];
										}
										if (dynamic_cast<klocek_odbijajacy*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											point przec = przeciecie(p1, p2, l1, l2);
											punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
											//punkty_P.push_back(Vertex(plansza[i][j]->_obiekty[0].getPosition(), Color::Red));
											znaleziono_klocek = true;
											aktualny_element = plansza[i][j];
										}
										if (dynamic_cast<odbiornik*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											if (plansza[i][j]->_odblokowany)
											{
												point przec = przeciecie(p1, p2, l1, l2);
												punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
												sukces = true;
												znaleziono_klocek = true;
												aktualny_element = plansza[i][j];
											}
										}
										if (znaleziono_klocek || znaleziono) break;


									}
									if (przecinaja_sie(l3, l4, p1, p2) && plansza[i][j] != aktualny_element)
									{
										if (dynamic_cast<punkt*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											//wybuch(window, *plansza[i][j], _tekstura_wybuch, koniec_gry, sukces, punkty_P);
											plansza[i][j]->zestrzel();

											//punkty_P.push_back(Vertex((*itr2)->_obiekty[0].getPosition(), Color::Red));
											//znaleziono_klocek = true;
											d = odleglosc(p1, l3);
											//aktualny_element = plansza[i][j];
										}
										if (dynamic_cast<klocek_odbijajacy*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											point przec = przeciecie(p1, p2, l3, l4);
											punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
											znaleziono_klocek = true;
											aktualny_element = plansza[i][j];
										}
										if (dynamic_cast<odbiornik*>(plansza[i][j]))// && odleglosc(p1, l1) < d)
										{
											if (plansza[i][j]->_odblokowany)
											{
												point przec = przeciecie(p1, p2, l3, l4);
												punkty_P.push_back(Vertex(Vector2f(przec.x, przec.y), Color::Red));
												sukces = true;
												znaleziono_klocek = true;
												aktualny_element = plansza[i][j];
											}
										}
										if (znaleziono_klocek || znaleziono) break;
									}
								}
							}
							if (znaleziono_klocek || znaleziono) break;
						}
					}

					if (znaleziono == false && znaleziono_klocek == false)
					{

						punkty_P.push_back(Vertex(Vector2f(p2.x, p2.y), Color::Red));
						break;
					}
					else break;
				}


				if (znaleziono == false || znaleziono_klocek == true) break;


				cosinus = cosf(aktualny_element->_obrot * 3.14 / 180.0);
				cosinus = round(cosinus * 100.0) / 100.0;
				sinus = sinf(aktualny_element->_obrot * 3.14 / 180.0);
				sinus = round(sinus * 100.0) / 100.0;
				znaleziono = false;
				Wektor2D n(sinus, -cosinus);
				n.normuj();
				float tmp = d0*n;
				tmp = 2 * tmp;
				n = { tmp*n.x,tmp*n.y };
				Wektor2D d1 = d0 - n;
				d1 = { round(d1.x * 100.f) / 100.f , round(d1.y * 100.f) / 100.f };
				if (d1.x == -0.0) d1.x = 0.0;
				if (d1.y == -0.0) d1.y = 0.0;
				d0 = d1;
				p1 = { punkty_P.back().position.x ,punkty_P.back().position.y };
				p2 = { p1.x + d0.x * window_r, p1.y + d0.y * window_r };

				licznik++;
			}
		}

		return sukces;
}

int main()
{
	/*USTAWIENIA POCZ¥TKOWE*/

	laduj_konfiguracje();
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(window_x, window_y), "Nowy Deflektor!", sf::Style::Close | sf::Style::Titlebar);
	const unsigned char * Icon = icon.getPixelsPtr();
	window.setIcon(70, 70, Icon);

reset:
	for (auto &poziom : poziomy)
	{
		static int aktualny_poziom = 1;
		bool exit = false;
		plansza.clear();
		wskazniki.clear();
		przyciski.clear();
		teksty.clear();
		dodawanieElementow(window, poziom);
		sf::Clock timer; // zegar uzywany przez funkcje "sukces"
		sf::Clock timer3; // zegar odswiezania
		sf::Clock czas_od_uruchomienia; // zegar do pomiaru energii
		sf::Time energia;
		sf::Time czas_zatrzymania = milliseconds(0.f);
		int liczba_punktow = 0;
		int max_liczba_punktow = 0;
		bool koniec_gry = false;
		bool sukces = false;
		bool restart = false;
		bool ladowanie = true;
		for (auto itr = plansza.begin(); itr != plansza.end(); itr++)
		{
			for (auto itr2 = (*itr).begin(); itr2 != (*itr).end(); itr2++)
			{
				if (dynamic_cast<punkt*>(*itr2))
				{
					max_liczba_punktow++;
				}
			}
		}
		if (max_liczba_punktow == 0) max_liczba_punktow = 1;
		ustawienia_poczatkowe(window, max_liczba_punktow,aktualny_poziom);
		/*G£óWNA PÊTLA PROGRAMU*/
		while (window.isOpen())
		{
			if (!pauza) energia = czas_od_uruchomienia.getElapsedTime() + czas_zatrzymania;

			/*obs³uga zdarzeñ*/

			sf::Event event;
			while (window.pollEvent(event) && ladowanie == false)
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				{
					if (!pauza) czas_zatrzymania = czas_od_uruchomienia.getElapsedTime();
					if (pauza)
					{
						czas_od_uruchomienia.restart();
					}
					pauza = !pauza;

				}

				if ((100 - energia.asSeconds()) < 0)
					koniec_gry = true;
				/*KLIKNIECIE PRZYCISKU*/
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == (sf::Mouse::Left) && czyWcisnieto(przyciski[2], window))
				{
					restart = true;
				}
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == (sf::Mouse::Left) && czyWcisnieto(przyciski[3], window))
				{
					if (!pauza) czas_zatrzymania = czas_od_uruchomienia.getElapsedTime();
					if (pauza)
					{
						czas_od_uruchomienia.restart();
					}
					pauza = !pauza;

				}
			}



			if (!sukces && !ladowanie && !pauza) wskazniki[0]->aktualizuj(100 - energia.asSeconds()*predkosc_gry*0.01);
			wskazniki[1]->aktualizuj(liczba_punktow * 100 / max_liczba_punktow);
			if (liczba_punktow == max_liczba_punktow)
			{
				odbiornik1->_odblokowany = true;
				plansza[odbiornik1->_polozenie_na_planszy_y][odbiornik1->_polozenie_na_planszy_x + 1]->zestrzel();
				//plansza[odbiornik1->_polozenie_na_planszy_y][odbiornik1->_polozenie_na_planszy_x + 1]->aktualizuj();

				if (plansza[odbiornik1->_polozenie_na_planszy_y][odbiornik1->_polozenie_na_planszy_x + 1]->stan() == 1)
				{
					plansza[odbiornik1->_polozenie_na_planszy_y].at(odbiornik1->_polozenie_na_planszy_x + 1) = new puste_pole(window);

				}


			}
			if (ladowanie)
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					exit = true;
				}
				Time time4 = timer.getElapsedTime();
				if (time4.asMilliseconds() > 300.f)
				{
					//wsk_energii.aktualizuj(wsk_energii.stan() + 1);
					wskazniki[0]->aktualizuj(wskazniki[0]->stan() + 10);
					for (auto itr = plansza.begin(); itr != plansza.end(); itr++)
					{
						for (auto itr2 = (*itr).begin(); itr2 != (*itr).end(); itr2++)
						{
							if (dynamic_cast<lustro*>(*itr2))
							{
								(*itr2)->zmien_polozenie((float)(rand() % 360));
							}
						}
					}
					timer.restart();
				}

				czas_od_uruchomienia.restart();
				if (wskazniki[0]->stan() > 100) ladowanie = false;
			}
			while (sukces)
			{

				Time time4 = timer.getElapsedTime();
				if (time4.asMilliseconds() > 300.f)
				{
					//wsk_energii.aktualizuj(wsk_energii.stan() + 1);
					wskazniki[0]->aktualizuj(wskazniki[0]->stan() + 1);
					timer.restart();
				}
				sf::Event event2;
				while (window.pollEvent(event2) && ladowanie == false) {
					if (event2.type == sf::Event::MouseButtonPressed && event2.mouseButton.button == (sf::Mouse::Left) && czyWcisnieto(plansza_koncowa, window))
					{
						czas_od_uruchomienia.restart();
						exit = true;
					}
					if (event2.type == sf::Event::KeyPressed && event2.key.code == sf::Keyboard::Enter)
					{
						czas_od_uruchomienia.restart();
						exit = true;
					}
					if (event2.type == sf::Event::MouseButtonPressed && event2.mouseButton.button == (sf::Mouse::Left) && czyWcisnieto(przyciski[2], window))
					{
						czas_od_uruchomienia.restart();
						restart = true;
					}
					if (event2.type == sf::Event::Closed)
					{
						window.close();
						exit = true;
					}
						
				}
				if (exit || restart) break;
			}
			if (exit) break;
			if (restart)
			{
				for (auto itr = plansza.begin(); itr != plansza.end(); itr++)
				{
					for (auto itr2 = (*itr).begin(); itr2 != (*itr).end(); itr2++)
					{
						//if (dynamic_cast<punkt*>(*itr2))
						{
							(*itr2)->resetuj();
						}
						//if (dynamic_cast<lustro*>(*itr2))
						//{
						//	(*itr2)->zmien_polozenie(0.f);
						//}

					}
				}
				if (dynamic_cast<puste_pole*>(plansza[odbiornik1->_polozenie_na_planszy_y][odbiornik1->_polozenie_na_planszy_x + 1]))
				{
					plansza[odbiornik1->_polozenie_na_planszy_y].at(odbiornik1->_polozenie_na_planszy_x + 1) = new klocek_odbijajacy(window);
					plansza[odbiornik1->_polozenie_na_planszy_y].at(odbiornik1->_polozenie_na_planszy_x + 1)->ustaw_na_planszy(odbiornik1->_polozenie_na_planszy_x + 1, odbiornik1->_polozenie_na_planszy_y, window);
				}
				liczba_punktow = 0;
				sukces = false;
				koniec_gry = false;
				pauza = false;
				wskazniki[0]->aktualizuj(0);
				wskazniki[1]->aktualizuj(0);
				//rysuj_plansze(window, koniec_gry, sukces, restart, punkty_P);
				czas_od_uruchomienia.restart();
				czas_zatrzymania = milliseconds(0.f);
				pauza = false;
				restart = false;
				ladowanie = true;
			}

			if (timer3.getElapsedTime() >= sf::milliseconds(30))
			{
				std::vector<sf::Vertex> punkty_P;
				//wektor przechowujacy wspolrzedne punktow odbiæ, resetowany przy ka¿dym obiegu pêtli, zachowuje dane przy pauzie

				if (pauza == false && koniec_gry == false && ladowanie == false)
				{
					/*KLIKNIECIA NA LUSTRA*/
					if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == (sf::Mouse::Left))
					{
						for (auto itr = plansza.begin(); itr != plansza.end(); itr++)
						{
							for (auto itr2 = (*itr).begin(); itr2 != (*itr).end(); itr2++)
							{
								if (dynamic_cast<lustro*>(*itr2))
								{
									float obrot = (*itr2)->_obiekty[1].getRotation();
									if (czyWcisnieto((*itr2)->_obiekty[0], window))
									{
										(*itr2)->zmien_polozenie(obrot + 1.f);
										break;
									}
								}
							}
						}
					}
					if (aktualizuj(window, koniec_gry, sukces, restart, punkty_P, liczba_punktow, max_liczba_punktow))
						sukces = true;



				}

				rysuj_plansze(window, ladowanie, koniec_gry, sukces, restart, punkty_P);
				timer3.restart();
			}
		}
		aktualny_poziom++;
		//end for
	}

	while (window.isOpen())
	{
		sf::Event event;
		bool exit = false;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == (sf::Mouse::Left) && czyWcisnieto(plansza_koncowa, window))
			{
				exit = true;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
			{
				exit = true;
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == (sf::Mouse::Left) && czyWcisnieto(przyciski[2], window))
			{
				goto reset;
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (exit) break;
	}
		return 0;
}

