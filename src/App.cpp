/**
 *  @file   App.cpp
 *  @brief  Main class for program
 *  @author Mike and and team van_doesnt_go
 *  @date   2020-08-04
 ***********************************************/

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window.hpp>
// Include standard library C++ libraries.
#include <cassert>

// Project header files
#include "App.hpp"
#include <Global.hpp>



/*! \brief     A default constructor to initialize all the variables.
*
*/
App::App() : currentBrushColor(sf::Color::Red), serverCurrentBrushColor(sf::Color::Red),
currentCanvasColor(sf::Color::Black){
    m_initFunc = nullptr;
    m_loopFunc = nullptr;

    pmouseX = pmouseY = mouseX = mouseY = 0;

    m_window = nullptr;


    m_image = new sf::Image;
    m_sprite = new sf::Sprite;
    m_texture = new sf::Texture;

    canvasWidth = Global::WINDOW_WIDTH;
    canvasHeight = Global::WINDOW_HEIGHT;
    serverBrushType = BrushType::REGULAR;
}

/*! \brief     A copy constructor to make a copy of the existing instance of App
*
*/
App::App(const App& rhs) : currentBrushColor(rhs.currentBrushColor),
serverCurrentBrushColor(rhs.serverCurrentBrushColor), currentCanvasColor(rhs.currentCanvasColor) {
    m_initFunc = rhs.m_initFunc;
    m_loopFunc = rhs.m_loopFunc;

    pmouseX = rhs.pmouseX;
    pmouseY = rhs.pmouseY;
    mouseX = rhs.mouseX;
    mouseY = rhs.mouseY;

    m_window = rhs.m_window;

    m_image = new sf::Image;
    m_sprite = new sf::Sprite;
    m_texture = new sf::Texture;


    canvasWidth = rhs.canvasWidth;
    canvasHeight = rhs.canvasHeight;
    serverBrushType = rhs.serverBrushType;
}

/*! \brief     An assignment operator to assign one instance to another
*
*/
App&App::operator=(const App& rhs) {
    if (&rhs != this) {
        m_initFunc = rhs.m_initFunc;
        m_loopFunc = rhs.m_loopFunc;

        pmouseX = rhs.pmouseX;
        pmouseY = rhs.pmouseY;
        mouseX = rhs.mouseX;
        mouseY = rhs.mouseY;



        m_window = rhs.m_window;

        m_image = new sf::Image;
        m_sprite = new sf::Sprite;
        m_texture = new sf::Texture;

        currentBrushColor = rhs.currentBrushColor;
        serverCurrentBrushColor = rhs.serverCurrentBrushColor;
        currentCanvasColor = rhs.currentCanvasColor;


        canvasWidth = rhs.canvasWidth;
        canvasHeight = rhs.canvasHeight;
        serverBrushType = rhs.serverBrushType;
    }

    return *this;
}

/*! \brief     Destructor to delete the app and its member variables
*
*/
App::~App(){
    delete m_image;
    delete m_sprite;
    delete m_texture;
    delete m_window;
}

/*! \brief     Get mouse x position
*
*/
unsigned int App::getMouseX(){
    return mouseX;
}

/*! \brief     Get mouse y position
*
*/
unsigned int App::getMouseY(){
    return mouseY;
}

/*! \brief     Get current brush color
*
*/
sf::Color App::getCurrentBrushColor(){
    return currentBrushColor;
}

/*! \brief     Get current server brush color
*
*/
sf::Color App::getServerCurrentBrushColor(){
    return serverCurrentBrushColor;
}

/*! \brief     Return canvas color
*
*/
sf::Color App::getCurrentCanvasColor(){
    return currentCanvasColor;
}

/*! \brief     When we draw, we would prefer to add
*        a command to a data structure.
*
*/
void App::AddCommand(Command* c) {
    std::stack<Command*> empty;
    std::swap(m_commands, empty);

    if ((mouseX == pmouseX) && (mouseY == pmouseY)) {
        return;
    }

    if ((mouseX <= canvasWidth) && (mouseY <= canvasHeight)) {
        m_commands.push(c);
    }
}

