/**
*  @file   DrawCircleCommand.hpp
*  @brief  Object for the DrawCircleCommand command, which inherits from AbstractCommand class
*  @author Mike and van_doesnt_go
*  @date   2020-13-04
***********************************************/

#ifndef APP_DRAWCIRCLECOMMAND_HPP
#define APP_DRAWCIRCLECOMMAND_HPP
#include <command/AbstractCommand.hpp>
#include <command/Pixel.hpp>
#include <command/CommandDescription.hpp>
#include <vector>
#include <stack>
#include "App.hpp"

/*! \brief Object for the DrawCircleCommand command, which inherits from AbstractCommand class
 */
class DrawCircleCommand : public AbstractCommand {
    private:
        int radius;
//        std::stack<std::vector<Pixel>> pixelVector;

        std::vector<Pixel> getCircleCoords();
    public:
        DrawCircleCommand(const CommandDescription & commandDescription, App* mainApp);
        bool execute() override;
};

#endif //APP_DRAWCIRCLECOMMAND_HPP
