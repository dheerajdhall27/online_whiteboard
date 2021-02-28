/**
 *  @file   main_test.cpp 
 *  @brief  Unit Tests for our program
 *  @author Mike and ???? 
 *  @date   yyyy-dd-mm 
 ***********************************************/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
// Include standard library C++ libraries.
#include <iostream>
#include <string>
#include <Global.hpp>
#include <networking/ClientMessageType.hpp>
#include <networking/Client.hpp>
#include <networking/Server.hpp>
#include <AppEventHandler.hpp>
// Project header files
#include "App.hpp"
#include "command/Command.hpp"
#include "command/DrawCommand.hpp"
#include "command/DrawDiagonalLineCommand.hpp"


void initialization(){
    std::cout << "Starting the App" << std::endl;
}
 
/*! \brief  Initialize and destroy the program
*       
*/
TEST_CASE("init and destroy"){
    App* app = new App();
    app->Init(&initialization);
    // Destroy our app
    app->Destroy();
}

/*! \brief 	Initialize the program and check the window color and Destroy the program
*
*/
TEST_CASE("init check color and destroy"){
    App app;
    app.Init(&initialization);

    sf::Image image = app.GetImage();

    sf::Vector2u windowVector =  image.getSize();
    for(int x = 0; x < windowVector.x; x++) {
        for(int y = 0; y < windowVector.y; y++) {
            REQUIRE(image.getPixel(x, y) == sf::Color::Black);
        }
    }

}


/*! \brief 	Initialize the program and check the window color and Destroy the program
*
*/
TEST_CASE("init color first line check first line and destroy") {
    App app;
    app.Init(&initialization);

    for(int x = 0; x < app.GetWindow().getSize().x; x++) {
        app.GetImage().setPixel(x, 0, sf::Color::Red);
    }

    sf::Image image= app.GetImage();
    for(int x = 0; x < app.GetWindow().getSize().x; x++) {
        REQUIRE(image.getPixel(x, 0) == sf::Color::Red);
    }

}

/*! \brief 	Initialize the program and check the window, texture and image are not null and destroy program
*
*/
TEST_CASE("init check for null and destroy") {
    App app;
    app.Init(&initialization);

    sf::RenderWindow* window = &app.GetWindow();
    sf::Texture* texture = &app.GetTexture();
    sf::Image* image = &app.GetImage();

    REQUIRE(window != nullptr);
    REQUIRE(texture != nullptr);
    REQUIRE(image != nullptr);

}


/*! \brief 	Initialize the program, draw using the diagonal line brush and check whether or not
*           the pixels are modified
*/

TEST_CASE("test new feature") {
    App app;
    app.Init(&initialization);
    app.setMouseX(1);
    app.setMouseY(1);
    app.AddCommand(new DrawDiagonalLineCommand(CommandDescription::LocalCommand,&app));
    app.ExecuteCommand();

    sf::Image* image = &app.GetImage();

    for (int i = 1; i<= Global::WINDOW_WIDTH/20 + 1;i++){
        REQUIRE(image->getPixel(i,i) == sf::Color::Red);
    }


}


/*! \brief 	Initialize the program, draw using the diagonal line brush, then undo, and check whether or not
*           the pixels are back to their original colors
*/

TEST_CASE("test local undo") {
    App app;
    app.Init(&initialization);
    app.setMouseX(1);
    app.setMouseY(1);
    app.AddCommand(new DrawDiagonalLineCommand(CommandDescription::LocalCommand,&app));
    app.ExecuteCommand();
    app.UndoCommand();

    sf::Image* image = &app.GetImage();

    for (int i = 1; i<= Global::WINDOW_WIDTH/20 + 1;i++){
        REQUIRE(image->getPixel(i,i) == sf::Color::Black);
    }

}

/*! \brief 	Initialize the program, draw using the diagonal line brush, then undo, and redo, and check whether or not
*           the pixels are red or not
*/

