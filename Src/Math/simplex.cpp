#include "simplex.h"

optimisation::Simplex::Simplex()
{
}

void optimisation::Simplex::setFunction(std::vector<double> function, bool maximise)
{
	m_function = function;
	m_maximise = maximise;
	nbVars = function.size();
}

void optimisation::Simplex::addConstraint(std::vector<double> line, double out, Operation operation)
{
	m_system.push_back(line);
	m_out.push_back(out);
	m_operators.push_back(operation);
}

void optimisation::Simplex::invertFunction()
{
	for (size_t i = 0; i < m_function.size(); i++)
	{
		m_function[i] *= -1;
	}
}

void optimisation::Simplex::addBasicsVariables()
{
	m_indexFirstBasicVar = m_system[0].size();

	for (size_t i = 0; i < m_system.size(); i++)
	{
		if (m_operators[i] == Operation::SUP)addOneNegativeBasicVariable(i);
		if (m_operators[i] == Operation::INF)addOneBasicVariable(i);
	}
	for (size_t i = 0; i < m_system.size(); i++)
	{
		if (m_operators[i] == Operation::EQL)addOneSuplemBasicVariable(i);
		if (m_operators[i] == Operation::SUP)addOneSuplemBasicVariable(i);
	}

	for (size_t i = 0; i < m_system.size(); i++)
	{

		int index;

		for (index = m_system[i].size() - 1; index >= 0; index--)
		{
			if (m_system[i][index] != 0) break;
		}

		m_indexBasicVars.push_back(index);

	}

}

void optimisation::Simplex::addOneBasicVariable(int index)
{
	m_function.push_back(0);
	for (size_t i = 0; i < m_system.size(); i++)
	{
		m_system[i].push_back(0);
		if (i == index)
		{
			m_allVarsName.push_back(str::u8string("x") + str::getIndexOf(str::u8string(std::to_string(m_system[i].size()))));
			m_system[i].back() = 1;
		}
	}
}

void optimisation::Simplex::addOneSuplemBasicVariable(int index)
{
	addOneBasicVariable(index);
	nbArtificalVars++;

	m_allVarsName.pop_back();
	m_allVarsName.push_back(str::u8string("y") + str::getIndexOf(str::u8string(std::to_string(nbArtificalVars))));

}



void optimisation::Simplex::addOneNegativeBasicVariable(int index)
{
	m_function.push_back(0);
	for (size_t i = 0; i < m_system.size(); i++)
	{
		m_system[i].push_back(0);
		if (i == index)
		{
			m_allVarsName.push_back(str::u8string("x") + str::getIndexOf(str::u8string(std::to_string(m_system[i].size()))));
			m_system[i].back() = -1;
		}
	}
}

void optimisation::Simplex::decomposeVars(int index)
{
	m_function.insert(m_function.begin() + index + 1, -m_function[index]);
	for (size_t i = 0; i < m_system.size(); i++)
	{
		m_system[i].insert(m_system[i].begin() + index + 1, -m_system[i][index]);
	}
}

void optimisation::Simplex::solve(bool showInfos,std::string varName)
{
	for (size_t i = 0; i < m_system[0].size(); i++)
	{
		m_allVarsName.push_back(str::u8string(varName) + str::getIndexOf(str::u8string(std::to_string(i + 1))));
	}
	
	if (showInfos)
	{
		std::cout << "résolution du system linéaire suivant : "<<std::endl;
		print();
	}

	if (m_maximise)invertFunction();

	addBasicsVariables();
	calcBasicSolution();

	// on fait des pivots en boucle jusqu'a résoudre le problème
	while (pivot()){}
	
}

double optimisation::Simplex::getOptimalite()
{
	return m_functionOut;
}
std::vector<double> optimisation::Simplex::getValuesForEachVars()
{
	std::vector<double> res;
	for (int i = 0; i < nbVars; i++)
	{
		res.push_back(m_solutions[i]);
	}
	return res;
}

void optimisation::Simplex::calcBasicSolution()
{
	std::vector<double> sol = vector::createVector(m_system[0].size(), 0.0);

	for (size_t i = m_indexFirstBasicVar; i < sol.size(); i++)
	{
		sol[i] = m_out[i - m_indexFirstBasicVar];
	}
	m_solutions = sol;
}

bool optimisation::Simplex::pivot()
{
	int varIndex = getIndexOfFirstNonNegativeCoefInFunction();
	if (varIndex == -1) return false;
	std::vector<double> maxValueOfVarSample = vector::createVector(m_system.size(), 0.0);
	if (m_maximise)
	{
		std::vector<double> maxValueOfVar = maxValueOfVarSample;
		for (size_t i = 0; i < m_system.size(); i++)
		{
			if (m_system[i][varIndex] > 0)
				maxValueOfVar[i] = m_out[i] / m_system[i][varIndex];
			else
				maxValueOfVar[i] = 10000000000000.0; // inifnity !!!!!!
		}

		int minIndex = vector::minIndex(maxValueOfVar);

		//on reset la solution
		m_solutions[m_indexBasicVars[minIndex]] = 0;
		m_indexBasicVars[minIndex] = varIndex;

		std::pair<std::vector<double>, double> varEquation = getVarIndexInFonctionOfOrtherIntoEquation(minIndex, varIndex);

		replaceInEachEquation(varEquation, varIndex, minIndex);
	}
	else
	{
		std::vector<double> maxValueOfVar = maxValueOfVarSample;
		for (size_t i = 0; i < m_system.size(); i++)
		{
			if (m_system[i][varIndex] < 0)
				maxValueOfVar[i] = m_out[i] / m_system[i][varIndex];
			else
				maxValueOfVar[i] = 10000000000000.0; // inifnity !!!!!!
		}

		int minIndex = vector::minIndex(maxValueOfVar);

		//on reset la solution
		m_solutions[m_indexBasicVars[minIndex]] = 0;
		m_indexBasicVars[minIndex] = varIndex;

		std::pair<std::vector<double>, double> varEquation = getVarIndexInFonctionOfOrtherIntoEquation(minIndex, varIndex);

		replaceInEachEquation(varEquation, varIndex, minIndex);
	}
	return true;
}

