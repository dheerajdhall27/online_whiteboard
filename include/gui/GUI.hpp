/**
 *  @file   GUI.hpp
 *  @brief  Class that represents the GUI of our program
 *  @author Mike and van_doesnt_go
 *  @date   2020-13-04
 ***********************************************/

#ifndef APP_GUI_HPP
#define APP_GUI_HPP
// Include some standard libraries
// The 'C-based' libraries are needed for Nuklear GUI
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <command/BrushType.hpp>

enum {BLACK = 27, WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN};

/*! \brief Object for the GUI interface where the user can control the application
 *          rather than through the keyboard. 
 * */
class GUI {
    private:
        // Member variables
        sf::ContextSettings     _settings;
        sf::RenderWindow        m_gui_window;
        struct nk_context       *_ctx;
        struct nk_font_atlas    *_atlas{};
    public:
        static int op;
        static int br_op;
        GUI();
        ~GUI();
        void drawLayout(struct nk_context* ctx);
        sf::RenderWindow* GetGuiWindow();
        struct nk_context* GetContext();

        void handleEvent(sf::Event& event);

        void beginInput(struct nk_context *context);

        void endInput(struct nk_context *context);

        void render();

        void clearColor();
};
#endif //APP_GUI_HPP
