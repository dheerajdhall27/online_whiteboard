/**
*  @file   AppEventHandler.cpp
*  @brief  Implementation of AppEventHandler.hpp
*  @author Mike and team van_doesnt_go
*  @date   2020-08-04
***********************************************/

#include "AppEventHandler.hpp"

//Static Variable Initialization
BrushType AppEventHandler::brushType = BrushType::REGULAR;


/*! \brief     Creates and returns a map of a color corresponding to a Color enum
*
*/
std::map<int,sf::Color> AppEventHandler::getBrushColorMap(){
    std::map<int,sf::Color> brushColorMap = {{BLACK,sf::Color::Black},{WHITE,sf::Color::White}, {RED, sf::Color::Red},
                                             {GREEN,sf::Color::Green},{YELLOW,sf::Color::Yellow},{BLUE,sf::Color::Blue},
                                             {CYAN,sf::Color::Cyan},{MAGENTA,sf::Color::Magenta}};
    return brushColorMap;
}

/*! \brief     Creates and returns a map of a brush type corresponding to a keyboard input
*
*/
std::map<sf::Keyboard::Key, BrushType> AppEventHandler::getBrushTypeKeyMap(){
    std::map<sf::Keyboard::Key, BrushType> brushTypeKeyMap = {{sf::Keyboard::C,BrushType::CIRCLE_BRUSH},
                                                              {sf::Keyboard::H,BrushType::HEART_BRUSH},
                                                              {sf::Keyboard::S,BrushType::SPRAY_PAINT_BRUSH},
                                                              {sf::Keyboard::D,BrushType::DIAGONAL_LINE_BRUSH},
                                                              {sf::Keyboard::R,BrushType::RECT_BRUSH},
                                                              {sf::Keyboard::Q,BrushType::SQUARE_BRUSH},
                                                              {sf::Keyboard::U,BrushType::REGULAR}};
    return brushTypeKeyMap;
}

/*! \brief     Creates and returns a map of a brush type corresponding to a Brush Type enum
*
*/
std::map<int, BrushType> AppEventHandler::getBrushTypeMouseMap(){
    std::map<int, BrushType> brushTypeMouseMap = {{CIRCLE_BRUSH,BrushType::CIRCLE_BRUSH},
                                                  {HEART_BRUSH,BrushType::HEART_BRUSH},
                                                  {SPRAY_PAINT_BRUSH,BrushType::SPRAY_PAINT_BRUSH},
                                                  {DIAGONAL_LINE_BRUSH,BrushType::DIAGONAL_LINE_BRUSH},
                                                  {RECT_BRUSH,BrushType::RECT_BRUSH},
                                                  {SQUARE_BRUSH,BrushType::SQUARE_BRUSH},
                                                  {REGULAR,BrushType::REGULAR}};
    return brushTypeMouseMap;
}



/*! \brief     Runs the desired actions in the app based on a mouse pressed event.
                When the mouse is pressed it creates a command to draw with the color
                that is selected and sends that information to the client in a packet.
*
*/
void AppEventHandler::handleMouseEvents(App *app, GUI *gui, AbstractNetworkManagerEntity *clientEntity) {

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        sf::RenderWindow &window = app->GetWindow();
        sf::Vector2i coordinate = sf::Mouse::getPosition(window);

        sf::RenderWindow *guiWindow = gui->GetGuiWindow();
        sf::Vector2i guiCoords = sf::Mouse::getPosition(*guiWindow);

        if (guiCoords.x <= Global::WINDOW_WIDTH &&
            guiCoords.y <= Global::WINDOW_HEIGHT) {
            static int oldOp = -1;
            static int oldBrOp = -10;
            if (oldOp != GUI::op) {
                changeBrushColor(GUI::op, app, clientEntity);
                oldOp = GUI::op;
            }
            if (oldBrOp != GUI::br_op){
                changeBrushType(GUI::br_op, app, clientEntity);
                oldBrOp = GUI::br_op;
            }
        }

        app->setMouseX(coordinate.x);
        app->setMouseY(coordinate.y);
        app->AddCommand(createCommandWithBrushType(brushType, CommandDescription::LocalCommand, app));
	    app->ExecuteCommand();
        app->setPmouseX(app->getMouseX());
        app->setPmouseY(app->getMouseY());

        sf::Packet packetSend;
        DataPacket dataPacket(coordinate.x,
                              coordinate.y,
                              app->getCurrentBrushColor().toInteger(),
                              app->getCurrentCanvasColor().toInteger());
        mutex.lock();
        packetSend << static_cast<int32_t >(ClientMessageType::DRAW_INFORMATION) << dataPacket
                   << static_cast<int32_t >(brushType);
        mutex.unlock();
        clientEntity->getSocket()->send(packetSend, clientEntity->getServerIp(), clientEntity->getServerPort());
    }
}

