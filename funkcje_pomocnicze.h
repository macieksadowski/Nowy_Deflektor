#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <SFML/Graphics.hpp>
#include "Wektor2D.h"
#include <SFML/System/Vector2.hpp>

bool czyWcisnieto(sf::Sprite &av_Sprite, sf::RenderWindow &av_Window);

float odleglosc(point p1, point p2);

point przeciecie(point p1, point p2, point p3, point p4);

bool lezy_miedzy(point p1, point p2, point p3);

float iloczyn(point p1, point p2, point p3);

bool przecinaja_sie(point p1, point p2, point p3, point p4);