/*! \brief     Pushes the command to the command stack and executes it
*
*/
void App::ExecuteCommand() {
    if (m_commands.empty()) {
        return;
    }
    Command* command = m_commands.top();

    command->execute();
    m_commands.pop();
    m_undo.push(command);
}


/*! \brief     Executes the commands from the top of the m_undo stack.
*
*/
void App::UndoCommand() {
    if (m_undo.empty()) {
        return;
    }

    m_undo.top()->undo();
    m_commands.push(m_undo.top());

    m_undo.pop();
}

/*! \brief     Returns a reference to our m_image, so that we do not have to publicly expose it.
*
*/
sf::Image& App::GetImage(){
    return *m_image;
}

/*! \brief     Returns a reference to our m_Texture so that we do not have to publicly expose it.
*
*/
sf::Texture& App::GetTexture(){
    return *m_texture;
}

/*! \brief     Returns a reference to our m_sprite so that we do not have to publicly expose it.
*
*/
sf::Sprite& App::GetSprite(){
    return *m_sprite;
}

/*! \brief     Returns a reference to our m_window so that we do not have to publicly expose it.
*
*/
sf::RenderWindow& App::GetWindow(){
    return *m_window;
}



/*! \brief     Destroy we manually call at end of our program.
*
*/
void App::Destroy(){
    delete m_image;
    delete m_sprite;
    delete m_texture;
    delete m_window;
}

/*! \brief     Initializes the App and sets up the main rendering window(i.e. our canvas.)
*/
void App::Init(void (*initFunction)()){
    sf::ContextSettings settings(24, 8, 4, 2, 2);
    // Create our window
    m_window = new sf::RenderWindow(sf::VideoMode(Global::WINDOW_WIDTH,Global::WINDOW_HEIGHT),"Mini-Paint alpha 0.0.2",
            sf::Style::Default, settings);
    m_window->setVerticalSyncEnabled(true);
    m_window->setActive(true);
    // Create an image which stores the pixels we will update
    m_image->create(canvasWidth, canvasHeight, currentCanvasColor);
    assert(m_image != nullptr && "m_image != nullptr");
    // Create a texture which lives in the GPU and will render our image
    m_texture->loadFromImage(*m_image);
    assert(m_texture != nullptr && "m_texture != nullptr");
    // Create a sprite which is the entity that can be textured
    m_sprite->setTexture(*m_texture);
    assert(m_sprite != nullptr && "m_sprite != nullptr");
    
    
    // Set our initialization function to perform any user
    // initialization
    m_initFunc = initFunction;
}



/*! \brief     The main loop function which handles initialization
        and will be executed until the main window is closed.
        Within the loop function the update and draw callback
        functions will be called.
*
*/
void App::LoopCallback(void (*loopFunction)()){
    // Call the init function
    m_initFunc();
    m_loopFunc = loopFunction;
    m_loopFunc();
}

/*! \brief     Set previous mouse x
*
*/
void App::setPmouseX(unsigned int pmX) {
    App::pmouseX = pmX;
}

/*! \brief     Set previous mouse y
*
*/
void App::setPmouseY(unsigned int pmY) {
    App::pmouseY = pmY;
}

/*! \brief     Set current mouse x
*
*/
void App::setMouseX(unsigned int mX) {
    App::mouseX = mX;
}

/*! \brief     Set current mouse y
*
*/
void App::setMouseY(unsigned int mY) {
    App::mouseY = mY;
}

/*! \brief     Set current brush color
*
*/
void App::setCurrentBrushColor(const sf::Color &cbColor) {
    App::currentBrushColor = cbColor;
}

/*! \brief     Set current server brush color
*
*/
void App::setServerCurrentBrushColor(const sf::Color &scbColor) {
    App::serverCurrentBrushColor = scbColor;
}

/*! \brief     Return current canvas color
*
*/
void App::setCurrentCanvasColor(const sf::Color &ccColor) {
    App::currentCanvasColor = ccColor;
}

