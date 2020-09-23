#include "Graph.h"

template<typename T>
inline Graph<T>::Graph()
{
}

template<typename T>
inline void Graph<T>::addNode(T value)
{
	typename std::vector<T>::iterator it = std::find(m_nodes.begin(), m_nodes.end(), value);

	if (it == m_nodes.end())
	{
		m_nodes.push_back(value);


		for (size_t i = 0; i < m_edges.size(); i++)
		{

			m_edges[i].push_back(std::make_pair(false, 0));
		}


		m_edges.push_back(vector::createVector(m_nodes.size(), std::make_pair(false, 0.0)));

	}
	else
	{
		std::cout << "erreur : value deja pr�sente" << std::endl;
	}
}

template<typename T>
inline void Graph<T>::addEdges(T from, T to, double distance)
{
	typename std::vector<T>::iterator it1 = std::find(m_nodes.begin(), m_nodes.end(), from);
	typename std::vector<T>::iterator it2 = std::find(m_nodes.begin(), m_nodes.end(), to);

	if (it1 != m_nodes.end(), it2 != m_nodes.end())
	{
		int i = std::distance(m_nodes.begin(), it1);
		int j = std::distance(m_nodes.begin(), it2);


		m_edges[i][j].first = true;
		m_edges[i][j].second = distance;


	}
}




template<typename T>
inline void Graph<T>::removeEdges(T from, T to)
{
	typename std::vector<T>::iterator it1 = std::find(m_nodes.begin(), m_nodes.end(), from);
	typename std::vector<T>::iterator it2 = std::find(m_nodes.begin(), m_nodes.end(), to);

	if (it1 != m_nodes.end(), it2 != m_nodes.end())
	{
		int i = distance(m_nodes.begin, it1);
		int j = distance(m_nodes.begin, it2);

		m_edges[i][j].first = false;
		m_edges[i][j].second = 0;
	}
}

