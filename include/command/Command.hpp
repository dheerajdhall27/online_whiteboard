/**
 *  @file   Command.hpp
 *  @brief  Represents an actionable command by the user.
 *  @author Mike and van_doesnt_go
 *  @date   2020-13-04
 ***********************************************/
#ifndef COMMAND_HPP
#define COMMAND_HPP


// Include standard library C++ libraries.
#include <string>
#include "CommandDescription.hpp"


/*! \brief Object for the execute and undo commnands of the application
 */
class Command{
private:
    CommandDescription m_commandDescription;
public:
    explicit Command(CommandDescription commandDescription) : m_commandDescription(commandDescription) {}
    // Destructor for a command
    virtual ~Command();

    // Returns true or false if the command was able to succssfully
    // execute.
    // If it executes successfully, then that command is added to the
    // undo stack.
    // Each parameters also takes in a string name. While this may not be optimal,
    // it allows us to easily debug what each command is doing in a textual form.
    virtual bool execute() = 0;
    virtual bool undo() = 0;
};



#endif
