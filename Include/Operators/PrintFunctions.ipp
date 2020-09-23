#include "PrintFunctions.h"

namespace print {

	template<typename T>
	void print(T var)
	{
		std::cout << var;
	}
	///////////////////////////////////////////////////////////////
	template<typename T>
	void print(T* var)
	{
		print(*var);
	}
	///////////////////////////////////////////////////////////////

	template<typename T>
	void print(std::vector<T> vector)
	{
		std::cout << "[";
		for (size_t i = 0; i < vector.size(); i++)
		{
			print(vector[i]);
			if (i < vector.size() - 1) std::cout << ',';
		}
		std::cout << "]";
	}
	template<typename T, typename J, typename K>
	void print(std::tuple<T, J, K> tuple)
	{
		T a;
		J b;
		K c;
		std::tie(a, b, c) = tuple;
		std::cout << '(';
		print(a);
		std::cout << ',';
		print(b);
		std::cout << ',';
		print(c);
		std::cout << ')';
	}
	///////////////////////////////////////////////////////////////
	template<typename T, typename J>
	void print(std::pair<T, J> pair)
	{
		std::cout << '(';
		print(pair.first);
		std::cout << ',';
		print(pair.second);
		std::cout << ')';
	}
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
	os << "\n[";
	for (int i = 0; i < v.size(); ++i) {
		os << v[i];
		if (i != v.size() - 1)
			os << ", ";
	}
	os << "]";
	return os;
}



template<typename T>
inline std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& v)
{
	os << '(';
	os << v.x;
	os << ',';
	os << v.y;
	os << ')';
	return os;
}

template<typename T, typename J>
inline std::ostream& operator<<(std::ostream& os, const std::pair<T, J>& v)
{
	os << '(';
	os << v.first;
	os << ',';
	os << v.second;
	os << ')';
	return os;
}

template<typename T, typename J, typename K>
inline std::ostream& operator<<(std::ostream& os, const std::tuple<T, J, K>& v)
{
	T a;
	J b;
	K c;
	std::tie(a, b, c) = v;
	os << '(';
	os << a;
	os << ',';
	os << b;
	os << ',';
	os << c;
	os << ')';

	return os;
}

template<typename T, typename J, typename K>
inline std::ostream& operator<<(std::ostream& os, const std::triplet<T, J, K>& v)
{
	os << '(';
	os << v.first;
	os << ',';
	os << v.second;
	os << ',';
	os << v.third;
	os << ')';

	return os;
}


