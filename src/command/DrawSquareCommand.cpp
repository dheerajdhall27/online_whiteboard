/**
 *  @file   DrawSquareCommand.cpp
 *  @brief  DrawSprayPaintCommand implementation,  a command for drawing with the Square brush
 *  @author Mike and team van_doesnt_go
 *  @date   2020-08-02
 ***********************************************/

#include "App.hpp"
#include "command/DrawSquareCommand.hpp"


/*! \brief This constructor is used to create a DrawSquareCommand Command
*
*/
DrawSquareCommand::DrawSquareCommand(const CommandDescription & commandDescription, App* mainApp):
    AbstractCommand(commandDescription, mainApp) {
    sideLength = 15;
}


/*! \brief This method draws a pixel on the canvas
*
*/
bool DrawSquareCommand::execute() {
   std::vector<Pixel> shapeData = getSquarePixels(_pixelData.getX(), _pixelData.getY());
   pixelVector.push(shapeData); 
   std::vector<Pixel>::iterator iterator; 
   
   
   for(iterator = shapeData.begin(); iterator != shapeData.end(); ++iterator) {
   	if ((_pixelData.getX() <= app->canvasWidth) &&
           (_pixelData.getY() <= app->canvasHeight)) {
            app->GetImage().setPixel(iterator->getX(), iterator->getY(), iterator->getBrushColor());   
   	}
   }  
  return true;
}

/*! \brief This function returns a vector that contains all the pixels of a square
*
*/
std::vector<Pixel> DrawSquareCommand::getSquarePixels(unsigned int x, unsigned int y) {
    std::vector<Pixel> data;

    for(int i = 0;i <= sideLength; i++) {
        //Horizontal
        Pixel p1(x + i, y, _pixelData.getBrushColor(), _pixelData.getCanvasColor());
        Pixel p2(x + i, y + sideLength, _pixelData.getBrushColor(),
                _pixelData.getCanvasColor());

        //Vertical
        Pixel p3(x, y + i, _pixelData.getBrushColor(), _pixelData.getCanvasColor());
        Pixel p4(x + sideLength, y + i, _pixelData.getBrushColor(),
                _pixelData.getCanvasColor());

        data.push_back(p1);
        data.push_back(p2);
        data.push_back(p3);
        data.push_back(p4);
    }


    return data;
}
