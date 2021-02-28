/**
*  @file   NetworkManagerFactory.hpp
*  @brief  A factory for creating network managers
*  @author Mike and van_doesnt_go
*  @date   2020 - 04 - 13
***********************************************/
#ifndef APP_NETWORKMANAGERFACTORY_HPP
#define APP_NETWORKMANAGERFACTORY_HPP

#include "AbstractNetworkManagerEntity.hpp"
#include "NetworkEntityType.hpp"

/*! \brief A factory for creating network managers
 */
class NetworkManagerFactory {
    public:
        static AbstractNetworkManagerEntity* makeNetworkEntity(NetworkEntityType networkEntityType);
};

#endif //APP_NETWORKMANAGERFACTORY_HPP
