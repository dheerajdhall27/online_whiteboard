/**
*  @file   DrawDiagonalLineCommand.hpp
*  @brief  Object for the DrawDiagonalLineCommand command, which inherits from AbstractCommand class
*  @author Mike and Van_doesnt_go
*  @date   2020-04-13
***********************************************/

#ifndef APP_DRAWDIAGONALLINECOMMAND_HPP
#define APP_DRAWDIAGONALLINECOMMAND_HPP


// Include standard library C++ libraries.
#include <string>
// Project header files
#include "command/AbstractCommand.hpp"
#include "command/Pixel.hpp"
#include "command/CommandDescription.hpp"
#include "App.hpp"


// Anytime we want to implement a new command in our paint tool,
// we have to inherit from the command class.
// This forces us to implement an 'execute' and 'undo' command.

/*! \brief Object for the DrawDiagonalLineCommand command, which inherits from AbstractCommand class
 */
class DrawDiagonalLineCommand : public AbstractCommand{
private:
    std::vector<Pixel> getLineCoords();
public:
    DrawDiagonalLineCommand(const CommandDescription & commandDescription, App* mainApp);
    bool execute() override;
};


#endif
