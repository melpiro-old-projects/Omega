
#include "StringFunctions.h"
#include "PrintFunctions.h"

enum Operation
{
	SUP,INF,EQL
};

namespace optimisation
{
	class Simplex
	{
	public:
		Simplex();

		void setFunction(std::vector<double> function, bool maximise = true);
		void addConstraint(std::vector<double> line, double out, Operation operation = Operation::INF);

		
		void solve(bool showInfos = false, std::string varName = "x");

		double getOptimalite();
		std::vector<double> getValuesForEachVars();

		

	private:

		void invertFunction();
		void addBasicsVariables();

		void addOneBasicVariable(int index);
		void addOneSuplemBasicVariable(int index);
		void addOneNegativeBasicVariable(int index);
		void decomposeVars(int i);

		void calcBasicSolution();
		bool pivot();

		// line / out
		std::pair<std::vector<double>, double> getVarIndexInFonctionOfOrtherIntoEquation(int indexEquation, int indexVar);

		int getIndexOfFirstNonNegativeCoefInFunction();
		void replaceInEachEquation(std::pair<std::vector<double>, double> equation, int indexVar, int indexEquation);
	
		void print();





		std::vector<std::vector<double>> m_system;
		std::vector<double> m_out;
		std::vector<Operation> m_operators;

		std::vector<double> m_function;
		double m_functionOut = 0; // suelement pour le pivot
		std::vector<int> m_indexBasicVars;

		bool m_maximise;

		std::vector<double> m_solutions;
		int m_indexFirstBasicVar;


		std::vector<str::u8string> m_allVarsName;
		int nbArtificalVars = 0;

		int nbVars;
	};



}