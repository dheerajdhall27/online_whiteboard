/**
 *  @file   App.hpp
 *  @brief  App class interface
 *  @author Mike and Van_doesnt_go
 *  @date   2020-April- 10
 ***********************************************/
#ifndef APP_HPP
#define APP_HPP

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
// Include standard library C++ libraries.
#include <queue>
#include <stack>
#include "command/Command.hpp"
#include <command/BrushType.hpp>
// Project header files
// #include ...


/*! \brief Object for our application, stores the bulk of the data needed to run
 *          the app. 
 */
class App{
private:
    std::stack<Command*> m_commands;
    std::stack<Command*> m_undo;

    sf::Image* m_image;
    sf::Sprite* m_sprite;
    sf::Texture* m_texture;

    unsigned int        pmouseX, pmouseY, mouseX, mouseY;
    sf::RenderWindow*   m_window;
    sf::Color           currentBrushColor;
    sf::Color           serverCurrentBrushColor;
    sf::Color           currentCanvasColor;

    BrushType serverBrushType;

    void (*m_initFunc)();
    void (*m_loopFunc)();

public:
    App();
    App(const App&);
    App& operator=(const App& );
    ~App();

    unsigned int        canvasWidth, canvasHeight;

    unsigned int        getMouseX();
    unsigned int        getMouseY();
    sf::Color           getCurrentBrushColor();
    sf::Color           getServerCurrentBrushColor();
    sf::Color           getCurrentCanvasColor();

    void                setPmouseX(unsigned int pmX);
    void                setPmouseY(unsigned int pmY);
    void                setMouseX(unsigned int mX);
    void                setMouseY(unsigned int mY);
    void                setCurrentBrushColor(const sf::Color &cbColor);
    void                setServerCurrentBrushColor(const sf::Color &sbColor);
    void                setCurrentCanvasColor(const sf::Color &ccColor);

    void                AddCommand(Command* c);
    void                ExecuteCommand();
    void                UndoCommand();
    sf::Image&          GetImage();
    sf::Texture&        GetTexture();
    sf::RenderWindow&   GetWindow();
    sf::Sprite&         GetSprite();

    void Destroy();
    void Init(void (*initFunction)());
    void LoopCallback(void (*loopFunction)());

};




#endif
