#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>
#include "StaticValues.h"

namespace math {
	template<typename T>
	double getCoefDir(sf::Vector2<T> p1, sf::Vector2<T> p2);

	template<typename T>
	double getDistance(sf::Vector2<T> origine, sf::Vector2<T> destination);
	
	template<typename T>
	double getDistance(sf::Vector2<T> origine);

	template<typename T>
	double getDistanceCarre(sf::Vector2<T> origine, sf::Vector2<T> destination);

	template<typename T>
	double getDistance(T ax, T ay, T bx, T by);
	
	template<typename T>
	double getDistance(T ax, T ay);

	template<typename T>
	double getDistanceCarre(T ax, T ay, T bx, T by);


	template<typename T>
	double getDirection(sf::Vector2<T> A, sf::Vector2<T> B);

	template<typename T>
	double getAngle(sf::Vector2<T> origine, sf::Vector2<T> destination);

	template<typename T>
	bool isAtLeft(sf::Vector2<T> p, double myRotation, sf::Vector2<T> target);
	template<typename T>
	bool isAtLeft(sf::Vector2<T> V1, sf::Vector2<T> V2);

	template<typename T>
	double getDirectionDeg(sf::Vector2<T> A, sf::Vector2<T> B);

	template<typename T>
	double getAngleDeg(sf::Vector2<T> origine, sf::Vector2<T> destination);

	template<typename T>
	T PGCD(T a, T b);

	template<typename T,typename J>
	T mod(T a, J b);

	template<typename T>
	bool isDivisibleBy(T num, T diviseur);
	template<typename T>
	bool isMultiple(T num, T multiple);


	double ToDeg(double rad);
	double ToRad(double deg);

	double round(double value, int nbChiffre);

	int getNbDigits(int nb);

	sf::Vector2f normalise(sf::Vector2f vec);
	double dot(sf::Vector2f a, sf::Vector2f b);
	
}

#include "MathFunction.ipp"