/**
*  @file   DrawDiagonalLineCommand.cpp
*  @brief  DrawDiagonalLineCommand implementation, command object for drawing with a diagonal line brush
*  @author Mike and team van_doesnt_go
*  @date   2020-08-02
***********************************************/

#include <command/DrawDiagonalLineCommand.hpp>
#include "Global.hpp"


/*! \brief This constructor is used to create a DrawCommand object
*
*/
DrawDiagonalLineCommand::DrawDiagonalLineCommand(const CommandDescription & commandDescription, App* mainApp):
    AbstractCommand(commandDescription, mainApp) {
}

/*! \brief This method draws a pixel on the canvas
*
*/
bool DrawDiagonalLineCommand::execute() {
    std::vector<Pixel> data = getLineCoords();
    pixelVector.push(data);

    std::vector<Pixel>::iterator it;
    for (it = data.begin(); it != data.end(); ++it){
        if ((it->getX() <= app->canvasWidth) &&
            (it->getY() <= app->canvasHeight)) {
            app->GetImage().setPixel(it->getX(), it->getY(), it->getBrushColor());
        }
    }
    return true;
}

/*! \brief This method calculates all of the pixels in a DiagonalLine Brush object and returns them in a vector 
*
*/
std::vector<Pixel> DrawDiagonalLineCommand::getLineCoords() {
    unsigned int x = _pixelData.getX();
    unsigned int y = _pixelData.getY();
    int width = Global::WINDOW_WIDTH/20;

    std::vector<Pixel> data;
    for (int i = 0; i<=width;i++){
        auto* p = new Pixel(x+i, y+i, _pixelData.getBrushColor(), _pixelData.getCanvasColor());
        data.push_back(*p);
        delete p;
    }

    return data;

}
