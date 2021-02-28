/**
*  @file   DataPacket.hpp
*  @brief  Object for the data packet that is sent from each client drawing on the canvas.
*  @author Mike and van_doesnt_go
*  @date   2020-13-04
***********************************************/
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "command/BrushType.hpp"

/*! \brief Object for the data packet that is sent from each client drawing on the canvas.
 */
class DataPacket : public sf::Packet {
    private:
        unsigned int mouseX{}, mouseY{};
        sf::Uint32 brushColor{};
        sf::Uint32 canvasColor{};
    public:
        DataPacket();
        DataPacket(unsigned int x, 
                   unsigned int y, 
                   sf::Uint32 bColor,
                   sf::Uint32 cColor);
        unsigned int getMouseX() const;
        unsigned int getMouseY() const;
        sf::Uint32 getBrushColor() const;
        sf::Uint32 getCanvasColor() const;

	friend sf::Packet& operator <<(sf::Packet& packet, const DataPacket& dataPacket);

	friend sf::Packet& operator >>(sf::Packet& packet, DataPacket& dataPacket);
};

