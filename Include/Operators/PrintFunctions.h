#pragma once

#include <vector>
#include <iostream>
#include <tuple>
#include <SFML/Graphics.hpp>

#include "triplet.h"
#include "CityNode.h"

template<typename T> struct is_vector : public std::false_type {};

template<typename T, typename A>
struct is_vector<std::vector<T, A>> : public std::true_type {};

namespace print {
	template<typename T>
	void print(T var);
	template<typename T>
	void print(T* var);
	void print(CityNode var);
	template<typename T, typename J>
	void print(std::pair<T, J> pair);
	template<typename T>
	void print(std::vector<T> vector);
	template<typename T, typename J, typename K>
	void print(std::tuple<T, J, K> tuple);

}

std::ostream& operator<<(std::ostream& os, std::wstring str);

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v);

template <typename T>
std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& v);

std::ostream& operator<<(std::ostream& os, const sf::Color v);


template <typename T, typename J>
std::ostream& operator<<(std::ostream& os, const std::pair<T, J >& v);
template<typename T, typename J, typename K>
std::ostream& operator<<(std::ostream& os, const std::tuple<T, J, K>& v);

template<typename T, typename J, typename K>
std::ostream& operator<<(std::ostream& os, const std::triplet<T, J, K>& v);


#include "PrintFunctions.ipp"


