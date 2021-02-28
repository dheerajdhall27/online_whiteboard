/**
*  @file   DrawCircleCommand.cpp
*  @brief Implementation of DrawCircleCommand, represents an object for the Draw Circle Command
*  @author Mike and team VanDoesn'tGo
*  @date   2020-08-02
***********************************************/
#include <command/DrawCircleCommand.hpp>
#include <cmath>
#include <iostream>

/*! \brief This constructor is used to create a DrawCommand object
*
*/
DrawCircleCommand::DrawCircleCommand(const CommandDescription &commandDescription, App *mainApp) :
     AbstractCommand(commandDescription, mainApp) {
    radius = 10;
}


/*! \brief This method draws a Circle shape on the canvas
*
*/
bool DrawCircleCommand::execute() {
    std::vector<Pixel> data = getCircleCoords();
    pixelVector.push(data);

    std::vector<Pixel>::iterator it;

    for (it = data.begin(); it != data.end(); ++it) {
        if ((it->getX() <= app->canvasWidth) &&
            (it->getY() <= app->canvasHeight)) {
            app->GetImage().setPixel(it->getX(), it->getY(), it->getBrushColor());
        }
    }

    return true;
}

/*! \brief This method calculates the pixel coordinates which make up the circle brush and return them in a vector
*
*/
std::vector<Pixel> DrawCircleCommand::getCircleCoords() {
    unsigned int x = _pixelData.getX();
    unsigned int y = _pixelData.getY();

    std::vector<Pixel> data;
    for (int angle = 0; angle <= 360; angle += 1) {
        auto *p = new Pixel((unsigned int)(x + radius * cos(angle)), (unsigned int) (y + radius * sin(angle)),
                            _pixelData.getBrushColor(), _pixelData.getCanvasColor());
        data.push_back(*p);
        delete p;
    }

    return data;
}

