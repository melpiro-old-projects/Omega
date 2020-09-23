#pragma once
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
#include "triplet.h"
#include <climits>
#include <queue>
#include "VectorFunctions.h"

#include "FileFunctions.h"
#include "ParseFunctions.h"

template <typename T>
class Graph
{
public:
	Graph();


	void addNode(T value);
	void addEdges(T from, T to, double distance);
	void removeEdges(T from, T to);

	int minDistance(std::vector<double> dist, std::vector<bool> sptSet);
	int maxDistance(std::vector<double> dist, std::vector<bool> sptSet);

	int getIndexInListNode(T node);

	std::vector < std::triplet<T, T, double>> dijkstra(T from);
	std::vector <T> dijkstra(T from, T to);

	bool bfs(std::vector<std::vector< std::pair<bool, double> >>rGraph, int s, int t, std::vector<int>& parent);
	std::pair<double, std::vector<std::vector< std::pair<bool, double> >> > fordFulkerson(T source, T puit, std::vector<std::pair<std::pair<T, T>, double>>  minConstraint = std::vector<std::pair<std::pair<T, T>, double>>(0));

	std::vector<T> getAllNodes();
	std::vector<std::vector< std::pair<bool, double> >> getAllEdges();

	double getDistance(std::vector<T> path);

	bool isConnexe();

	bool haveEdge(T from, T to);

	void print();


private:

	std::vector<T> m_nodes;

	std::vector<std::vector< std::pair<bool, double> >> m_edges;


};
#include "Graph.ipp"

namespace graph
{
	Graph<int> loadFromFile(std::string fileName, bool isOriented=true);
} // namespace graph