TEST_CASE("test local redo") {
    App app;
    app.Init(&initialization);
    app.setMouseX(1);
    app.setMouseY(1);
    app.AddCommand(new DrawDiagonalLineCommand(CommandDescription::LocalCommand,&app));
    app.ExecuteCommand();
    app.UndoCommand();
    app.ExecuteCommand();

    sf::Image* image = &app.GetImage();

    for (int i = 1; i<= Global::WINDOW_WIDTH/20 + 1;i++){
        REQUIRE(image->getPixel(i,i) == sf::Color::Red);
    }

}


void startServer(Server* serverEntity) {
    serverEntity->launch();
}

void startClient(Client* clientEntity) {
    std::cout << "Starting" <<std::endl;

}

void init() {
    std::cout << "App started" << std::endl;
}

void handleIncomingPackets1(App* app, Client* clientEntity, AppEventHandler* appEventHandler) {
    appEventHandler->handleIncomingPackets(app, clientEntity);
}

void handleIncomingPackets2(App* app, Client* clientEntity, AppEventHandler* appEventHandler) {
    appEventHandler->handleIncomingPackets(app, clientEntity);
}

TEST_CASE("test Draw Information is received correctly") {
    Server* serverEntity;
    unsigned short serverPort = 2006;
    unsigned short clientPort = 2007;
    unsigned short clientPort2 = 2008;

    sf::Mutex mutex;

    App* app1 = new App();
    app1->Init(&init);
    App* app2 = new App();
    app2->Init(&init);

    auto* clientEntity = new Client(clientPort);
    clientEntity->getSocket()->setBlocking(true);
    auto* clientEntity2 = new Client(clientPort2);
    clientEntity2->getSocket()->setBlocking(true);

    auto* handler1 = new AppEventHandler();
    auto* handler2 = new AppEventHandler();

    sf::Thread* serverThread = nullptr;
    sf::Thread* clientThread1 = nullptr;
    sf::Thread* clientThread2 = nullptr;

    serverEntity = new Server(serverPort);
    serverThread = new sf::Thread(&startServer, serverEntity);
    serverThread->launch();

    clientThread1 = new sf::Thread(std::bind(&handleIncomingPackets1, app1, clientEntity, handler1));
    clientThread1->launch();
    clientThread2 = new sf::Thread(std::bind(&handleIncomingPackets2, app2, clientEntity, handler2));
    clientThread2->launch();

    sleep(sf::seconds(3));

    sf::Packet p;
    mutex.lock();
    p << static_cast<int32_t >(ClientMessageType::CLIENT_JOINING);
    mutex.unlock();
    clientEntity->getSocket()->send(p, sf::IpAddress::getLocalAddress(), serverPort);


    sf::Packet p2;
    mutex.lock();
    p << static_cast<int32_t >(ClientMessageType::CLIENT_JOINING);
    mutex.unlock();
    clientEntity2->getSocket()->send(p, sf::IpAddress::getLocalAddress(), serverPort);


    app1->setMouseX(100);
    app1->setMouseY(100);
    app1->AddCommand(new DrawCommand(CommandDescription::LocalCommand, app1));
    app1->ExecuteCommand();
    app1->setPmouseX(app1->getMouseX());
    app1->setPmouseY(app1->getMouseY());

    sf::Packet packet;
    DataPacket dp(100, 100, app1->getCurrentBrushColor().toInteger(), app1->getCurrentCanvasColor().toInteger());
    mutex.lock();
    packet << static_cast<int32_t >(ClientMessageType::DRAW_INFORMATION) << dp;
    mutex.unlock();
    clientEntity->getSocket()->send(packet, sf::IpAddress::getLocalAddress(), serverPort);

    sf::Packet undoPacket2;
    sf::IpAddress ipAddressUndo2;
    unsigned short portUndo2;
    if(clientEntity2->getSocket()->receive(undoPacket2, ipAddressUndo2, portUndo2) == sf::Socket::Done) {
        int value;
        undoPacket2 >> value;
        auto clientMessageType = (ClientMessageType) value;

        if(clientMessageType == DRAW_INFORMATION) {
            DataPacket dp;
            if (undoPacket2 >> dp) {

                app2->setMouseX(dp.getMouseX());
                app2->setMouseY(dp.getMouseY());
                app2->setServerCurrentBrushColor(sf::Color(dp.getBrushColor()));
                app2->setCurrentCanvasColor(sf::Color(dp.getCanvasColor()));

                app2->AddCommand(new DrawCommand(CommandDescription::ServerCommand, app2));
                app2->ExecuteCommand();
                app2->setPmouseX(app2->getMouseX());
                app2->setPmouseY(app2->getMouseY());
            }
        }
    }

    REQUIRE(app2->GetImage().getPixel(100, 100).toInteger() == sf::Color::Red.toInteger());
}


