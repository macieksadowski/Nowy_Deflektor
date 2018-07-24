#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

class element
{
protected:
	Vector2f _polozenie;
	float window_x;
	float window_y;
	std::vector<Texture> _tekstury;
public:

	float _obrot; // zakres 0-15 co 22.5 stopnia
	float x_p, y_p, x_k, y_k, x_p2, y_p2, x_k2, y_k2;
	std::vector<Sprite> _obiekty;
	int _polozenie_na_planszy_x, _polozenie_na_planszy_y;
	bool _zdobyty;
	bool _odblokowany;

	element(const String & sciezka_tekstury, sf::RenderWindow &av_Window);
	element(sf::RenderWindow &av_Window);
	

	/*METODY*/
	void setPosition(float x, float y);
	void setPosition(const Vector2f& position);
	void setRotation(float angle);
	void setScale(float factorX, float factorY);
	void setScale(const Vector2f& factors);
	void setOrigin(float x, float y);
	void setOrigin(const Vector2f& origin);
	const Vector2f& getPosition() const;
	float getRotation() const;
	const Vector2f& getScale() const;
	const Vector2f& getOrigin() const;
	void move(float offsetX, float offsetY);
	void move(const Vector2f& offset);
	void rotate(float angle);
	void scale(float factorX, float factorY);
	void scale(const Vector2f& factor);
	virtual void rysuj(sf::RenderWindow &av_Window);
	void przesun_na_planszy(int x, int y, sf::RenderWindow &av_Window);
	virtual void ustaw_na_planszy(int x, int y, sf::RenderWindow &av_Window);
	void obroc_na_planszy(int obrot, sf::RenderWindow &av_Window);
	virtual void zmien_polozenie(float kat);
	virtual void zestrzel();
	virtual int stan();  //dotyczy klocka przy odbiorniku
	virtual void aktywuj();
	virtual void resetuj();
	virtual void dezaktywuj();
	virtual void aktualizuj();
	virtual void automatyczne();
	~element();
};

