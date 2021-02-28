/**
*  @file   DataPacket.cpp
*  @brief Implementation of DataPacket.hpp
*  @author Mike and team VanDoesn'tGo
*  @date   2020-08-02
***********************************************/

#include "command/DataPacket.hpp"

/*! \brief     Constructor for data packet, takes in position
*              canvas color and brush color
*/
DataPacket::DataPacket(unsigned int x, 
                       unsigned int y, 
                       sf::Uint32 bColor,
                       sf::Uint32 cColor) : brushColor(bColor), canvasColor(cColor) {
    mouseX = x;
    mouseY = y;

}

/*! \brief     Default constructor
*/
DataPacket::DataPacket(): mouseX(0), mouseY(0), brushColor(0), canvasColor(0) {
}

/*! \brief     Returns mouse position on x axis
*/
unsigned int DataPacket::getMouseX() const{
    return mouseX;
}

/*! \brief     Returns mouse position on y axis
*/
unsigned int DataPacket::getMouseY() const{
    return mouseY;
}

/*! \brief     Returns brush color
*/
sf::Uint32 DataPacket::getBrushColor() const{
    return brushColor;
}

/*! \brief     Returns canvas color
*/
sf::Uint32 DataPacket::getCanvasColor() const{
    return canvasColor;
}


/*! \brief     Sending info from data packet
*/
sf::Packet& operator <<(sf::Packet& packet, const DataPacket& dataPacket)
{
    return packet << dataPacket.mouseX << dataPacket.mouseY << dataPacket.brushColor << dataPacket.canvasColor;
}

/*! \brief     Extracting info from data packet
*/
sf::Packet& operator >>(sf::Packet& packet, DataPacket& dataPacket)
{
    return packet >> dataPacket.mouseX >> dataPacket.mouseY >> dataPacket.brushColor >> dataPacket.canvasColor;
}

