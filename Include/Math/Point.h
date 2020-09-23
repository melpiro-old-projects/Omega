#pragma once

#include <SFML/System/Vector2.hpp>

template<typename T>
class Point
{
public:
	Point();
	Point(sf::Vector2<T> v);
	Point(T x, T y);


	Point& operator= (const sf::Vector2<T>& v) { return *(this(v.x,v.y)); }
	operator sf::Vector2<T>() { return sf::Vector2<T>(x,y); }

	T x;
	T y;
};


#include "Point.ipp"


