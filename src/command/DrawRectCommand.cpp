/**
*  @file   DrawRectCommand.cpp
*  @brief  DrawRectCommand implementation, a command for drawing with the rectangle brush
*  @author Mike and team van_doesnt_go
*  @date   2020-08-02
***********************************************/

#include <command/DrawRectCommand.hpp>
#include "Global.hpp"


/*! \brief This constructor is used to create a DrawCommand object
*
*/
DrawRectCommand::DrawRectCommand(const CommandDescription & commandDescription, App* mainApp):
    AbstractCommand(commandDescription, mainApp) {
}

/*! \brief This method draws a pixel on the canvas
*
*/
bool DrawRectCommand::execute() {
    std::vector<Pixel> data = getRectCoords();
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

/*! \brief This method calculates the coordinates of each pixel in the Rectangle brush and adds them to a vector 
*
*/
std::vector<Pixel> DrawRectCommand::getRectCoords() {
    unsigned int x = _pixelData.getX();
    unsigned int y = _pixelData.getY();
    int width = Global::WINDOW_WIDTH/20;
    int height = Global::WINDOW_HEIGHT/20;

    std::vector<Pixel> data;

    for (int i = 0; i<=width;i++){
        auto*p1 = new Pixel(x+i,y,_pixelData.getBrushColor(), _pixelData.getCanvasColor());
        auto*p2 = new Pixel(x+i,y+height,_pixelData.getBrushColor(), _pixelData.getCanvasColor());

        data.push_back(*p1);
        data.push_back(*p2);

        delete p1;
        delete p2;
    }

    for (int j = 0; j<=height;j++){
        auto*p1 = new Pixel(x,y+j,_pixelData.getBrushColor(), _pixelData.getCanvasColor());
        auto*p2 = new Pixel(x+width,y+j,_pixelData.getBrushColor(), _pixelData.getCanvasColor());

        data.push_back(*p1);
        data.push_back(*p2);

        delete p1;
        delete p2;
    }

    return data;

}