std::pair<std::vector<double>, double>  optimisation::Simplex::getVarIndexInFonctionOfOrtherIntoEquation(int indexEquation, int indexVar)
{
	std::vector<double> res = vector::createVector(m_system[indexEquation].size(), 0.0);
	for (size_t i = 0; i < m_system[indexEquation].size(); i++)
	{
		res[i] = m_system[indexEquation][i] / m_system[indexEquation][indexVar];
	}
	double out = m_out[indexEquation] / m_system[indexEquation][indexVar];

	return std::make_pair(res, out);
}

int optimisation::Simplex::getIndexOfFirstNonNegativeCoefInFunction()
{
	if (m_maximise) {
	
		double minValue = 0;
		int minIndex = -1;
		for (size_t i = 0; i < m_function.size(); i++)
		{
			if (m_function[i] < minValue)
			{
				minValue = m_function[i];
				minIndex = i;
			}
		}
		return minIndex;
	}
	else
	{
		double maxValue = 0;
		int maxIndex = -1;
		for (size_t i = 0; i < m_function.size(); i++)
		{
			if (m_function[i] > maxValue)
			{
				maxValue = m_function[i];
				maxIndex = i;
			}
		}
		return maxIndex;
	}
	return -1;
}

void optimisation::Simplex::replaceInEachEquation(std::pair<std::vector<double>, double> equation, int indexVar, int indexEquation)
{
	m_system[indexEquation] = equation.first;
	m_out[indexEquation] = equation.second;

	
	// function

	double varCoefInFunction = m_function[indexVar];
	for (size_t i = 0; i < m_function.size(); i++)
	{
		m_function[i] -= varCoefInFunction * equation.first[i];
	}
	m_functionOut -= varCoefInFunction * equation.second;

	// system

	for (int i = 0; i < m_system.size(); i++)
	{
		if (i != indexEquation)
		{
			double varCoefInThisEquation = m_system[i][indexVar];

			for (size_t j = 0; j < m_system[i].size(); j++)
			{
				m_system[i][j] -= varCoefInThisEquation * equation.first[j];
			}
			m_out[i] -= varCoefInThisEquation * equation.second;
		}
	}

	

	// calc solutions :
	for (size_t i = 0; i < m_indexBasicVars.size(); i++)
	{
		m_solutions[m_indexBasicVars[i]] = m_out[i];
	}
}

void optimisation::Simplex::print()
{
	if (m_maximise)
		std::cout << "max : ";
	else
		std::cout << "min : ";

	unsigned long int decalage = 0;
	for (size_t i = 0; i < m_function.size(); i++)
	{

		if (m_function[i] != 0)
		{
			if (i == decalage)
			{
				if (m_function[i] < 0) std::cout << " - ";

				if (std::abs(m_function[i]) != 1)
					std::cout << std::abs(m_function[i]);
			}
			else
			{
				if (m_function[i] > 0) std::cout << " + ";
				else std::cout << " - ";

				if (std::abs(m_function[i]) != 1)
					std::cout << std::abs(m_function[i]);
			}

			std::cout << m_allVarsName[i];
		}
		else decalage++;
	}

	std::cout << '\n';
	for (size_t constraint = 0; constraint < m_system.size(); constraint++)
	{
		unsigned int decalage = 0;
		for (size_t i = 0; i < m_system[constraint].size(); i++)
		{

			if (m_system[constraint][i] != 0)
			{
				if (i == decalage)
				{
					if (m_system[constraint][i] < 0) std::cout << " - ";

					if (std::abs(m_system[constraint][i]) != 1)
						std::cout << std::abs(m_system[constraint][i]);
				}
				else
				{
					if (m_system[constraint][i] > 0) std::cout << " + ";
					else std::cout << " - ";

					if (std::abs(m_system[constraint][i]) != 1)
						std::cout << std::abs(m_system[constraint][i]);
				}

				std::cout << m_allVarsName[i];
			}
			else decalage++;
		}

		if (m_operators[constraint] == Operation::SUP)
		{
			std::cout <<str::u8char(u8" >");

		}
		else if (m_operators[constraint] == Operation::INF)
		{
			std::cout << str::u8char(u8" <");
		}
		else if (m_operators[constraint] == Operation::EQL)
		{
			std::cout << str::u8char(u8" =");
		}
		std::cout << " "<< m_out[constraint];

		std::cout << '\n';

	}
	std::cout << "\n";

}
