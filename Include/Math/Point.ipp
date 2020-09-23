#include "Point.h"
#pragma once


template<typename T>
inline Point<T>::Point()
{
	x = 0;
	y = 0;
}

template<typename T>
inline Point<T>::Point(sf::Vector2<T> v)
{
	this->x = v.x;
	this->y = v.y;
}

template<typename T>
inline Point<T>::Point(T x, T y)
{
	this->x = x;
	this->y = y;
}