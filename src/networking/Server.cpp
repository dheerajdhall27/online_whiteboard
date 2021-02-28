/**
*  @file   Server.cpp
*  @brief  Constructs the Server and initializes the member variables
*  @author Mike and and team van_doesnt_go
*  @date   2020-05-04
***********************************************/

#include "networking/Server.hpp"

/*! \brief     Constructs the Server and initializes the member variables
*
*/
Server::Server() : serverPort(0) {
    serverSocket = new sf::UdpSocket();
    globalCommandStructure = new std::vector<sf::Packet>();
}

/*! \brief     A copy constructor to make a copy of the existing instance of Server
*
*/
Server::Server(const Server& rhs) : serverPort(rhs.serverPort), serverIp(rhs.serverIp){
    serverSocket = new sf::UdpSocket();

    globalCommandStructure = new std::vector<sf::Packet>();
}

/*! \brief     An assignment operator to assign one instance to another
*
*/
Server& Server::operator=(const Server& rhs)  {
    if (&rhs != this) {

        serverSocket = new sf::UdpSocket();
        serverPort = rhs.serverPort;
        serverIp = rhs.serverIp;
        globalCommandStructure = new std::vector<sf::Packet>();
    }

    return *this;

}

/*! \brief     Constructs the Server and initializes the member variables
 *             sets the port value to the value passed.
*
*/
Server::Server(unsigned short port) : serverIp(sf::IpAddress::getLocalAddress()), serverPort(port)  {
    serverSocket= new sf::UdpSocket;

    globalCommandStructure = new std::vector<sf::Packet>();
}

/*! \brief     Destructor the deletes the server socket
*
*/
Server::~Server() {
    delete globalCommandStructure;
    delete serverSocket;
}

/*! \brief     Gets port input from the user and starts binding
*
*/
void Server::getPortInfoAndBind() {
    if(serverPort == 0) {
        std::cout << "Set port number: ";
        std::cin >> serverPort;
        std::cout << "Enter Server IpAddress: ";
        std::cin >> serverIp;
    }
    std::cout << "Confirming server port number as: " << serverPort << std::endl;

    // Listening to a port
    serverSocket->bind(serverPort);

    serverSocket->setBlocking(true);
}

/*! \brief     Returns the IP Address of the server
*
*/
sf::IpAddress Server::getServerIp(){
    return serverIp;
}

/*! \brief     Returns the port number of the server
*
*/
unsigned short Server::getServerPort() {
    return serverPort;
}

/*! \brief     Main event loop for server receiving incoming packets
*
*/
void Server::serverLoop() {
    sf::SocketSelector selector;
    selector.add(*serverSocket);

    while(true) {
        sf::Packet packetReceived;
        sf::IpAddress tempIp;


        try {
            if(selector.wait(sf::seconds(1.0f))) {
                unsigned short tempPort;
                if(serverSocket->receive(packetReceived, tempIp, tempPort) == sf::Socket::Done) {
                    int value;
                    packetReceived  >> value;
                    ClientMessageType  clientMessageType = (ClientMessageType) value;

                    handleIncomingMessage(clientMessageType, packetReceived, tempIp, tempPort);
                }
            } else {
                handleIncomingMessage(ClientMessageType::IS_CLIENT_ALIVE);
            }
        } catch(...){
            std::cout << "Server Loop Could not receive data" << std::endl;
        }
    }
}


/*! \brief     Launches the server and waits for clients
*
*/
bool Server::launch() {
    // A map data structure stores all of the client connections to the server.

    getPortInfoAndBind();

    std::cout << "\nUDP Server Launched waiting for clients" << std::endl;

    serverLoop();

    return true;
}

/*! \brief     Returns the current socket.
*/
sf::UdpSocket* Server::getSocket() {
    return this->serverSocket;
}

/*! \brief     Receives incoming message from client to update the window in some way and sends
*               the request to update all client windows with the requested message (client joining,
*               draw information, redo, undo, is client alive, paint canvas, change brush color)
*
*/
void Server::handleIncomingMessage(ClientMessageType clientMessageType,
                           sf::Packet packetReceived,
                           sf::IpAddress ipAddress,
                           unsigned short port) {
    sf::SocketSelector selector;
    selector.add(*serverSocket);

    std::map<unsigned short, sf::IpAddress>::iterator ipIterator;

    try {
        switch(clientMessageType) {
            case ClientMessageType::CLIENT_JOINING:
            {
                std::cout << "Client with Port : " << port << " Joined" << std::endl;
                computerID[port] = ipAddress;

                if(!globalCommandStructure->empty()) {
                    std::vector<sf::Packet>::iterator iterator;
                    iterator = globalCommandStructure->begin();
                    while(iterator != globalCommandStructure->end()) {
                        selector.wait(sf::seconds(0.02f));
                        serverSocket->send(*iterator, ipAddress, port);
                        ++iterator;
                    }
                }
                break;
            }
            case ClientMessageType::DRAW_INFORMATION:
            {
                globalCommandStructure->push_back(packetReceived);
                for(ipIterator = computerID.begin(); ipIterator != computerID.end(); ++ipIterator){
                    if (ipIterator->first != port) {
                        serverSocket->send(packetReceived, ipIterator->second, ipIterator->first);
                    }
                }
                break;
            }
            case ClientMessageType::IS_CLIENT_ALIVE:
            {
                if(computerID.empty()) {
                    break;
                }
                sf::Packet receivedPacket;
                sf::Packet packetSend;
                packetSend << static_cast<int32_t >(ClientMessageType::IS_CLIENT_ALIVE);

                std::vector<unsigned int> portVector;
                for(ipIterator = computerID.begin(); ipIterator != computerID.end(); ++ipIterator) {
                    serverSocket->send(packetSend, ipIterator->second, ipIterator->first);
                    unsigned short tempPort = ipIterator->first;
                    try {
                        if(selector.wait(sf::seconds(3.0f))) {
                            if(serverSocket->receive(receivedPacket, ipIterator->second, tempPort) == sf::Socket::Done) {
                            }
                        } else {
                            std::cout << "Could Not Receive Packets Maybe Client Left?" << std::endl;
                            portVector.push_back(ipIterator->first);
                        }
                    } catch(...) {
                        std::cout << "Error Referencing Client! Client left possibly?" << std::endl;
                    }
                }
                std::vector<unsigned int>::iterator iterator;
                for(iterator = portVector.begin(); iterator != portVector.end();++iterator){
                    computerID.erase(*iterator);
                }
                break;
            }
            case ClientMessageType::REDO_COMMAND:
            case ClientMessageType::UNDO_COMMAND:
            {
                updateEachClient(ipIterator, packetReceived);
                break;
            }
            case ClientMessageType::PAINT_CANVAS:
            {
                globalCommandStructure->push_back(packetReceived);
                updateEachClient(ipIterator, packetReceived);
                break;

            }
            default:
                break;
        }
    } catch(...) {
        std::cout << "Error Sending information to clients" << std::endl;
    }
}

/*! \brief     Updates all client windows with the change that was made
*
*/
void Server::updateEachClient(std::map<unsigned short, sf::IpAddress>::iterator ipIterator, sf::Packet packet) {
    for(ipIterator = computerID.begin(); ipIterator != computerID.end(); ++ipIterator) {
        serverSocket->send(packet, ipIterator->second, ipIterator->first);
    }
}


