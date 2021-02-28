/**
*  @file  AbstractNetworkManagerEntity.hpp
*  @brief  Abstract class for server and client entity to extend to
*  @author Mike and van_doesnt_go
*  @date    2020-04-05
***********************************************/

#ifndef ASSIGNMENT4_NETWORKING_ABSTRACTNETWORKMANAGERENTITY_HPP
#define ASSIGNMENT4_NETWORKING_ABSTRACTNETWORKMANAGERENTITY_HPP

#include <SFML/Network.hpp>

/*! \brief Abstract class for server and client entity to extend to
 *
 */
class AbstractNetworkManagerEntity {
    public:
        virtual bool launch() = 0;
        virtual sf::UdpSocket* getSocket() = 0;
        virtual ~AbstractNetworkManagerEntity() = default;
        virtual void joinServer(sf::IpAddress ipAddress, unsigned short serverPort){};

        virtual sf::IpAddress getServerIp(){};
        virtual unsigned short getServerPort(){};

};

#endif //ASSIGNMENT4_NETWORKING_ABSTRACTNETWORKMANAGERENTITY_HPP
