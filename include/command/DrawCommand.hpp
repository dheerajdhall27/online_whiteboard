/**
 *  @file   DrawCommand.hpp
 *  @brief  Drawing actions interface.
 *  @author Mike and van_doesnt_go
 *  @date   2020-13-04
 ***********************************************/
#ifndef DRAW_H
#define DRAW_H


// Include standard library C++ libraries.
#include <string>
// Project header files
#include "command/AbstractCommand.hpp"
#include "command/Pixel.hpp"
#include "command/CommandDescription.hpp"
// Anytime we want to implement a new command in our paint tool,
// we have to inherit from the command class.
// This forces us to implement an 'execute' and 'undo' command.

/*! \brief Object for the DrawCommand command, which inherits from AbstractCommand class
 */
class DrawCommand : public AbstractCommand{
    private:

//        static sf::Color getColor(const CommandDescription &commandDescription, App* mainApp);
    public:
        DrawCommand(const CommandDescription & commandDescription, App* mainApp);
        bool execute() override;
        bool undo() override;
};

#endif
