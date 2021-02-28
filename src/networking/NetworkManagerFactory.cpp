/**
*  @file   NetworkManagerFactory.cpp
*  @brief  Factory to create new servers and clients depending on the entity type input
*  @author Mike and and team van_doesnt_go
*  @date   2020-05-04
***********************************************/

#include "networking/NetworkManagerFactory.hpp"
#include "networking/Server.hpp"
#include "networking/Client.hpp"
#include <iostream>

/*! \brief     Factory to create new servers and clients depending on the entity type input
*/
AbstractNetworkManagerEntity* NetworkManagerFactory::makeNetworkEntity(NetworkEntityType networkEntityType) {

    switch (networkEntityType) {
        case SERVER:
            return new Server;
        case CLIENT:
            return new Client;
        default:
            return nullptr;
    }
}