void startServer2(Server* serverEntity) {
    serverEntity->launch();
}



TEST_CASE("test client can undo other client's work") {
    Server* serverEntity;
    unsigned short serverPort = 2001;
    unsigned short clientPort = 2002;
    unsigned short clientPort2 = 2003;
    sf::Mutex mutex;

    auto* clientEntity = new Client(clientPort);
    clientEntity->getSocket()->setBlocking(true);
    auto* clientEntity2 = new Client(clientPort2);
    clientEntity2->getSocket()->setBlocking(true);

    auto* handler1 = new AppEventHandler();
    auto* handler2 = new AppEventHandler();

    App* app1 = new App();
    app1->Init(&init);
    App* app2 = new App();
    app2->Init(&init);

    sf::Thread* serverThread = nullptr;
    sf::Thread* clientThread1 = nullptr;
    sf::Thread* clientThread2 = nullptr;

    serverEntity = new Server(serverPort);
    serverThread = new sf::Thread(&startServer2, serverEntity);
    serverThread->launch();

    clientThread1 = new sf::Thread(std::bind(&handleIncomingPackets1, app1, clientEntity, handler1));
    clientThread1->launch();
    clientThread2 = new sf::Thread(std::bind(&handleIncomingPackets2, app2, clientEntity, handler2));
    clientThread2->launch();

    sleep(sf::seconds(3));

    sf::Packet p;
    mutex.lock();
    p << static_cast<int32_t >(ClientMessageType::CLIENT_JOINING);
    mutex.unlock();
    clientEntity->getSocket()->send(p, sf::IpAddress::getLocalAddress(), serverPort);


    sf::Packet p2;
    mutex.lock();
    p << static_cast<int32_t >(ClientMessageType::CLIENT_JOINING);
    mutex.unlock();
    clientEntity2->getSocket()->send(p, sf::IpAddress::getLocalAddress(), serverPort);

//    sleep(3);

    app1->setMouseX(100);
    app1->setMouseY(100);
    app1->AddCommand(new DrawCommand(CommandDescription::LocalCommand, app1));
    app1->ExecuteCommand();
    app1->setPmouseX(app1->getMouseX());
    app1->setPmouseY(app1->getMouseY());

    sf::Packet packet;
    DataPacket dp(100, 100, app1->getCurrentBrushColor().toInteger(), app1->getCurrentCanvasColor().toInteger());
    mutex.lock();
    packet << static_cast<int32_t >(ClientMessageType::DRAW_INFORMATION) << dp;
    mutex.unlock();
    clientEntity->getSocket()->send(packet, sf::IpAddress::getLocalAddress(), serverPort);

    app1->setMouseX(101);
    app1->setMouseY(101);
    app1->AddCommand(new DrawCommand(CommandDescription::LocalCommand, app1));
    app1->ExecuteCommand();
    app1->setPmouseX(app1->getMouseX());
    app1->setPmouseY(app1->getMouseY());

    sf::Packet packet2;
    DataPacket dp2(101, 101, app1->getCurrentBrushColor().toInteger(), app1->getCurrentCanvasColor().toInteger());
    mutex.lock();
    packet << static_cast<int32_t >(ClientMessageType::DRAW_INFORMATION) << dp2;
    mutex.unlock();
    clientEntity->getSocket()->send(packet, sf::IpAddress::getLocalAddress(), serverPort);

    sf::Packet packet3;
    mutex.lock();
    packet3 << static_cast<int32_t >(ClientMessageType::UNDO_COMMAND);
    mutex.unlock();
    clientEntity2->getSocket()->send(packet3, sf::IpAddress::getLocalAddress(), serverPort);

    sf::Packet packet4;
    mutex.lock();
    packet4 << static_cast<int32_t >(ClientMessageType::UNDO_COMMAND);
    mutex.unlock();
    clientEntity2->getSocket()->send(packet4, sf::IpAddress::getLocalAddress(), serverPort);

    sf::Packet undoPacket;
    sf::IpAddress ipAddressUndo;
    unsigned short portUndo;

    if(clientEntity->getSocket()->receive(undoPacket, ipAddressUndo, portUndo) == sf::Socket::Done) {
        int value;
        undoPacket >> value;
        auto clientMessageType = (ClientMessageType) value;

        if(clientMessageType == UNDO_COMMAND) {
            app1->UndoCommand();
        }
    }

    sf::Packet undoPacket2;
    sf::IpAddress ipAddressUndo2;
    unsigned short portUndo2;

    if(clientEntity2->getSocket()->receive(undoPacket2, ipAddressUndo2, portUndo2) == sf::Socket::Done) {
        int value;
        undoPacket2 >> value;
        auto clientMessageType = (ClientMessageType) value;

        if(clientMessageType == UNDO_COMMAND) {
            app1->UndoCommand();
        }
    }

    REQUIRE(app1->GetImage().getPixel(101, 101).toInteger() == sf::Color::Black.toInteger());

    delete app1;
    delete app2;
    delete handler1;
    delete handler2;
    delete clientEntity;
    delete clientEntity2;
}