/*! \brief     Runs the desired actions in the app based on a keyboard press.
                Escape closes the window, z sends an undo command to the server,
                y send a redo command. Number 1-8 change the color of the brush
                and space sets the background of the canvas equal to the current
                brush color.
*
*/
void AppEventHandler::handleKeyboardEvents(const sf::Event &event, App *app, AbstractNetworkManagerEntity *clientEntity) {
    handleBrushChange(event, app);
    if (event.type == sf::Event::KeyReleased) {

        if (event.key.code == sf::Keyboard::Escape) {
            app->GetWindow().close();
            exit(EXIT_SUCCESS);
        }

        if (event.key.code == sf::Keyboard::Z) {
            sf::Packet packetSend;
            mutex.lock();
            packetSend << static_cast<int32_t >(ClientMessageType::UNDO_COMMAND);
            mutex.unlock();
            clientEntity->getSocket()->send(packetSend, clientEntity->getServerIp(), clientEntity->getServerPort());
        }

        if (event.key.code == sf::Keyboard::Y) {
            sf::Packet packetSend;
            mutex.lock();
            packetSend << static_cast<int32_t >(ClientMessageType::REDO_COMMAND);
            mutex.unlock();
            clientEntity->getSocket()->send(packetSend, clientEntity->getServerIp(), clientEntity->getServerPort());
        }

        if (event.key.code >= Global::NUMBER_ONE_CODE && event.key.code <= Global::NUMBER_EIGHT_CODE) {
            std::cout << "Handled" << std::endl;
            changeBrushColor(event.key.code, app, clientEntity);
        } else if (event.key.code >= Global::NUMPAD_ONE_CODE && event.key.code <= Global::NUMPAD_EIGHT_CODE) {
            changeBrushColor(event.key.code - Global::NUMPAD_ONE_CODE + Global::NUMBER_ONE_CODE, app, clientEntity);
        }

        if (event.key.code == sf::Keyboard::Space) {
            app->GetImage().create(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT, app->getCurrentBrushColor());
            app->GetTexture().loadFromImage(app->GetImage());
            sf::Packet packetSend;
            mutex.lock();
            packetSend << static_cast<int32_t >(ClientMessageType::PAINT_CANVAS)
                       << app->getCurrentBrushColor().toInteger();
            mutex.unlock();
            clientEntity->getSocket()->send(packetSend, clientEntity->getServerIp(), clientEntity->getServerPort());
        }
    }
}

/*! \brief     Receives packets from the client, depending on the message received it
                either checks if the client is connected, draws on the canvas,
                resets the canvas background or changes the brush color.
*
*/
void AppEventHandler::handleIncomingPackets(App *app, AbstractNetworkManagerEntity *clientEntity) {
    sf::Packet receive;
    sf::Packet tempPacket;
    sf::IpAddress tempIp;

    try {
        unsigned short tempPort;
        if (clientEntity->getSocket()->receive(receive, tempIp, tempPort) == sf::Socket::Done) {
            int value;
            receive >> value;
            auto clientMessageType = (ClientMessageType) value;

            switch (clientMessageType) {
                case ClientMessageType::IS_CLIENT_ALIVE: {
                    clientEntity->getSocket()->send("Connected", 100, tempIp, tempPort);
                    break;
                }
                case ClientMessageType::DRAW_INFORMATION: {
                    DataPacket dp;
                    if (receive >> dp) {
                        int brushValue;
                        receive >> brushValue;
                        auto bType = (BrushType) brushValue;

                        app->setMouseX(dp.getMouseX());
                        app->setMouseY(dp.getMouseY());
                        app->setServerCurrentBrushColor(sf::Color(dp.getBrushColor()));
                        app->setCurrentCanvasColor(sf::Color(dp.getCanvasColor()));

                        app->AddCommand(createCommandWithBrushType(bType,
                                CommandDescription::ServerCommand, app));
                        app->ExecuteCommand();
                        app->setPmouseX(app->getMouseX());
                        app->setPmouseY(app->getMouseY());
                    }
                    break;
                }
                case ClientMessageType::PAINT_CANVAS: {
                    setCanvasColor(receive, app);
                    app->GetImage().create(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT, app->getCurrentCanvasColor());
                    app->GetTexture().loadFromImage(app->GetImage());
                    break;
                }
                case ClientMessageType::UNDO_COMMAND: {
                    app->UndoCommand();
                    break;
                }
                case ClientMessageType::REDO_COMMAND: {
                    app->ExecuteCommand();
                    break;
                }
                default:
                    break;
            }

        }
    } catch (...) {
        std::cout << "Error Receiving From Client" << std::endl;
    }
}

