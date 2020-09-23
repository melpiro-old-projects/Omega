#include "EnsembleFunctions.h"


namespace math {

	template<typename T>
	std::vector<std::vector<T>> getCombinationsWithReapeat(std::vector<T> vector, int nbElements)
	{
		if (nbElements <= 0) return std::vector<std::vector<T>>(0);
		std::vector<std::vector<T>> res;

		std::vector<int> combin = vector::createVector(nbElements, 0);

		bool run = true;

		while (run)
		{
			res.push_back(std::vector<T>(nbElements));
			for (size_t i = 0; i < nbElements; i++)
			{
				res.back()[i] = vector[combin[i]];
			}


			int indexLast = combin.size() - 1;
			combin[indexLast]++;

			while (indexLast > 0 && combin[indexLast] >= vector.size())
			{
				combin[indexLast - 1]++;
				combin[indexLast] = 0;

				indexLast--;
			}

			if (indexLast <= 0 && combin[indexLast] >= vector.size()) return res;

		}

	}

	template<typename T>
	std::vector<std::vector<T>> getCombinations(std::vector<T> vector, int nbElements)
	{
		if (nbElements <= 0) return std::vector<std::vector<T>>(0);
		if (nbElements > vector.size()) return std::vector<std::vector<T>>(0);

		std::vector<std::vector<T>> res;

		std::vector<int> combin = vector::createVector(nbElements, 0, 1);

		bool run = true;

		while (run)
		{
			res.push_back(std::vector<T>(nbElements));
			for (size_t i = 0; i < nbElements; i++)
			{
				res.back()[i] = vector[combin[i]];
			}


			int indexLast = combin.size() - 1;
			combin[indexLast]++;

			while (indexLast > 0 && combin[indexLast] > vector.size() + indexLast - nbElements)
			{
				combin[indexLast - 1]++;
				indexLast--;
			}

			if (indexLast == 0 && combin[indexLast] > vector.size() - nbElements) return res;

			for (size_t i = indexLast; i < combin.size() - 1; i++)
			{
				combin[i + 1] = combin[i] + 1;
			}
		}
	}
	template<typename T>
	std::vector<std::vector<T>> getAllCombinationsWithReapeat(std::vector<T> vector, int nbMaxElements)
	{
		std::vector<std::vector<T>> res(0);

		for (size_t i = 1; i <= nbMaxElements; i++)
		{
			vector::pushBack(res, getCombinationsWithReapeat(vector, i));
		}
		return res;
	}
	template<typename T>
	std::vector<std::vector<T>> getAllCombinationsWithReapeat(std::vector<T> vector)
	{
		std::vector<std::vector<T>> res(0);

		for (size_t i = 1; i <= vector.size(); i++)
		{
			vector::pushBack(res, getCombinationsWithReapeat(vector, i));
		}
		return res;
	}
	template<typename T>
	std::vector<std::vector<T>> getAllCombinations(std::vector<T> vector, int nbMaxElements)
	{
		std::vector<std::vector<T>> res(0);

		for (size_t i = 1; i <= nbMaxElements; i++)
		{
			vector::pushBack(res, getCombinations(vector, i));
		}
		return res;
	}
	template<typename T>
	std::vector<std::vector<T>> getAllCombinations(std::vector<T> vector)
	{
		std::vector<std::vector<T>> res(0);

		for (size_t i = 1; i <= vector.size(); i++)
		{
			vector::pushBack(res, getCombinations(vector, i));
		}
		return res;
	}
	template<typename T>
	std::vector<std::vector<T>> getPermutations(std::vector<T> vector)
	{
		std::vector < std::vector<T> > res;
		_getPermutationsRecur(vector, vector.size(), vector.size(), res);
		return res;
	}
	template<typename T>
	void _getPermutationsRecur(std::vector<T>& vector, int size, int n, std::vector < std::vector<T> >& res)
	{
		if (size == 1)
		{
			res.push_back(vector);
			return;
		}
		for (int i = 0; i < size; i++)
		{
			_getPermutationsRecur(vector, size - 1, n, res);

			if (size % 2 == 1)
				vector::swap(&vector, 0, size - 1);
			else
				vector::swap(&vector, i, size - 1);
		}
	}
	template<typename T>
	std::vector<std::vector<T>> getArrengements(std::vector<T> vector, int size)
	{
		
	}
}