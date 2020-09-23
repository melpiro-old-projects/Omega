#pragma once

#include "VectorFunctions.h"


namespace math {

	template<typename T>
	std::vector< std::vector< T >> getCombinationsWithReapeat(std::vector<T> vector, int nbElements);

	template<typename T>
	std::vector< std::vector< T >> getCombinations(std::vector<T> vector, int nbElements);

	template<typename T>
	std::vector< std::vector< T >> getAllCombinationsWithReapeat(std::vector<T> vector, int nbMaxElements);
	template<typename T>
	std::vector< std::vector< T >> getAllCombinationsWithReapeat(std::vector<T> vector);
	template<typename T>
	std::vector< std::vector< T >> getAllCombinations(std::vector<T> vector, int nbMaxElements);
	template<typename T>
	std::vector< std::vector< T >> getAllCombinations(std::vector<T> vector);

	template<typename T>
	std::vector< std::vector< T >> getPermutations(std::vector<T> vector);
	template<typename T>
	void _getPermutationsRecur(std::vector<T>& vector, int size, int n, std::vector < std::vector<T> >& res);

	template<typename T>
	std::vector< std::vector< T >> getArrengements(std::vector<T> vector, int size);




}


#include "EnsembleFunction.ipp"