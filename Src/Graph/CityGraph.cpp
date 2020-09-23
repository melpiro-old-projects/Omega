#include "CityGraph.h"

CityGraph::CityGraph()
{
}


void CityGraph::addNode(CityNode dataNode)
{
	// on fait une recherche dychotomique pour ins�rer le neud dans la liste des neud
	int inf = 0;
	int sup = m_nodes.size();
	int m = (int)((inf + sup) / 2);
	int lm = m;
	
	while (inf < sup )
	{
		if (dataNode.id < m_nodes[m]->id)
		{
			sup = m;
		}
		else
		{
			inf = m + 1;
		}
		lm = m;
		m = (int)((inf + sup) / 2);
	}

	
	if (m_nodes.size() > 0 && m != m_nodes.size() && m_nodes[m]->id == dataNode.id)
	{
		std::cout << "Error : node d�ja existant !" << std::endl;
		return;
	}

	m_nodes.insert(m_nodes.begin() + m, new CityNode(dataNode));


	// ensuite on cree la liste d'edges pour la liste d'adagacence
	m_edgesList.insert(m_edgesList.begin() + m, std::vector<CityEdge*>(0) );


}

void CityGraph::addEdges(CityEdge data)
{
	int indexFrom = findIndexNodeById(data.from->id);


	// update liste adjacence
	m_edgesList[indexFrom].push_back(new CityEdge(data));

}



void CityGraph::removeEdges(CityNode from, CityNode to, CityEdge data)
{
	int indexFrom = findIndexNodeByCityNode(from);
	int indexToInAdjList = findIndexInAdjListOfDest(indexFrom,to);


	if (indexFrom == -1 || indexToInAdjList == -1)
	{
		std::cout << "error : impossible de supprimer l'edges : noeud inexistant" << std::endl;
		return;
	}
	// on supprime dans la liste d'adjacence
	delete m_edgesList[indexFrom][indexToInAdjList];
	m_edgesList[indexFrom].erase(m_edgesList[indexFrom].begin() + indexToInAdjList);

	
}

void CityGraph::removeEdges(unsigned long long int idNodeFrom, unsigned long long int idNodeTo)
{
	int indexFrom = findIndexNodeById(idNodeFrom);
	int indexToInAdjList = findIndexInAdjListOfDest(indexFrom, idNodeTo);

	if (indexFrom == -1 || indexToInAdjList == -1)
	{
		std::cout << "error : impossible de supprimer l'edges, noeud inexistant" << std::endl;
		return;
	}
	// on supprime dans la liste d'adjacence
	delete m_edgesList[indexFrom][indexToInAdjList];
	m_edgesList[indexFrom].erase(m_edgesList[indexFrom].begin() + indexToInAdjList);

}

