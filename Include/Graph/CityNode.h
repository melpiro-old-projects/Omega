
#pragma once
#include <string>

class CityNode
{
public:
	unsigned long long int id = 0;
	double x = 0;
	double y = 0;
	std::string ref = "";
	std::string highway = "";


	double dijkstra_distance = 0.0;
	CityNode* dijkstra_lastNode = nullptr;
	bool dijkstra_isVisited = false;
};

