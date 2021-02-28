/**
*  @file  AppEventHandler.hpp
*  @brief  EventHandler object, used for handling keyboard and mouse input and other events
*  @author Mike and Van_doesnt_go
*  @date   2020-April- 10
***********************************************/

#ifndef APP_APPEVENTHANDLER_HPP
#define APP_APPEVENTHANDLER_HPP

// includ
#include <SFML/Network.hpp>
#include <iostream>
#include <networking/ClientMessageType.hpp>

#include <App.hpp>
#include <Global.hpp>
#include <networking/AbstractNetworkManagerEntity.hpp>
#include <command/DrawCommand.hpp>
#include <command/DrawDiagonalLineCommand.hpp>
#include <command/DataPacket.hpp>
#include <command/DrawHeartCommand.hpp>
#include <command/DrawSquareCommand.hpp>
#include <command/DrawSprayPaintCommand.hpp>
#include <command/DrawRectCommand.hpp>
#include <command/DrawCircleCommand.hpp>
#include <gui/GUI.hpp>
#include <command/CommandDescription.hpp>
#include <command/BrushType.hpp>

/*! \brief  EventHandler object, used for handling keyboard and mouse input and other events
 *          happening inside the App
 */
class AppEventHandler {
    private:
        // Member variables
        sf::Mutex mutex;
        static BrushType brushType;
        static std::map<int,sf::Color> getBrushColorMap();
        static std::map<sf::Keyboard::Key, BrushType> getBrushTypeKeyMap();
        static std::map<int, BrushType> getBrushTypeMouseMap();

        // Member functions
        void changeBrushColor(int code, App *app, AbstractNetworkManagerEntity *clientEntity);
        void changeBrushType(int code, App* app, AbstractNetworkManagerEntity *clientEntity);
        static void setCanvasColor(sf::Packet receive, App* app);
        static void handleBrushChange(const sf::Event& event, App *app);
        static AbstractCommand* createCommandWithBrushType(BrushType bType, CommandDescription commandDescription,
                App *app);

    public:

        void handleKeyboardEvents(const sf::Event& event, App *app, AbstractNetworkManagerEntity *clientEntity);
        void handleMouseEvents(App *app, GUI* gui, AbstractNetworkManagerEntity *clientEntity);
        static void handleIncomingPackets(App *app, AbstractNetworkManagerEntity *clientEntity);
};

#endif //APP_APPEVENTHANDLER_HPP