void CityGraph::speedRender()
{
	sf::RenderWindow m_fen(sf::VideoMode(1000,800), m_titleGraph);
	std::vector<sf::CircleShape> nodesRender;
	std::vector<sf::RectangleShape> edgesRender;

	double nodeRadius = 0.05;
	double edgesWidth = 0.01;
	double viewSpeed = 1;
	double zoom = 1;
	double zoomSpeed = 0.5;

	for (size_t i = 0; i < m_nodes.size(); i++)
	{
		sf::CircleShape c(nodeRadius);
		c.setOrigin(sf::Vector2f(nodeRadius, nodeRadius));
		c.setPosition(m_nodes[i]->x, -m_nodes[i]->y);
		c.setFillColor(sf::Color(110, 255, 110));
		nodesRender.push_back(c);

	}
	
	for (size_t i = 0; i < m_edgesList.size(); i++)
	{
		for (size_t j = 0; j < m_edgesList[i].size(); j++)
		{
			sf::RectangleShape rect;
			rect.setPosition(m_edgesList[i][j]->from->x, -m_edgesList[i][j]->from->y);
			rect.setFillColor(sf::Color(110, 110, 255));
			rect.setSize(sf::Vector2f(math::getDistance((sf::Vector2f)sf::Vector2f(m_edgesList[i][j]->from->x, -m_edgesList[i][j]->from->y),
				(sf::Vector2f)sf::Vector2f(m_edgesList[i][j]->to->x, -m_edgesList[i][j]->to->y)), edgesWidth));

			rect.setRotation(math::getAngleDeg((sf::Vector2f)sf::Vector2f(m_edgesList[i][j]->from->x, -m_edgesList[i][j]->from->y),
				(sf::Vector2f)sf::Vector2f(m_edgesList[i][j]->to->x, -m_edgesList[i][j]->to->y)));

			edgesRender.push_back(rect);
		}
		
	}

	
	sf::View v = m_fen.getView();

	if (m_nodes.size()> 0)
		v.setCenter(m_nodes[0]->x, -m_nodes[0]->y);

	
	int step = 0;
	unsigned long long int idFrom=-1;
	unsigned long long int idTo = -1;

	while (m_fen.isOpen())
	{
		// event
		sf::Event e;
		while (m_fen.pollEvent(e))
		{
			if (e.type == sf::Event::Closed) m_fen.close();
			
			if (e.type == sf::Event::MouseWheelMoved)
			{
				if (e.mouseWheel.delta > 0) v.zoom(zoomSpeed), zoom*=zoomSpeed;
				else v.zoom(1.0/zoomSpeed), zoom /= zoomSpeed;
			}


			if (e.type == sf::Event::MouseButtonReleased)
			{
				for (size_t i = 0; i < nodesRender.size(); i++)
				{
					//std::cout << m_fen.mapCoordsToPixel(nodesRender[i].getPosition()).x <<" "<< m_fen.mapCoordsToPixel(nodesRender[i].getPosition()).y << " - " << sf::Mouse::getPosition(m_fen).x << " " << sf::Mouse::getPosition(m_fen).y << std::endl;
					if (math::getDistance(sf::Vector2f(m_fen.mapCoordsToPixel(nodesRender[i].getPosition())), sf::Vector2f(sf::Mouse::getPosition(m_fen))) < nodeRadius / zoom)
					{
						if (step == 0)
						{
							for (size_t i = 0; i < nodesRender.size(); i++)
							{
								nodesRender[i].setFillColor(sf::Color(110, 255, 110));
							}

							idFrom = m_nodes[i]->id;
							step++;
						}
						else if (step == 1)
						{
							idTo = m_nodes[i]->id;
							std::vector <CityNode*> path = node_dijkstra(idFrom, idTo);

							for (size_t i = 0; i < path.size(); i++)
							{
								nodesRender[findIndexNodeByCityNode(*path[i])].setFillColor(sf::Color(255, 0, 255));
							}

							step = 0;
						}
					}
				}
			}
		}

		// updates
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) v.move(0,-viewSpeed * zoom);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) v.move(0, viewSpeed * zoom);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) v.move(-viewSpeed * zoom, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) v.move(viewSpeed * zoom, 0);

		m_fen.setView(v);

		// draw
		m_fen.clear(sf::Color(19, 19, 19));
		for (size_t i = 0; i < edgesRender.size(); i++)
		{
			m_fen.draw(edgesRender[i]);
		}
		for (size_t i = 0; i < nodesRender.size(); i++)
		{
			m_fen.draw(nodesRender[i]);
		}

		m_fen.display();
	}
}

double CityGraph::minDistance()
{
	double min = INT8_MAX;
	double min_index;

	for (int v = 0; v < m_nodes.size(); v++)
		if (m_nodes[v]->dijkstra_isVisited == false && m_nodes[v]->dijkstra_distance< min)
			min = m_nodes[v]->dijkstra_distance, min_index = v;

	return min_index;
}




