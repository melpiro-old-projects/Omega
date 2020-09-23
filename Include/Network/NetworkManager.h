#pragma once
#include <SFML/Network.hpp>
#include <future>
#include <iostream>
#include <vector>

#include "Protocole.h"

class NetworkManager
{
public:
	NetworkManager();
	NetworkManager(sf::IpAddress addresse, unsigned short port);

	void update();

	void run();
	void stop();

	template<typename T>
	void sendData(Protocole protocole, T data);

	template<typename T>
	void sendData(Protocole protocole, sf::Vector2<T> pair);

	template<typename T>
	void sendData(Protocole protocole, sf::Vector3<T> triplet);

	template<typename T, typename L>
	void sendData(Protocole protocole, std::pair<T, L> pair);
	template<typename T, typename L>
	void sendData(Protocole protocole, T first, L second);
	template<typename T, typename L, typename M>
	void sendData(Protocole protocole, T first, L second, M third);
	template<typename T, typename L, typename M, typename N>
	void sendData(Protocole protocole, T first, L second, M third, N quad);

	template<typename T>
	void sendData(Protocole protocole, std::vector<T> list);

	void sendData(Protocole protocole);

	bool isConnected();
	bool isAuthentified();

	bool checkPing();

	void setAllName(sf::Packet& p);
	std::vector<std::pair<std::string,std::string>> getAllName();

private:

	void validPing();

	void connect();
	void receveur();

	sf::TcpSocket m_tcpSoket;
	bool m_runNetworkManager;

	std::future<void> m_thread_receveur;

	sf::IpAddress m_addresse;
	unsigned short m_port;

	bool m_isConnected;

	sf::Clock m_checkConection;

	sf::Clock m_whaitBeforReconect;
	bool m_reconnect;
	bool m_reconectIsEmitted;
	
	bool m_isAuthentified;

	/////////////////////////////// DONNEE TRAITEE PAR LE RECEVEUR //////////////////////

	std::vector<std::pair<std::string, std::string>> m_allName;
};


#include "NetworkManager.ipp"