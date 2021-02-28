/**
 *  @file   DrawHeartCommand.cpp
 *  @brief  DrawHeartCommand implementation, a command for drawing with the heart brush
 *  @author Mike and created by Lunden and refactored by team van_doesnt_go
 *  @date   2020-08-02
 ***********************************************/

#include "App.hpp"
#include "command/DrawHeartCommand.hpp"


/*! \brief This constructor is used to create a DrawHeartCommand Command
*
*/
DrawHeartCommand::DrawHeartCommand(const CommandDescription & commandDescription, App* mainApp):
    AbstractCommand(commandDescription, mainApp) {
}

/*! \brief This constructor adds all the pixels of a heart to a vector and then returns it
*
*/
std::vector<Pixel> DrawHeartCommand::getHeartPixels() {
     	unsigned int x = _pixelData.getX();
     	unsigned int y = _pixelData.getY();

    	std::vector<Pixel> data;
     	//First Row of Hearts Pixels
     	auto* frOne = new Pixel(x + 1, y + 1,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
	data.push_back(*frOne);     
	auto* frTwo = new Pixel(x + 2, y + 1,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
    	data.push_back(*frTwo);
	auto* frThre = new Pixel(x + 6, y + 1,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*frThre);
	auto* frFour = new Pixel(x + 7, y + 1,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*frFour);
	
	delete frOne;
	delete frTwo;
	delete frThre;
	delete frFour;

	//Second Row of Heart Pixels 
     	auto* srOne = new Pixel(x, y + 2,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*srOne);
	auto* srTwo = new Pixel(x + 1, y + 2,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*srTwo);
	auto* srThree = new Pixel(x + 2, y + 2,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*srThree);
	auto* srFour = new Pixel(x + 3, y + 2,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*srFour);
	auto* srFive = new Pixel(x + 5, y + 2,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*srFive);
	auto* srSix = new Pixel(x + 6, y + 2,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
    	data.push_back(*srSix);
	auto* srSeven = new Pixel(x + 7, y + 2,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*srSeven);
	auto* srEight = new Pixel(x + 8, y + 2,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*srEight);

	delete srOne;
        delete srTwo;
        delete srThree;
        delete srFour;
        delete srFive;
        delete srSix;
        delete srSeven;
        delete srEight;
	
	//Third Row of Heart Pixels
     	auto* trOne = new Pixel(x, y + 3,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*trOne);
	auto* trTwo = new Pixel(x + 1, y + 3,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*trTwo);
	auto* trThree = new Pixel(x + 2, y + 3,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*trThree);
	auto* trFour = new Pixel(x + 3, y + 3,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*trFour);
	auto* trFive = new Pixel(x + 5, y + 3,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*trFive);
	auto* trSix = new Pixel(x + 6, y + 3,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*trSix);
	auto* trSeven = new Pixel(x + 7, y + 3,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*trSeven);
	auto* trEight = new Pixel(x + 8, y + 3,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*trEight);
	
	delete trOne;
        delete trTwo;
        delete trThree;
        delete trFour;
        delete trFive;
        delete trSix;
        delete trSeven;
        delete trEight;
	
	//Fourth Row of Heart Pixels
     	auto* froOne = new Pixel(x, y + 4,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*froOne);
	auto* froTwo = new Pixel(x + 1, y + 4,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*froTwo);
	auto* froThree = new Pixel(x + 2, y + 4,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*froThree);
	auto* froFour = new Pixel(x + 3, y + 4,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*froFour);
	auto* froFive = new Pixel(x + 5, y + 4,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*froFive);
	auto* froSix = new Pixel(x + 6, y + 4,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*froSix);
	auto* froSeven = new Pixel(x + 7, y + 4,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*froSeven);
	auto* froEight = new Pixel(x + 8, y + 4,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*froEight);
	auto* froNine = new Pixel(x + 4, y + 4,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*froNine);
	
	delete froOne; 
	delete froTwo;
	delete froThree;
	delete froFour;
	delete froFive;
	delete froSix;
	delete froSeven;
	delete froEight;
	delete froNine;


	//Fifth Row of Heart Pixels
     	auto* fioOne = new Pixel(x + 1, y + 5,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
    	data.push_back(*fioOne);
	auto* fioTwo = new Pixel(x + 2, y + 5,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*fioTwo);
	auto* fioThree = new Pixel(x + 3, y + 5,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*fioThree);
	auto* fioFour = new Pixel(x + 4, y + 5,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*fioFour);
	auto* fioFive = new Pixel(x + 5, y + 5,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
     	data.push_back(*fioFive);
	auto* fioSix = new Pixel(x + 6, y + 5,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
      	data.push_back(*fioSix);
	auto* fioSeven = new Pixel(x + 7, y + 5,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
      	data.push_back(*fioSeven);
	
	delete fioOne;
	delete fioTwo;
	delete fioThree;
	delete fioFour;
	delete fioFive;
	delete fioSix;
	delete fioSeven;

	//Sixth Row of Heart Pixels
      
	auto* sioOne = new Pixel(x + 2, y + 6,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
      	data.push_back(*sioOne);
	auto* sioTwo = new Pixel(x + 3, y + 6,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
      	data.push_back(*sioTwo);
	auto* sioThree = new Pixel(x + 4, y + 6,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
        data.push_back(*sioThree);
	auto* sioFour = new Pixel(x + 5, y + 6,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
        data.push_back(*sioFour);
	auto* sioFive = new Pixel(x + 6, y + 6,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
      	data.push_back(*sioFive);
	
	delete sioOne;
	delete sioTwo;
	delete sioThree;
	delete sioFour;
	delete sioFive;

	//Seventh Row of Heart Pixels 
      	
	auto* sevOne = new Pixel(x + 3, y + 7,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
      	data.push_back(*sevOne);
	auto* sevTwo = new Pixel(x + 4, y + 7,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
      	data.push_back(*sevTwo);
	auto* sevThree = new Pixel(x + 5, y + 7,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
      	data.push_back(*sevThree);
	
	delete sevOne;
	delete sevTwo;
	delete sevThree;

	//Eight Row of Heart Pixels
      	
	auto* eiOne = new Pixel(x + 4, y + 8,
                 _pixelData.getBrushColor(), _pixelData.getCanvasColor());
	data.push_back(*eiOne);
	
	delete eiOne;
      
	return data;

 }

/*! \brief This method draws a pixel on the canvas
*
*/
bool DrawHeartCommand::execute() {
    
    std::vector<Pixel> data = getHeartPixels();
    pixelVector.push(data);

    std::vector<Pixel>::iterator iterator;

    for(iterator = data.begin(); iterator != data.end(); ++iterator){
    	if ((iterator->getX() <= app->canvasWidth) &&
        (iterator->getY() <= app->canvasHeight)) {
        app->GetImage().setPixel(iterator->getX(), iterator->getY(), iterator->getBrushColor());
        
    	}

    }
    return true;
}