std::vector<std::pair<CityNode*, double>> CityGraph::node_dijkstra(int idNodeFrom)
{
	int indexFrom = findIndexNodeById(idNodeFrom);

	if (indexFrom != -1)
	{

		for (int i = 0; i < m_nodes.size(); i++)
			m_nodes[i]->dijkstra_lastNode = nullptr,
			m_nodes[i]->dijkstra_distance = 10000000.0, 
			m_nodes[i]->dijkstra_isVisited = false;

		m_nodes[indexFrom]->dijkstra_distance = 0;

		for (int count = 0; count < m_nodes.size() - 1; count++) {
			int u = minDistance();

			m_nodes[u]->dijkstra_isVisited = true;

			// pour tout les adj au node u :
			for (int v = 0; v < m_edgesList[u].size(); v++) {
				// si le neud est non vist�
				// et que sa distance n'est pas infinie
				// et que la distance de ce noeud est plus petite que sa distance qu'on a deja calculer
				if (!m_edgesList[u][v]->to->dijkstra_isVisited && m_nodes[u]->dijkstra_distance != 10000000.0 && m_nodes[u]->dijkstra_distance + m_edgesList[u][v]->distance + m_edgesList[u][v]->addedWeight < m_edgesList[u][v]->to->dijkstra_distance) {

					// alors il est plus proche
					m_edgesList[u][v]->to->dijkstra_distance = m_nodes[u]->dijkstra_distance + m_edgesList[u][v]->distance + m_edgesList[u][v]->addedWeight;
					m_edgesList[u][v]->to = m_nodes[u];
				}
			}
		}


		std::vector<std::pair<CityNode*, double>> res;
		for (size_t i = 0; i < m_nodes.size(); i++)
		{
			if (m_nodes[i]->dijkstra_lastNode != nullptr)
				res.push_back(std::make_pair(m_nodes[i]->dijkstra_lastNode, m_nodes[i]->dijkstra_distance));
		}

		return res;

	}
	else
	{
		return std::vector<std::pair<CityNode*, double>>(0);
	}
}

std::vector<CityNode*> CityGraph::node_dijkstra(unsigned long long int idNodeFrom, unsigned long long int idNodeTo)
{

	int indexFrom = findIndexNodeById(idNodeFrom);
	int indexTo = findIndexNodeById(idNodeTo);

	if (indexFrom != -1, indexTo != -1)
	{

		for (int i = 0; i < m_nodes.size(); i++)
			m_nodes[i]->dijkstra_lastNode = nullptr,
			m_nodes[i]->dijkstra_distance = 10000000.0,
			m_nodes[i]->dijkstra_isVisited = false;

		m_nodes[indexFrom]->dijkstra_distance = 0;

		for (int count = 0; count < m_nodes.size(); count++) {
			int u = minDistance();

			m_nodes[u]->dijkstra_isVisited = true;

			// pour tout les adj au node u :
			for (int v = 0; v < m_edgesList[u].size(); v++) {
				// si le neud est non vist�
				// et que sa distance n'est pas infinie
				// et que la distance de ce noeud est plus petite que sa distance qu'on a deja calculer
				if (!m_edgesList[u][v]->to->dijkstra_isVisited && m_nodes[u]->dijkstra_distance != 10000000.0 && m_nodes[u]->dijkstra_distance + m_edgesList[u][v]->distance + m_edgesList[u][v]->addedWeight < m_edgesList[u][v]->to->dijkstra_distance) {

					// alors il est plus proche
					m_edgesList[u][v]->to->dijkstra_distance = m_nodes[u]->dijkstra_distance + m_edgesList[u][v]->distance + m_edgesList[u][v]->addedWeight;
					m_edgesList[u][v]->to->dijkstra_lastNode = m_nodes[u];
					
				}
			}
		}

		std::vector<CityNode*> res;
		CityNode* nodeFrom = m_nodes[indexFrom];
		CityNode* nodeActu = m_nodes[indexTo];
		res.push_back(nodeActu);


		while (nodeActu->id != nodeFrom->id)
		{
			if (nodeActu->dijkstra_lastNode != nullptr)
			{
				nodeActu = nodeActu->dijkstra_lastNode;
				res.push_back(nodeActu);
			}
			else
			{
				std::cout << "Alert : pas de chemin trouv� !" << std::endl;
				return vector::reverse(res);
			}
		}

		return vector::reverse(res);

	}
	else
	{
		return std::vector<CityNode*>(0);
	}
}

