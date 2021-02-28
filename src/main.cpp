/**
 *  @file   main.cpp
 *  @brief  Entry point into the program.
 *  @author Mike and team van_doesnt_go
 *  @date   2020-08-04
 ***********************************************/

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>

#include "App.hpp"
#include "AppEventHandler.hpp"
#include "networking/AbstractNetworkManagerEntity.hpp"
#include "networking/NetworkManagerFactory.hpp"
#include "networking/NetworkEntityType.hpp"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SFML_GL2_IMPLEMENTATION

// Create App, EventHandler, client and server
App *app = nullptr;
AbstractNetworkManagerEntity *clientEntity = nullptr;
AbstractNetworkManagerEntity *serverEntity = nullptr;
AppEventHandler *appEventHandler = nullptr;

// Create GUI object
GUI *gui = nullptr;

// Create GUI object variables needed for the code below.
struct nk_context *ctx = nullptr;
sf::RenderWindow *gui_window = nullptr;


/*! \brief     Initialization function callback for passing into the App object
*
*/
void initialization() {
    std::cout << "Starting the App" << std::endl;
}

/*! \brief     Updates the app depending on the actions of the user
*
*/
void updateApp(sf::Event &event) {
    while (app->GetWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            app->GetWindow().close();
            exit(EXIT_SUCCESS);
        }

        appEventHandler->handleKeyboardEvents(event, app, clientEntity);
    }
}

/*! \brief     Updates the GUI depending on the actions of the user
*
*/
void updateGUI(sf::Event &event) {
    while (gui_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            gui_window->close();
            exit(EXIT_SUCCESS);
        } else if (event.type == sf::Event::KeyReleased) {
            std::cout << "Key Pressed" << std::endl;
            if (event.key.code == sf::Keyboard::Escape) {
                gui_window->close();
                exit(EXIT_SUCCESS);
            }
        }
        gui->handleEvent(event);
        appEventHandler->handleKeyboardEvents(event, app, clientEntity);
    }
}

/*! \brief      Sets up GUI panel for user to interface with the application
*
*/
void setupGUI() {
    gui->endInput(ctx);

    gui->drawLayout(ctx);

    appEventHandler->handleMouseEvents(app, gui, clientEntity);

    AppEventHandler::handleIncomingPackets(app, clientEntity);

    gui_window->setActive(true);
    gui_window->clear();
    gui->clearColor();
    glClear(GL_COLOR_BUFFER_BIT);

    gui->render();
    gui_window->display();
}

/*! \brief     The update callback function for handling event happening inside the canvas window and the GUI window
*
*/
void update() {
    sf::Event event{};

    updateApp(event);

    gui->beginInput(ctx);

    updateGUI(event);

    setupGUI();

    app->GetWindow().setActive(true);
    app->GetWindow().clear();
    app->GetWindow().draw(app->GetSprite());
    app->GetWindow().display();
}


/*! \brief  Draws the pixels that were modified to the window every 0 draw calls that were made
*/
void draw() {
    static int refreshRate = 0;
    ++refreshRate;

    if (refreshRate > 10) {
        app->GetTexture().loadFromImage(app->GetImage());
        refreshRate = 0;
    }
}

/*! \brief Loop callback function. While the ap is open, this updates and draws
*               on the canvas.
*/
void loop() {
    while (app->GetWindow().isOpen() && gui_window->isOpen()) {
        app->GetWindow().clear();
        update();
        draw();

    }
}


/*! \brief Instantiates the GUI interface and starts the application
 */
void startApplication() {
    gui = new GUI();
    ctx = gui->GetContext();
    gui_window = gui->GetGuiWindow();

    std::cout << "Starting" << std::endl;

    app = new App;

    app->Init(&initialization);

    app->LoopCallback(&loop);

}


/*! \brief     The entry point into our program.
*
*/
int main() {
    appEventHandler = new AppEventHandler();
    std::string role;

    std::cout << "Enter (s) for Server, Enter (c) for client: " << std::endl;
    std::cin >> role;

    if (role[0] == 's') {
        serverEntity = NetworkManagerFactory::makeNetworkEntity(SERVER);
        serverEntity->launch();
    } else if (role[0] == 'c') {
        clientEntity = NetworkManagerFactory::makeNetworkEntity(CLIENT);
        clientEntity->joinServer(clientEntity->getServerIp(),
                                 clientEntity->getServerPort());
        clientEntity->launch();
        startApplication();
    }

    delete clientEntity;
    delete serverEntity;
    delete appEventHandler;
    delete gui;
    delete app;

    return 0;
}
