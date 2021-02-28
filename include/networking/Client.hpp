/**
 *  @file   Client.hpp
 *  @brief  Class that represents the client for networking
 *  @author Mike and van_doesnt_go
 *  @date   2020-13-04
 ***********************************************/
#ifndef APP_CLIENT_HPP
#define APP_CLIENT_HPP

#include <SFML/Network.hpp>
#include <iostream>
#include <cstring>

#include "AbstractNetworkManagerEntity.hpp"
#include "ClientMessageType.hpp"

/*! \brief Object for clients that are connected to the applicaiton.
 */
class Client : public AbstractNetworkManagerEntity {
private:
    //Member variables
    sf::UdpSocket* clientSocket;
    unsigned short clientPort;
    sf::IpAddress serverIp;
    unsigned short serverPort;

    // Member functions
    bool respondToServer(sf::IpAddress sIp, unsigned short sPort);

public:
    // Default constructor
    Client();
    // Copy constructor
    Client(const Client&);
    // Assignment operator
    Client& operator=(const Client&);
    explicit Client(unsigned short port);
    // Destructor
    ~Client() override;
    bool launch() override;

    sf::UdpSocket* getSocket() override;

    void joinServer(sf::IpAddress ipAddress, unsigned short sPort) override;
    sf::IpAddress getServerIp() override;
    unsigned short getServerPort() override;

};

#endif //APP_CLIENT_HPP
