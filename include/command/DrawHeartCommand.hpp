/**
 *  @file   DrawHeartCommand.hpp
 *  @brief  Object for the DrawHeartCommand command, which inherits from AbstractCommand class
 *  @author Mike and Van_doesnt_go
 *  @date   2020-13-04
 ***********************************************/

#ifndef DRAWHEART_H
#define DRAWHEART_H


// Include standard library C++ libraries.
#include <string>
// Project header files
#include "command/AbstractCommand.hpp"
#include "command/Pixel.hpp"
#include "command/CommandDescription.hpp"
// Anytime we want to implement a new command in our paint tool,
// we have to inherit from the command class.
// This forces us to implement an 'execute' and 'undo' command.

/*! \brief Object for the DrawHeartCommand command, which inherits from AbstractCommand class
 */
class DrawHeartCommand : public AbstractCommand{
    private:
   	    std::vector<Pixel> getHeartPixels();
    public:
        DrawHeartCommand(const CommandDescription & commandDescription, App* mainApp);
        bool execute() override;
};

#endif
