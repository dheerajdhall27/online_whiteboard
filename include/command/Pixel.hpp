/**
*  @file  Pixel.hpp
*  @brief  Object for each pixel that is drawn on the canvas
*  @author Mike and Van_doesnt_go
*  @date   3/29/20.
***********************************************/

#ifndef ASSIGNMENT4_NETWORKING_PIXEL_H
#define ASSIGNMENT4_NETWORKING_PIXEL_H

#include <SFML/Graphics.hpp>

/*! \brief Object for each pixel that is drawn on the canvas
 */
class Pixel {
    private:
        unsigned int _x{};
        unsigned int _y{};

        sf::Color _brushColor;
        sf::Color _canvasColor;

    public:
        Pixel(unsigned int x, unsigned int y, sf::Color brushColor, sf::Color canvasColor);
        Pixel() = default;

        unsigned int getX() const;
        unsigned int getY() const;

        sf::Color getBrushColor();
        sf::Color getCanvasColor();
};


#endif //ASSIGNMENT4_NETWORKING_PIXEL_H
