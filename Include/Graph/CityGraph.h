#pragma once
#include <SFML/Graphics.hpp>	
#include <vector>
#include <algorithm>
#include <iostream>


#include "PrintFunctions.h"
#include "MathFunctions.h"
#include "CityNode.h"
#include "CityEdge.h"
#include "VectorFunctions.h"
#include "FileFunctions.h"
#include "ParseFunctions.h"


///////////////////////////////////////////////////////////////:
// NOTE IMPORTANTE :
// le graph est cod�e par liste d'adjacence et matrice d'ajacence en m�me temps
// pour des soucis d'optimisation de differants algorithmes
// qui sont plus ou moin efficace avec une m�thode
// ou l'autre
//
// La classe utilise la liste ou la matrice
// selon l'algo demand� pour etre plus efficace
//
// Mais attention tout cela implique de bien comprendre
// les m�thodes appel�, car certaines peuvent etre tr�s lentes (recherches dycotomique etc)
// comme d'autres tr�s rapides
//
// de plus, attention les index et les id sont deux valeurs tr�s differantes :
// index = index dans le vector des nodes
// id = id du node dans le graph
// 


class CityGraph
{
public:
	CityGraph();

	void addNode(CityNode dataNode);
	void addEdges(CityEdge data);

	void removeEdges(CityNode from, CityNode to, CityEdge data);
	void removeEdges(unsigned long long int idNodeFrom, unsigned long long int idNodeTo);

	void speedRender();


	std::vector < std::pair<CityNode*, double>> node_dijkstra(int idNodeFrom);
	std::vector <CityNode*> node_dijkstra(unsigned long long int idNodeFrom, unsigned long long int idNodeTo);
	std::vector < std::pair<CityNode*, double>> node_dijkstra(CityNode from);
	std::vector <CityNode*> node_dijkstra(CityNode from, CityNode to);

	std::vector<CityNode*> getAllNodes();
	CityNode* getNode(unsigned long long int indexNode);
	CityEdge* getEdge(unsigned long long int indexFrom, unsigned long long int indexTo);


	std::vector<CityEdge*> getAllEdgesFrom(CityNode from);
	std::vector<CityEdge*> getAllEdgesFrom(unsigned long long int idNodeFrom);


	int findIndexNodeById(unsigned long long int id);
	int findIndexNodeByCityNode(CityNode node);
	CityNode* findNodeById(unsigned long long int id);
	CityNode* findNodeByCityNode(CityNode node); 

	int findIndexInAdjListOfDest(unsigned long long int indexNodeFrom, CityNode to);
	int findIndexInAdjListOfDest(unsigned long long int indexNodeFrom, unsigned long long int to);

	void setAddedWeightOnEdge(CityNode from, CityNode to, double value);
	void setAddedWeightOnEdge(unsigned long long int idNodeFrom, unsigned long long int idNodeTo, double value);
	void setAddedWeightOnEdgeWithIndex(unsigned long long int indexNodeFrom, unsigned long long int indexNodeTo);

	double getAddedWeightOnEdge();

	void loadPythonGraph(std::string name);
	void loadFromXmlFile(std::string path);
	void createFor(std::string name);

private:

	double minDistance();

	////////////////////////////////////////////////////////////////////////
	// ordon�e par id pour pouvoir trouver un node d'id pr�cis plus vite 
	std::vector<CityNode*> m_nodes;
	
	//liste des edges connect�s par liste adjacence
	std::vector< std::vector<CityEdge*>> m_edgesList;

	std::string m_titleGraph;
};
#include "CityGraph.ipp"

