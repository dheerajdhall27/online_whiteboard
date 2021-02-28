/**
*  @file   Client.cpp
*  @brief  Class that represents the client for networking
*  @author Mike and and team van_doesnt_go
*  @date   2020-05-04
***********************************************/

#include <networking/Client.hpp>

/*! \brief     A default constructor to initialize all
            the variables of the Client entity.
*
*/
Client::Client() : clientPort(0), serverPort(0), serverIp(sf::IpAddress())  {
    clientSocket = new sf::UdpSocket();
}

/*! \brief     A copy constructor to make a copy of the existing instance of Client
*
*/
Client::Client(const Client& rhs) {
    clientSocket = new sf::UdpSocket();
    clientPort = rhs.clientPort;
    serverPort = rhs.serverPort;
    serverIp = rhs.serverIp;

}

/*! \brief     An assignment operator to assign one instance to another
*
*/
Client&  Client::operator=(const Client& rhs) {
    if (&rhs != this) {
        clientSocket = new sf::UdpSocket();
        clientPort = rhs.clientPort;
        serverPort = rhs.serverPort;
        serverIp = rhs.serverIp;
    }

    return *this;

}


/*! \brief     A default constructor to initialize all the variables of the Client entity.
*
*/
Client::Client(unsigned short port) : serverIp(sf::IpAddress()) , serverPort(0), clientPort(port)  {
    clientSocket = new sf::UdpSocket();
}

/*! \brief     Destructor to delete client socket
*
*/
Client::~Client() {
    delete clientSocket;
}

/*! \brief     Launches the clients and prompts for port input
*
*/
bool Client::launch() {
    std::cout << "============Initiating UDP Client==========" << std::endl;

    std::cout << "Enter Server IpAddress: ";
    std::cin >> serverIp;
    std::cout << "Enter Server Port Number: ";
    std::cin >> serverPort;
    std::cout << "Enter Client Port Number: ";
    std::cin >> clientPort;
    std::cout << "Confirming Port Number as: " << clientPort << std::endl;

    clientSocket->bind(clientPort);

    clientSocket->setBlocking(false);
    sf::Packet packetSend;

    packetSend << static_cast<int32_t > (ClientMessageType::CLIENT_JOINING);

    return respondToServer(serverIp, serverPort);
}

/*! \brief     Check if the client has connected or not
*
*/
bool Client::respondToServer(sf::IpAddress sIp, unsigned short sPort) {
    std::cout << "Server Port: " << sPort << std::endl;
    sf::Packet packetSend;
    packetSend << static_cast<int32_t > (ClientMessageType::CLIENT_JOINING);
    if(clientSocket->send(packetSend, sIp, sPort) != sf::Socket::Done){
        std::cout << "Client error? Wrong IP?" << std::endl;
    } else{
        std::cout << "Client connecting--awaiting server start" << std::endl;
        return true;
    }
    return false;

}

/*! \brief    Returns Client socket
*
*/
sf::UdpSocket* Client::getSocket() {
    return this->clientSocket;
}


/*! \brief     Sets server IP Address and port
*
*/
void Client::joinServer(sf::IpAddress ipAddress, unsigned short sPort) {
    serverIp = ipAddress;
    serverPort = sPort;
}

/*! \brief     Get server IP
*
*/
sf::IpAddress Client::getServerIp() {
    return serverIp;
}

/*! \brief     Get server port
*
*/
unsigned short Client::getServerPort() {
    return serverPort;
}




