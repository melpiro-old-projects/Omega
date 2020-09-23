#pragma once

namespace std {

	template<typename T, typename U, typename V>
	class triplet;

	template<typename T, typename U, typename V>
	triplet<T, U, V> make_triplet(T first, U second, V third);

	template<typename T, typename U, typename V>
	class triplet
	{
	public:
		T first;
		U second;
		V third;
	};
	
}

namespace std {
	template<typename T, typename U, typename V>
	inline triplet<T, U, V> make_triplet(T first, U second, V third)
	{
		triplet<T, U, V> r;
		r.first = first;
		r.second = second;
		r.third = third;

		return r;
	}
}