template<typename T>
inline int Graph<T>::minDistance(std::vector<double> dist, std::vector<bool> sptSet)
{
	double min = INT_MAX, min_index;

	for (int v = 0; v < m_edges.size(); v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

template<typename T>
inline int Graph<T>::maxDistance(std::vector<double> dist, std::vector<bool> sptSet)
{
	double max = 0, max_index;

	for (int v = 0; v < m_edges.size(); v++)
		if (sptSet[v] == false && dist[v] >= max)
			max = dist[v], max_index = v;

	return max_index;
}

template<typename T>
inline std::vector <std::triplet<T, T, double>> Graph<T>::dijkstra(T from)
{

	typename std::vector<T>::iterator it1 = std::find(m_nodes.begin(), m_nodes.end(), from);

	if (it1 != m_nodes.end())
	{
		int src = distance(m_nodes.begin(), it1);

		std::vector<double> dist(m_edges.size());
		std::vector<int> lastNodes = vector::createVector(m_edges.size(), -1);

		std::vector<bool> sptSet(m_edges.size());
		for (int i = 0; i < m_edges.size(); i++)
			dist[i] = 10000000.0, sptSet[i] = false;

		dist[src] = 0;

		for (int count = 0; count < m_edges.size() - 1; count++) {
			int u = minDistance(dist, sptSet);

			sptSet[u] = true;

			for (int v = 0; v < m_edges.size(); v++) {
				if (!sptSet[v] && m_edges[u][v].first && dist[u] != 10000000.0 && dist[u] + m_edges[u][v].second < dist[v]) {

					dist[v] = dist[u] + m_edges[u][v].second;
					lastNodes[v] = u;
				}
			}
		}

		std::vector<std::triplet<T, T, double >> res;
		for (size_t i = 0; i < lastNodes.size(); i++)
		{
			res.push_back(std::make_triplet(m_nodes[i], m_nodes[lastNodes[i]], dist[i]));
			
		}

		return res;

	}
	else
	{
		return std::vector<std::triplet<T, T, double >>(0);
	}
}

template<typename T>
inline bool  Graph<T>::haveEdge(T from, T to)
{
	int i = getIndexInListNode(from);
	int j = getIndexInListNode(to);

	return m_edges[i][j].first;
}

template<typename T>
inline int Graph<T>::getIndexInListNode(T node)
{
	return vector::find(m_nodes, node);
}

template<typename T>
inline void Graph<T>::print()
{
	std::cout << "Nodes : " << std::endl;
	for (size_t i = 0; i < m_nodes.size(); i++)
	{
		std::cout << m_nodes[i] << std::endl;
	}

	std::cout << "edges : " << std::endl;

	for (size_t i = 0; i < m_edges.size(); i++)
	{
		for (size_t j = 0; j < m_edges[i].size(); j++)
		{
			if (m_edges[i][j].first)
				std::cout << m_nodes[i] <<" -> "<< m_nodes[j]<<" : "<< m_edges[i][j].second << std::endl;

		}
	}

}


template<typename T>
inline std::vector<T> Graph<T>::dijkstra(T from, T to)
{

	typename std::vector<T>::iterator it1 = std::find(m_nodes.begin(), m_nodes.end(), from);
	typename std::vector<T>::iterator it2 = std::find(m_nodes.begin(), m_nodes.end(), to);

	if (it1 != m_nodes.end() && it2 != m_nodes.end())
	{
		int src = distance(m_nodes.begin(), it1);
		int noeudDestinationId = distance(m_nodes.begin(), it2);

		std::vector<double> dist(m_edges.size());
		std::vector<int> lastNodes = vector::createVector(m_edges.size(), -1);

		std::vector<bool> sptSet(m_edges.size());
		for (int i = 0; i < m_edges.size(); i++)
			dist[i] = 10000000.0, sptSet[i] = false;

		dist[src] = 0;

		for (int count = 0; count < m_edges.size() - 1; count++) {
			int u = minDistance(dist, sptSet);

			sptSet[u] = true;

			for (int v = 0; v < m_edges.size(); v++) {
				if (!sptSet[v] && m_edges[u][v].first && dist[u] != 10000000.0 && dist[u] + m_edges[u][v].second < dist[v]) {
					dist[v] = dist[u] + m_edges[u][v].second;
					lastNodes[v] = u;
				}
			}
		}

		std::vector<T> res;
		int d = noeudDestinationId;

		res.push_back(m_nodes[d]);
		while (d != src)
		{
			d = lastNodes[d];
			res.push_back(m_nodes[d]);
		}


		return vector::reverse(res);

	}
	else
	{
		return std::vector<T>(0);
	}
}

template<typename T>
inline bool Graph<T>::bfs(std::vector<std::vector< std::pair<bool, double> >>rGraph, int s, int t, std::vector<int>& parent)
{
	std::vector<bool> visited = vector::createVector(m_nodes.size(), false);

	std::queue<int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	while (!q.empty())
	{
		int u = q.front();
		q.pop();

		for (int v = 0; v < m_nodes.size(); v++)
		{
			if (visited[v] == false && rGraph[u][v].first && rGraph[u][v].second > 0)
			{
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}

			else if (visited[v] == false && rGraph[v][u].first && rGraph[v][u].second < m_edges[v][u].second)
			{
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}
	return (visited[t] == true);
}

template<typename T>
inline std::pair<double, std::vector<std::vector< std::pair<bool, double> >> > Graph<T>::fordFulkerson(T source, T puit, std::vector<std::pair<std::pair<T, T>, double>> minConstraint)
{
	typename std::vector<T>::iterator it1 = std::find(m_nodes.begin(), m_nodes.end(), source);
	typename std::vector<T>::iterator it2 = std::find(m_nodes.begin(), m_nodes.end(), puit);

	std::vector < std::pair < std::pair<int, int>, double> > minConstraintIndexed;

	/*for (size_t i = 0; i < minConstraint.size(); i++)
	{
		int u = distance(minConstraint.begin(), std::find(m_nodes.begin(), m_nodes.end(), minConstraintIndexed[i].first.first));
		int v = distance(minConstraint.begin(), std::find(m_nodes.begin(), m_nodes.end(), minConstraintIndexed[i].first.second));
		minConstraintIndexed.push_back(std::make_pair(std::make_pair(u,v), minConstraint[i].second));
	}*/

	if (it1 != m_nodes.end() && it2 != m_nodes.end())
	{
		int s = distance(m_nodes.begin(), it1);
		int t = distance(m_nodes.begin(), it2);

		int u, v;
		std::vector<std::vector< std::pair<bool, double> >> rGraph = m_edges;

		std::vector<int> parent(m_nodes.size());
		double max_flow = 0;

		while (bfs(rGraph, s, t, parent))
		{
			double path_flow = INT_MAX;
			for (v = t; v != s; v = parent[v])
			{
				u = parent[v];
				path_flow = std::min(path_flow, rGraph[u][v].second);
			}
			for (v = t; v != s; v = parent[v])
			{
				u = parent[v];

				rGraph[u][v].second -= path_flow;
				rGraph[v][u].second += path_flow;
			}
			max_flow += path_flow;
		}


		return std::make_pair( max_flow, rGraph);
	}
	return std::make_pair(0, std::vector<std::vector< std::pair<bool, double> >>(0) );
	
}
template<typename T>
inline std::vector<T> Graph<T>::getAllNodes()
{
	return m_nodes;
}

template<typename T>
inline std::vector<std::vector< std::pair<bool, double> >> Graph<T>::getAllEdges()
{
	return m_edges;
}

template<typename T>
inline double Graph<T>::getDistance(std::vector<T> path)
{
	double res = 0;
	for (size_t i = 0; i < path.size() - 1; i++)
	{
		typename std::vector<T>::iterator it1 = std::find(m_nodes.begin(), m_nodes.end(), path[i]);
		typename std::vector<T>::iterator it2 = std::find(m_nodes.begin(), m_nodes.end(), path[i+1]);
		
		res += m_edges[distance(m_nodes.begin(), it1)][distance(m_nodes.begin(), it2)].second;
	}
	return res;
}


template<typename T>
inline bool Graph<T>::isConnexe()
{

	// on verifie que tout les noeud sont biens conectés à l'ensemble du graph


	// on crée un tableau de bool (marqueurs) initialisées à false
	std::vector<bool> m_nodesOk = vector::createVector(m_nodes.size(), false);
	
	// on fait un parcours en profondeur du graphe en partant du noeud 0
	// à chaques fois qu'on atteint un noeud, on note qu'il à été visité
	// si à la fin, des noeuds sont non visité, le graph n'est pas connexe

	std::queue<int> file;
	file.push(0);
	while (file.size() > 0)
	{
		int sommet = file.front();
		file.pop();
		m_nodesOk[sommet] = true;

		for (size_t i = 0; i < m_nodes.size(); i++)
		{
			// si le neoud n'est pas marqué et que l'arête entre sommet et i existe
			if (!m_nodesOk[i] && m_edges[sommet][i].first)
			{
				file.push(i);
				m_nodesOk[i] = true;
			}
		}
	}

	return vector::allAreEquals(m_nodesOk, true);
}