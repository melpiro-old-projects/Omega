#pragma once
template<typename T>
void NetworkManager::sendData(Protocole protocole, T data)
{
	sf::Packet packet;
	packet << protocole;
	packet << data;
	m_tcpSoket.send(packet);
}

template<typename T>
void NetworkManager::sendData(Protocole protocole, sf::Vector2<T> pair)
{
	sf::Packet packet;
	packet << protocole;
	packet << pair.x;
	packet << pair.y;
	m_tcpSoket.send(packet);
}

template<typename T>
void NetworkManager::sendData(Protocole protocole, sf::Vector3<T> triplet)
{
	sf::Packet packet;
	packet << protocole;
	packet << triplet.x;
	packet << triplet.y;
	packet << triplet.z;
	m_tcpSoket.send(packet);
}

template<typename T, typename L>
void NetworkManager::sendData(Protocole protocole, std::pair<T, L> pair)
{
	sf::Packet packet;
	packet << protocole;
	packet << pair.first;
	packet << pair.second;
	m_tcpSoket.send(packet);
}

template<typename T, typename L>
void NetworkManager::sendData(Protocole protocole, T first, L second)
{
	sf::Packet packet;
	packet << protocole;
	packet << first;
	packet << second;
	m_tcpSoket.send(packet);
}

template<typename T, typename L, typename M>
void NetworkManager::sendData(Protocole protocole, T first, L second, M third)
{
	sf::Packet packet;
	packet << protocole;
	packet << first;
	packet << second;
	packet << third;
	m_tcpSoket.send(packet);
}

template<typename T, typename L, typename M, typename N>
void NetworkManager::sendData(Protocole protocole, T first, L second, M third, N quad)
{
	sf::Packet packet;
	packet << protocole;
	packet << first;
	packet << second;
	packet << third;
	packet << quad;
	m_tcpSoket.send(packet);
}


template<typename T>
void NetworkManager::sendData(Protocole protocole, std::vector<T> list)
{
	sf::Packet packet;
	packet << protocole;
	packet << list.size();
	for (size_t i = 0; i < list.size(); i++)
	{
		packet << list[i];
	}
	m_tcpSoket.send(packet);
}