std::vector<std::pair<CityNode*, double>> CityGraph::node_dijkstra(CityNode from)
{
	return node_dijkstra(findIndexNodeByCityNode(from));
}

std::vector<CityNode*> CityGraph::node_dijkstra(CityNode from, CityNode to)
{
	return node_dijkstra(findIndexNodeByCityNode(from), findIndexNodeByCityNode(to));
}


std::vector<CityNode*> CityGraph::getAllNodes()
{
	return m_nodes;
}

CityNode* CityGraph::getNode(unsigned long long int indexNode)
{
	return m_nodes[indexNode];
}

CityEdge* CityGraph::getEdge(unsigned long long int indexFrom, unsigned long long int indexTo)
{
	return m_edgesList[indexFrom][findIndexInAdjListOfDest(indexFrom,*m_nodes[indexFrom])];
}




std::vector<CityEdge*> CityGraph::getAllEdgesFrom(CityNode from)
{
	return getAllEdgesFrom(from.id);
}

std::vector<CityEdge*> CityGraph::getAllEdgesFrom(unsigned long long int idNodeFrom)
{
	int index = findIndexNodeById(idNodeFrom);
	return m_edgesList[index];
}



void CityGraph::loadPythonGraph(std::string name)
{
	// TODOOOOOOOOOOOOO
	// Py_Initialize();

	

	// std::string code = "";
	// code += "import osmnx as ox\n";
	// code += "G = ox.graph_from_place('" + name + "')\n";
	// code += "ox.save_graphml(G, filename = '" + name + "')";
	
	// std::cout << "telechragement du graph ..." ;
	// PyRun_SimpleString(code.c_str());
	// std::cout << " OK" << std::endl;


	// Py_Finalize();

}

