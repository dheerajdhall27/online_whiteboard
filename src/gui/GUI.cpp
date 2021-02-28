/**
*  @file   GUI.cpp
*  @brief   Class that represents the GUI of our program
*  @author Mike and team van_doesnt_go
*  @date   2020-08-04
***********************************************/
#include "gui/GUI.hpp"
// Nuklear needs to call OpenGL functions
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
// NUKLEAR implementation
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SFML_GL2_IMPLEMENTATION
#include "gui/nuklear.h"
#include "gui/nuklear_sfml_gl2.h"
#include "Global.hpp"

int GUI::op = RED;
int GUI::br_op = BrushType::REGULAR;
struct nk_colorf _bg;

/*! \brief     Constructor for initializing all the variables of the GUI class
*
*/
GUI::GUI():_settings(24, 8, 4, 2, 2),
           m_gui_window(sf::VideoMode(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT),
                        "GUI Window",
                        sf::Style::Default),
                        _ctx(nk_sfml_init(&m_gui_window)) {
    m_gui_window.setVerticalSyncEnabled(true);
    m_gui_window.setActive(true);
    glViewport(0, 0, m_gui_window.getSize().x, m_gui_window.getSize().y);

    nk_sfml_font_stash_begin(&_atlas);
    nk_sfml_font_stash_end();

    _bg.r = 0.10f, _bg.g = 0.18f, _bg.b = 0.24f, _bg.a = 1.0f;
}

/*! \brief     Returns GUI window
*/
sf::RenderWindow* GUI::GetGuiWindow() {
    return &m_gui_window;
}

/*! \brief     Returns GUI context
*/
struct nk_context* GUI::GetContext(){
    return _ctx;
}

/*! \brief     Creates the GUI window 
*/
void GUI::drawLayout(struct nk_context* ctx) {
    /* GUI */
    if (nk_begin(ctx, "Demo", nk_rect(50, 50, 360, 300),
                 NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
                 NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    {
        nk_layout_row_static(ctx, 40, 90, 1);

        nk_layout_row_dynamic(ctx, 20, 1);
        nk_label(ctx, "Brush Type:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 40, 3);
        if (nk_option_label(ctx, "regular", br_op == BrushType::REGULAR)){
            br_op = BrushType::REGULAR;
        }
        if (nk_option_label(ctx, "square", br_op == BrushType::SQUARE_BRUSH)){
            br_op = BrushType::SQUARE_BRUSH;
        }
        if (nk_option_label(ctx, "diagonal line", br_op == BrushType::DIAGONAL_LINE_BRUSH)){
            br_op = BrushType::DIAGONAL_LINE_BRUSH;
        }
        if (nk_option_label(ctx, "spray paint", br_op == BrushType::SPRAY_PAINT_BRUSH)){
            br_op = BrushType::SPRAY_PAINT_BRUSH;
        }
        if (nk_option_label(ctx, "heart", br_op == BrushType::HEART_BRUSH)){
            br_op = BrushType::HEART_BRUSH;
        }
        if (nk_option_label(ctx, "circle", br_op == BrushType::CIRCLE_BRUSH)){
            br_op = BrushType::CIRCLE_BRUSH;
        }
        if (nk_option_label(ctx, "rectangle", br_op == BrushType::RECT_BRUSH)){
            br_op = BrushType::RECT_BRUSH;
        }


        nk_layout_row_dynamic(ctx, 20, 1);
        nk_label(ctx, "Brush Color:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 40, 3);
        if (nk_option_label(ctx, "red", op == RED)){
            op = RED;
        }
        if (nk_option_label(ctx, "black", op == BLACK)){
            op = BLACK;
        }
        if (nk_option_label(ctx, "green", op == GREEN)){
            op = GREEN;
        }
        if (nk_option_label(ctx, "blue", op == BLUE)){
            op = BLUE;
        }
        if (nk_option_label(ctx, "white", op == WHITE)){
            op = WHITE;
        }
        if (nk_option_label(ctx, "yellow", op == YELLOW)){
            op = YELLOW;
        }
        if (nk_option_label(ctx, "magenta", op == MAGENTA)){
            op = MAGENTA;
        }
        if (nk_option_label(ctx, "cyan", op == CYAN)){
            op = CYAN;
        }

        nk_layout_row_dynamic(ctx, 20, 1);
        nk_label(ctx, "background:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 25, 1);
        if (nk_combo_begin_color(ctx, nk_rgb_cf(_bg), nk_vec2(nk_widget_width(ctx),400))) {
            nk_layout_row_dynamic(ctx, 120, 1);
            _bg = nk_color_picker(ctx, _bg, NK_RGBA);
            nk_layout_row_dynamic(ctx, 25, 1);
            _bg.r = nk_propertyf(ctx, "#R:", 0, _bg.r, 1.0f, 0.01f,0.005f);
            _bg.g = nk_propertyf(ctx, "#G:", 0, _bg.g, 1.0f, 0.01f,0.005f);
            _bg.b = nk_propertyf(ctx, "#B:", 0, _bg.b, 1.0f, 0.01f,0.005f);
            _bg.a = nk_propertyf(ctx, "#A:", 0, _bg.a, 1.0f, 0.01f,0.005f);
            nk_combo_end(ctx);
        }
    }
    nk_end(ctx);
}

/*! \brief    Destructor to shut down the GUI and delete its member variables
*
*/
GUI::~GUI(){
    nk_sfml_shutdown();
    delete _ctx;
    delete _atlas;
}


/*! \brief     Handles the event happening inside the GUI
*
*/
void GUI::handleEvent(sf::Event& event) {
    nk_sfml_handle_event(&event);
}

/*! \brief     Begins taking input to the GUI
*
*/
void GUI::beginInput(struct nk_context *context) {
    nk_input_end(context);
}

/*! \brief     Ends taking input to the GUI
*
*/
void GUI::endInput(struct nk_context *context) {
    nk_input_end(context);
}

/*! \brief     Renders the GUI
*
*/
void GUI::render() {
    nk_sfml_render(NK_ANTI_ALIASING_ON);
}

/*! \brief     Clears the GUI
*
*/
void GUI::clearColor() {
    glClearColor(_bg.r, _bg.g, _bg.b, _bg.a);
}
