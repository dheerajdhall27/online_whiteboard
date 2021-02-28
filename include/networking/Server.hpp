/**
*  @file  Server.hpp
*  @brief  Object for the server entity that each client connects to
*  @author Mike and van_doesnt_go
*  @date   2020-04-08
***********************************************/

#ifndef APP_SERVER_HPP
#define APP_SERVER_HPP
#include <SFML/Network.hpp>
#include <iostream>
#include <cstring>
#include <vector>
#include <map>

#include "AbstractNetworkManagerEntity.hpp"
#include "ClientMessageType.hpp"

/*! \brief Object for the server entity that each client connects to.
 */
class Server : public AbstractNetworkManagerEntity {

private:
    sf::UdpSocket* serverSocket;
    std::map<unsigned short, sf::IpAddress> computerID;
    std::vector<sf::Packet>* globalCommandStructure;
    sf::IpAddress serverIp;
    unsigned short serverPort;

    void getPortInfoAndBind();

    void serverLoop();

    void updateEachClient(std::map<unsigned short, sf::IpAddress>::iterator ipIterator, sf::Packet packet);

    void handleIncomingMessage(ClientMessageType clientMessageType,
                               sf::Packet packetReceived = sf::Packet(),
                               sf::IpAddress ipAddress = sf::IpAddress(),
                               unsigned short port = 0);

public:
    Server();
    Server(const Server&);
    Server& operator=(const Server&);
    explicit Server(unsigned short port);
    ~Server() override;
    bool launch() override;
    sf::UdpSocket* getSocket() override;
    sf::IpAddress getServerIp() override;
    unsigned short getServerPort() override;

};



#endif //APP_SERVER_HPP