void CityGraph::loadFromXmlFile(std::string path)
{
	///////////////////////////////////////////////////////////////:
	// �tape 1 : lecture du super fichier sa m�re
	std::cout << "Lecture en cours du fichier ... ";
	std::vector<std::string> allLines = file::getAllLines(path);
	std::cout << "OK" << std::endl;

	// map des key repr�sentatives du graph
	// ex : d5 -> x
	std::map<std::string, std::string> allKeyValue;


	///////////////////////////////////////////////////////////////:
	// �tape 2 : parsage des key !
	std::cout << "parsage des key id ... ";

	// on commence par lire la partie des key
	// cette partie commence � la ligne 3
	int ligne = 3;
	while (allLines[ligne].substr(2, 4) == "<key")
	{
		// on lit la ligne pour r�cup�rer le nom de l'id:
		std::string id = parcer::getValueOfAttributXML(allLines[ligne], "id");
		std::string name = parcer::getValueOfAttributXML(allLines[ligne], "attr.name");
		allKeyValue[id] = name;
		ligne++;
	}
	std::cout << "OK" << std::endl;

	std::cout << "parsage des nodes ... ";


	// on avance dans le fichier tant qu'on trouve pas de balise node
	while (allLines[ligne].substr(4, 5) != "<node") ligne++;

	///////////////////////////////////////////////////////////////:
	// �tape 3 : parsage des nodes

	// la premi�re map contient toutes les valeurs du node
	// la deuxi�me (dans la premi�re) est une liste de valeurs
	// qui contient les coordon�e x, y et plein d'autres trucs
	std::map<std::string, std::map<std::string, std::string>> allNodes;

	while (allLines[ligne].substr(4, 5) == "<node")
	{
		std::string id = parcer::getValueOfAttributXML(allLines[ligne], "id");

		ligne++;
		std::map<std::string, std::string> dataForThisNode;
		// tant que on atteint pas la balise de node fermante, on lis le bordel
		while (allLines[ligne].substr(4, 6) != "</node")
		{
			std::string key = parcer::getValueOfAttributXML(allLines[ligne], "key");

			// l'attribut d'id n'est pa n�c�ssaire car il est deja en cl� donc pas besoin de le r� enregistrer
			if (allKeyValue[key] != "osmid")
			{
				dataForThisNode[allKeyValue[key]] = parcer::getValueOfBaliseXML(allLines[ligne]);

			}

			ligne++;
		}
		
		allNodes[id] = dataForThisNode;
		ligne++;
	}
	std::cout << "OK" << std::endl;

	std::cout << "ligne actuelle : "<< ligne << std::endl;

	std::cout << "parsage des edge ... ";
	///////////////////////////////////////////////////////////////:
	// �tape 4 : parsage des edge

	// la premi�re map contient toutes les valeurs du edge
	// la deuxi�me (dans la premi�re) est une liste de valeurs
	// qui contient les coordon�e x, y et plein d'autres trucs
	std::map<std::string, std::map<std::string, std::string>> allEdges;

	while (allLines[ligne].substr(4, 5) == "<edge")
	{
		std::map<std::string, std::string> dataForThisNode;

		dataForThisNode["source"] = parcer::getValueOfAttributXML(allLines[ligne], "source");
		dataForThisNode["target"] = parcer::getValueOfAttributXML(allLines[ligne], "target");

		std::string id = dataForThisNode["source"] + dataForThisNode["target"];

		ligne++;
		// tant que on atteint pas la balise de node fermante, on lis le bordel
		while (allLines[ligne].substr(4, 6) != "</edge")
		{
			std::string key = parcer::getValueOfAttributXML(allLines[ligne], "key");

			if (allKeyValue[key] != "osmid")
			{
				dataForThisNode[allKeyValue[key]] = parcer::getValueOfBaliseXML(allLines[ligne]);

			}
			ligne++;
		}

		allEdges[id] = dataForThisNode;
		ligne++;
	}
	std::cout << "OK" << std::endl;

	std::cout << "ligne actuelle : " << ligne << std::endl;

	ligne++;
	std::cout << "Parsages des donn�e compl�mentaires ... ";
	m_titleGraph = parcer::getValueOfBaliseXML(allLines[ligne]);
	std::cout << "OK" << std::endl;

	std::cout << "Conversion des donn�e pour les nodes ... ";

	std::map<std::string, std::map<std::string, std::string>>::iterator it = allNodes.begin();

	int i = 0;
	for (it; it != allNodes.end(); it++)
	{
		CityNode cityNode;
		std::map<std::string, std::string>::iterator jt = it->second.begin();
		cityNode.id = atof(it->first.c_str());
		for (jt; jt != it->second.end(); jt++)
		{
			if (jt->first == "x")
			{
				cityNode.x = atof(jt->second.c_str()) * 600.0;
			}
			else if (jt->first == "y")
			{
				cityNode.y = atof(jt->second.c_str()) * 600.0;
			}
			else if (jt->first == "highway")
			{
				cityNode.highway = jt->second.c_str();
			}
			else if (jt->first == "ref")
			{
				cityNode.ref = jt->second.c_str();
			}
		}
		this->addNode(cityNode);
		i++;
		//std::cout << i << "/" << allNodes.size() << std::endl;
	}
	std::cout << "OK" << std::endl;

	std::cout << "Verification des donnees ... ";
	bool ok = true;
	for (size_t i = 1; i < m_nodes.size(); i++)
	{
		if (m_nodes[i - 1]->id > m_nodes[i]->id)
		{

			std::cout << "Error with node at id "<<i<<", id last node : "<< m_nodes[i-1]->id <<" > id : "<< m_nodes[i]->id << std::endl;
			ok = false;
			break;
		}
	}
	if (ok) std::cout << "OK" << std::endl;

	std::cout << "Conversion des donn�e pour les edges ... ";

	it = allEdges.begin();
	for (it; it != allEdges.end(); it++)
	{
		CityEdge cityEdge;

		std::map<std::string, std::string>::iterator jt = it->second.begin();
		for (jt; jt != it->second.end(); jt++)
		{
			if (jt->first == "source")
			{
				cityEdge.from = findNodeById( atof(jt->second.c_str()) );
			}
			else if (jt->first == "target")
			{
				cityEdge.to = findNodeById(atof(jt->second.c_str()));
			}
			else if (jt->first == "length")
			{
				cityEdge.distance = atof(jt->second.c_str());
			}
		}
		this->addEdges(cityEdge);
		i++;
	}

	std::cout << "OK" << std::endl;

	this->speedRender();

	
}

