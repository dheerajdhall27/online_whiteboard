/**
 *  @file   DrawCommand.cpp
 *  @brief  DrawCommand implementation, all drawing actions are commands.
 *  @author Mike and team van_doesnt_go
 *  @date   2020-08-02
 ***********************************************/

#include "App.hpp"  
#include "command/DrawCommand.hpp"


/*! \brief This constructor is used to create a DrawCommand object
*
*/
DrawCommand::DrawCommand(const CommandDescription & commandDescription, App* mainApp):
    AbstractCommand(commandDescription, mainApp) {
    app = mainApp;
}

/*! \brief This method draws a pixel on the canvas
*
*/
bool DrawCommand::execute() {
    if ((_pixelData.getX() <= app->canvasWidth) &&
        (_pixelData.getY() <= app->canvasHeight)) { 

	 app->GetImage().setPixel(_pixelData.getX(), _pixelData.getY(), _pixelData.getBrushColor());
       	
	return true;
    }

    return false;
}

/*! \brief  This method paints the canvas back to a previous state
*
*/
bool DrawCommand::undo() {
    if ((_pixelData.getX() < app->canvasWidth) &&
        (_pixelData.getY() < app->canvasHeight)) {
        app->GetImage().setPixel(_pixelData.getX(), _pixelData.getY(), _pixelData.getCanvasColor());
        return true;
    }
    return false;
}