/*! \brief     Receives a color code and depending on the code it sets the brush color and the GUI brush button
*               to match the what the user wants.
*
*/
void AppEventHandler::changeBrushColor(int code, App *app, AbstractNetworkManagerEntity *clientEntity) {

    std::map<int,sf::Color>::iterator it;
    std::map<int,sf::Color> brushColorMap = getBrushColorMap();

    it = brushColorMap.find(code);
    if (it != brushColorMap.end()) {

        GUI::op = it->first;
        sf::Color bColor = it->second;
        app->setCurrentBrushColor(bColor);

    } else {
        std::cout << "Invalid choice entered! Try again!"  << std::endl;
    }

}

/*! \brief     Receives packet and sets brush color to the color value in the packet.
*
*/
void AppEventHandler::setCanvasColor(sf::Packet receive, App *app) {
    sf::Uint32 colorValue;
    receive >> colorValue;
    app->setCurrentCanvasColor(sf::Color(colorValue));
}

/*! \brief     This method  updates the brush type based on the Keypress
*
*/
void AppEventHandler::handleBrushChange(const sf::Event& event, App *app) {

    if (event.type == sf::Event::KeyReleased) {
        sf::Keyboard::Key keyCode = event.key.code;


        std::map<sf::Keyboard::Key, BrushType>::iterator it;
        std::map<sf::Keyboard::Key, BrushType> brushTypeKeyMap = AppEventHandler::getBrushTypeKeyMap();


        it = brushTypeKeyMap.find(keyCode);

        if (it != brushTypeKeyMap.end()) {
            BrushType bType = it->second;
            GUI::br_op = bType;
            brushType = bType;

        }

    }
}

/*! \brief     This method updates the brush type based on the button clicked in the GUI
 *
 */
void AppEventHandler::changeBrushType(int code, App *app, AbstractNetworkManagerEntity *clientEntity) {

    std::map<int,BrushType>::iterator it;
    std::map<int, BrushType> brushTypeMouseMap = getBrushTypeMouseMap();

    it = brushTypeMouseMap.find(code);
    if (it != brushTypeMouseMap.end()) {

        BrushType bType = it->second;
        GUI::br_op = bType;
        brushType = bType;

    } else {
        std::cout << "Invalid choice entered! Try again!"  << std::endl;
    }


}

/*! \brief This method creates the appropriate Brush Command based on the
*              current brush type.
*
*/
AbstractCommand *AppEventHandler::createCommandWithBrushType(BrushType bType, CommandDescription commandDescription,App* app) {
    switch (bType) {
        case REGULAR:
            return new DrawCommand(commandDescription, app);
        case SQUARE_BRUSH:
            return new DrawSquareCommand(commandDescription, app);
        case RECT_BRUSH:
            return new DrawRectCommand(commandDescription, app);
        case HEART_BRUSH:
            return new DrawHeartCommand(commandDescription, app);
        case DIAGONAL_LINE_BRUSH:
            return new DrawDiagonalLineCommand(commandDescription, app);
        case SPRAY_PAINT_BRUSH:
            return new DrawSprayPaintCommand(commandDescription, app);
        case CIRCLE_BRUSH:
            return new DrawCircleCommand(commandDescription, app);
    }
    return nullptr;
}
