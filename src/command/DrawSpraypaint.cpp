/**
*  @file   DrawSpraypaint.cpp
*  @brief  DrawSprayPaintCommand implementation,  a command for drawing with the SprayPaint brush
*  @author Mike and and team van_doesnt_go
*  @date   2020-05-04
***********************************************/
#include "App.hpp"
#include "command/DrawSprayPaintCommand.hpp"

using namespace std;

/*! \brief This constructor is used to create a DrawCommand object
*
*/
DrawSprayPaintCommand::DrawSprayPaintCommand(const CommandDescription & commandDescription, App* mainApp):
    AbstractCommand(commandDescription, mainApp) {
}

/*! \brief This method draws a pixel on the canvas
*
*/
bool DrawSprayPaintCommand::execute() {
    if ((_pixelData.getX() <= app->canvasWidth) &&
        (_pixelData.getY() <= app->canvasHeight)) {
            spray(_pixelData.getX(), _pixelData.getY(), _pixelData.getBrushColor());
        return true;
    }

    return false;
}

/*! \brief This method randomly selects a pixel, that makes up a part of the spray paint brush, and colors
 the pixel Accordingly
*
*/
void DrawSprayPaintCommand::spray(unsigned int x, unsigned int y, sf::Color color){
    for(int i = 0; i < 8; i++){
        unsigned int randomX = x + (rand() % ( x + 10 - x + 1));
        unsigned int randomY = y + (rand() % ( y + 10 - y + 1));
        point p;
        p.x = randomX;
        p.y = randomY;
        p.color = color;
        allPoints.push_back(p);
        app->GetImage().setPixel(randomX, randomY, color);

    }
}

/*! \brief     This method paints the canvas back to a previous state
*
*/
bool DrawSprayPaintCommand::undo() {
    int s = allPoints.size();

    for (int i = 0; i < s; i++){
        if ((allPoints[i].x < app->canvasWidth) &&
            (allPoints[i].y < app->canvasHeight)) {
            app->GetImage().setPixel(allPoints[i].x, allPoints[i].y, _pixelData.getCanvasColor());
        }
    }
    return true;
}