void CityGraph::createFor(std::string name)
{
	loadPythonGraph(name);
	loadFromXmlFile(name);
}

int CityGraph::findIndexNodeById(unsigned long long int id)
{
	int inf = 0;
	int sup = m_nodes.size() - 1;
	int m = (int)((inf + sup) / 2);

	while (m_nodes[m]->id != id && inf < sup)
	{
		if (id < m_nodes[m]->id)
		{
			sup = m - 1;
		}
		else
		{
			inf = m + 1;
		}

		m = (int)((inf + sup) / 2);
	}

	if (m_nodes[m]->id == id)
	{
		return m;
	}

	std::cout << "nop : " << id << std::endl;
	print::print(m_nodes);

	return -1;
}


int CityGraph::findIndexNodeByCityNode(CityNode node)
{
	return findIndexNodeById(node.id);
}

CityNode* CityGraph::findNodeById(unsigned long long int id)
{

	int inf = 0;
	int sup = m_nodes.size() - 1;
	int m = (int)((inf + sup) / 2);


	while (m_nodes[m]->id != id && inf < sup)
	{
		if (id < m_nodes[m]->id)
		{
			sup = m - 1;
		}
		else
		{
			inf = m + 1;
		}

		m = (int)((inf + sup) / 2);
	}

	if ( m_nodes[m]->id == id)
	{
		return m_nodes[m];
	}
	
	std::cout << "nop : "<< id<<std::endl;
	print::print(m_nodes);


	return nullptr;
}

CityNode* CityGraph::findNodeByCityNode(CityNode node)
{
	return findNodeById(node.id);
}

int CityGraph::findIndexInAdjListOfDest(unsigned long long int indexNodeFrom, CityNode to)
{
	return findIndexInAdjListOfDest(indexNodeFrom, to.id);
}

int CityGraph::findIndexInAdjListOfDest(unsigned long long int indexNodeFrom, unsigned long long int to)
{
	for (size_t i = 0; i < m_edgesList[indexNodeFrom].size(); i++)
	{
		if (m_edgesList[indexNodeFrom][i]->to->id == to) return i;
	}
	return -1;
}

void CityGraph::setAddedWeightOnEdge(CityNode from, CityNode to, double value)
{
	setAddedWeightOnEdge(from.id, to.id, value);
}

void CityGraph::setAddedWeightOnEdge(unsigned long long int idNodeFrom, unsigned long long int idNodeTo, double value)
{
	int indexInList = findIndexNodeById(idNodeFrom);
	int indexInAdjList = findIndexInAdjListOfDest(idNodeFrom, indexInAdjList);

	if (indexInList != -1 && indexInAdjList != -1)
	{
		m_edgesList[indexInList][indexInAdjList]->addedWeight = value;
	}
	else
	{
		std::cout << "error edge not found !" << std::endl;
	}
}