TEST_CASE("test client can redo other client's work") {
    Server* serverEntity;
    unsigned short serverPort = 2010;
    unsigned short clientPort = 2011;
    unsigned short clientPort2 = 2012;
    sf::Mutex mutex;

    auto* clientEntity = new Client(clientPort);
    clientEntity->getSocket()->setBlocking(true);
    auto* clientEntity2 = new Client(clientPort2);
    clientEntity2->getSocket()->setBlocking(true);

    auto* handler1 = new AppEventHandler();
    auto* handler2 = new AppEventHandler();

    App* app1 = new App();
    app1->Init(&init);
    App* app2 = new App();
    app2->Init(&init);

    sf::Thread* serverThread = nullptr;
    sf::Thread* clientThread1 = nullptr;
    sf::Thread* clientThread2 = nullptr;

    serverEntity = new Server(serverPort);
    serverThread = new sf::Thread(&startServer2, serverEntity);
    serverThread->launch();

    clientThread1 = new sf::Thread(std::bind(&handleIncomingPackets1, app1, clientEntity, handler1));
    clientThread1->launch();
    clientThread2 = new sf::Thread(std::bind(&handleIncomingPackets2, app2, clientEntity, handler2));
    clientThread2->launch();

    sleep(sf::seconds(3));

    sf::Packet p;
    mutex.lock();
    p << static_cast<int32_t >(ClientMessageType::CLIENT_JOINING);
    mutex.unlock();
    clientEntity->getSocket()->send(p, sf::IpAddress::getLocalAddress(), serverPort);


    sf::Packet p2;
    mutex.lock();
    p << static_cast<int32_t >(ClientMessageType::CLIENT_JOINING);
    mutex.unlock();
    clientEntity2->getSocket()->send(p, sf::IpAddress::getLocalAddress(), serverPort);

//    sleep(3);

    app1->setMouseX(100);
    app1->setMouseY(100);
    app1->AddCommand(new DrawCommand(CommandDescription::LocalCommand, app1));
    app1->ExecuteCommand();
    app1->setPmouseX(app1->getMouseX());
    app1->setPmouseY(app1->getMouseY());

    sf::Packet packet;
    DataPacket dp(100, 100, app1->getCurrentBrushColor().toInteger(), app1->getCurrentCanvasColor().toInteger());
    mutex.lock();
    packet << static_cast<int32_t >(ClientMessageType::DRAW_INFORMATION) << dp;
    mutex.unlock();
    clientEntity->getSocket()->send(packet, sf::IpAddress::getLocalAddress(), serverPort);

    app1->setMouseX(101);
    app1->setMouseY(101);
    app1->AddCommand(new DrawCommand(CommandDescription::LocalCommand, app1));
    app1->ExecuteCommand();
    app1->setPmouseX(app1->getMouseX());
    app1->setPmouseY(app1->getMouseY());

    sf::Packet packet2;
    DataPacket dp2(101, 101, app1->getCurrentBrushColor().toInteger(), app1->getCurrentCanvasColor().toInteger());
    mutex.lock();
    packet << static_cast<int32_t >(ClientMessageType::DRAW_INFORMATION) << dp2;
    mutex.unlock();
    clientEntity->getSocket()->send(packet, sf::IpAddress::getLocalAddress(), serverPort);

    sf::Packet packet3;
    mutex.lock();
    packet3 << static_cast<int32_t >(ClientMessageType::UNDO_COMMAND);
    mutex.unlock();
    clientEntity2->getSocket()->send(packet3, sf::IpAddress::getLocalAddress(), serverPort);

    sf::Packet packet4;
    mutex.lock();
    packet4 << static_cast<int32_t >(ClientMessageType::UNDO_COMMAND);
    mutex.unlock();
    clientEntity2->getSocket()->send(packet4, sf::IpAddress::getLocalAddress(), serverPort);

    sf::Packet undoPacket;
    sf::IpAddress ipAddressUndo;
    unsigned short portUndo;

    if(clientEntity->getSocket()->receive(undoPacket, ipAddressUndo, portUndo) == sf::Socket::Done) {
        int value;
        undoPacket >> value;
        auto clientMessageType = (ClientMessageType) value;

        if(clientMessageType == UNDO_COMMAND) {
            app1->UndoCommand();
        }
    }

    sf::Packet undoPacket2;
    sf::IpAddress ipAddressUndo2;
    unsigned short portUndo2;

    if(clientEntity2->getSocket()->receive(undoPacket2, ipAddressUndo2, portUndo2) == sf::Socket::Done) {
        int value;
        undoPacket2 >> value;
        auto clientMessageType = (ClientMessageType) value;

        if(clientMessageType == UNDO_COMMAND) {
            app1->UndoCommand();
        }
    }

    sf::Packet packet5;
    mutex.lock();
    packet4 << static_cast<int32_t >(ClientMessageType::REDO_COMMAND);
    mutex.unlock();
    clientEntity2->getSocket()->send(packet4, sf::IpAddress::getLocalAddress(), serverPort);

    sf::Packet redoPacket;
    sf::IpAddress ipAddressRedo;
    unsigned short portRedo;

    if(clientEntity->getSocket()->receive(redoPacket, ipAddressRedo, portRedo) == sf::Socket::Done) {
        int value;
        redoPacket >> value;
        auto clientMessageType = (ClientMessageType) value;

        if(clientMessageType == REDO_COMMAND) {
            app1->ExecuteCommand();
        }
    }

    REQUIRE(app1->GetImage().getPixel(100, 100).toInteger() == sf::Color::Red.toInteger());

    delete app1;
    delete app2;
    delete handler1;
    delete handler2;
    delete clientEntity;
    delete clientEntity2;
}



