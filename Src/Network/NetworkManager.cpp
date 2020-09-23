#include "NetworkManager.h"

// surcharge des operateur pour les envois dans les packet :
// surcharge lecture du protocole :
sf::Packet& operator >>(sf::Packet& packet, const Protocole& protocole)
{
	return packet >> protocole;
}


NetworkManager::NetworkManager()
{
}

NetworkManager::NetworkManager(sf::IpAddress addresse, unsigned short port):
	m_addresse(addresse),
	m_port(port),
	m_reconnect(false)
{
	m_runNetworkManager = true;
}

void NetworkManager::update()
{
	if (m_isConnected && !checkPing()) // si on est connect� et que le ping n'est pas verifi�
	{
		m_reconectIsEmitted = true;
		m_whaitBeforReconect.restart();
	}

	if (m_reconectIsEmitted)
	{
		if (m_whaitBeforReconect.getElapsedTime() > sf::seconds(3))
		{
			m_reconnect = true;
			m_reconectIsEmitted = false;
		}
	}

	if (m_reconnect){

		m_reconnect = false;
		run();
	}
	
}

void NetworkManager::run()
{
	m_thread_receveur = std::async(std::launch::async, &NetworkManager::receveur, this);
}

void NetworkManager::stop()
{
	m_runNetworkManager = false;
	m_tcpSoket.setBlocking(false);
	m_tcpSoket.disconnect();
}


void NetworkManager::validPing()
{
	if (m_isConnected == false)
	{
		std::cout << "Connection effectuee avec succ�s ! " << std::endl;
		// TODO � enlever !
		sf::sleep(sf::seconds(0.5));
		m_isConnected = true;
	}
	else
	{ // on r�pond au mesage de ping
		sendData(Protocole::PING);
	}
	m_checkConection.restart();
}

void NetworkManager::connect()
{
	std::cout << "conection en cours au serveur "<< m_addresse<<":"<< m_port <<" ..." << std::endl;
	m_tcpSoket.setBlocking(true);

	if (m_tcpSoket.connect(m_addresse, m_port) != sf::TcpSocket::Done)
	{
		std::cout << "erreur de connection !" << std::endl;
		std::cout << "nouvelle tentative de connection dans 3 secondes !" << std::endl;
		m_whaitBeforReconect.restart();
		m_reconectIsEmitted = true;
		m_runNetworkManager = false;
		m_isConnected = false;
		m_isAuthentified = false;
	}
	else 
	{
		std::cout << "Lancement du receveur " << std::endl;
		m_runNetworkManager = true;
	}
}

void NetworkManager::receveur()
{
	connect(); 
	while (m_runNetworkManager)
	{
		sf::Packet data;
		std::cout << "En attente d'un nouveau message ..." << std::endl;
		if (m_tcpSoket.receive(data) != sf::TcpSocket::Done)
		{
			// si erreur alors c'est que la socket a �t� ferm�e proprement
			stop();
		}
		else
		{
			std::cout << "message recu";
			int protocole;
			data >> protocole;

			std::cout << " (code : " << protocole << " )" << std::endl;


			if (protocole == Protocole::PING)
			{
				std::cout << "PING !" << std::endl;
				validPing();
			}
			else if (protocole == Protocole::I_AM_ADMIN)
			{
				// TODO � enlever !
				sf::sleep(sf::seconds(0.5));
				m_isAuthentified = true;
			}
			else if (protocole == Protocole::ALL_CLIENT_DATA)
			{
				setAllName(data);
			}
		}
	}
}

bool NetworkManager::isConnected()
{
	return m_isConnected;
}

bool NetworkManager::isAuthentified()
{
	return m_isAuthentified;
}

bool NetworkManager::checkPing()
{
	if (m_checkConection.getElapsedTime() > sf::seconds(3))
	{
		std::cout << "conection perdue, retentative de connection dans 3 secondes" << std::endl;
		
		m_whaitBeforReconect.restart();
		m_reconectIsEmitted = true;
		m_isConnected = false;
		m_runNetworkManager = false;
		m_isAuthentified = false;

		return false;
	}
	else return true;
}

void NetworkManager::setAllName(sf::Packet& p)
{
	unsigned int size;
	p >> size;

	for (size_t i = 0; i < size; i++)
	{
		std::string first, second;
		p >> first >> second;
		m_allName.push_back(std::make_pair(first,second));
	}
}

std::vector<std::pair<std::string, std::string>> NetworkManager::getAllName()
{
	return m_allName;
}

void NetworkManager::sendData(Protocole protocole)
{
	sf::Packet packet;
	packet << protocole;
	m_tcpSoket.send(packet);
}
