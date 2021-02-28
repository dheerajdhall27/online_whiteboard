/**
*  @file  Pixel.cpp
*  @brief  An object that represents a pixel 
*  @author Mike and team VanDoesntgo
*  @date   3/29/20
***********************************************/
#include "command/Pixel.hpp"

#include <SFML/Graphics.hpp>

/*! \brief A Constructor to build a Pixel Object
 *
 */
Pixel::Pixel(unsigned int x, unsigned int y, sf::Color brushColor, sf::Color canvasColor)
        : _x(x), _y(y), _brushColor(brushColor), _canvasColor(canvasColor) {

}

/*! \brief     Returns the value of the x co-ordinate of the pixel.
*
*/
unsigned int Pixel::getX() const {
    return _x;
}

/*! \brief     Returns the value of the y co-ordinate of the pixel.
*
*/
unsigned int Pixel::getY() const {
    return _y;
}

/*! \brief     Returns the value of the brushColor.
*
*/
sf::Color Pixel::getBrushColor() {
    return _brushColor;
}

/*! \brief     Set the value of the canvasColor.
*
*/
sf::Color Pixel::getCanvasColor() {
    return _canvasColor;
}
