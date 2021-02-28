/**
 *  @file   DrawSquareCommand.hpp
 *  @brief  Class for Drawing a Square.
 *  @author Mike and van_doesnt_go
 *  @date   13 - April - 2020
 ***********************************************/
#ifndef DRAWSQUARE_H
#define DRAWSQUARE_H

// Include standard library C++ libraries.
#include <string>
// Project header files
#include "command/AbstractCommand.hpp"
#include "command/Pixel.hpp"
#include "command/CommandDescription.hpp"
// Anytime we want to implement a new command in our paint tool,
// we have to inherit from the command class.
// This forces us to implement an 'execute' and 'undo' command.


/*! \brief Object for the DrawSquareCommand command, which inherits from AbstractCommand class
 */
class DrawSquareCommand : public AbstractCommand{
    private:
	    unsigned int sideLength;
        std::vector<Pixel> getSquarePixels(unsigned int x, unsigned int y);
    public:
        DrawSquareCommand(const CommandDescription & commandDescription, App* mainApp);
        bool execute() override;
};

#endif
