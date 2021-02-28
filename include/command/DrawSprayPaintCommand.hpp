/**
*  @file  DrawSprayPaintCommand.hpp
*  @brief  Object for the DrawSprayPaintCommand command, which inherits from AbstractCommand class
*  @author Mike and Van_doesnt_go
*  @date   3/29/20.
***********************************************/
#ifndef DRAWSPRAYPAINT_H
#define DRAWSPRAYPAINT_H

// Include standard library C++ libraries.
#include <string>
#include <vector>
// Project header files
#include "command/AbstractCommand.hpp"
#include "command/Pixel.hpp"
#include "command/CommandDescription.hpp"

using namespace std; 
// Anytime we want to implement a new command in our paint tool,
// we have to inherit from the command class.
// This forces us to implement an 'execute' and 'undo' command.

/*! \brief Object for the DrawSprayPaintCommand command, which inherits from AbstractCommand class
 */
class DrawSprayPaintCommand : public AbstractCommand{
    private:
        void spray(unsigned int x,unsigned int y, sf::Color color);
        struct point {
            unsigned int x, y;
            sf::Color color;
            point() {
                x = 0;
                y = 0;
            }
        };
        vector<point>::iterator ptr;
        vector<point> allPoints;
    public:
        DrawSprayPaintCommand(const CommandDescription & commandDescription, App* mainApp);
        bool execute() override;
        bool undo() override;
};

#endif
