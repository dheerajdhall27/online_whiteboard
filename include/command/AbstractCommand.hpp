/**
*  @file   AbstractCommand.hpp
*  @brief Object for the AbstractCommand command, which inherits from Command class and provides code that is common for all of the draw commands
*  @author Mike and van_doesnt_go
*  @date   2020-13-04
***********************************************/

#ifndef APP_ABSTRACTCOMMAND_HPP
#define APP_ABSTRACTCOMMAND_HPP


#include <App.hpp>
#include "Command.hpp"
#include "Pixel.hpp"

/*! \brief Object for the AbstractCommand command, which inherits from Command class and provides code that is common for all of the draw commands
 */
class AbstractCommand : public Command {
    protected:
        Pixel _pixelData;
        App *app;

        std::stack<std::vector<Pixel>> pixelVector;

        static sf::Color getColor(const CommandDescription &commandDescription, App* mainApp) {
            switch(commandDescription) {
                case CommandDescription::ServerCommand:
                    return mainApp->getServerCurrentBrushColor();
                case CommandDescription::LocalCommand:
                    return mainApp->getCurrentBrushColor();
            }
        }
    public:
        explicit AbstractCommand(CommandDescription commandDescription, App *mainApp) : Command(commandDescription),
            _pixelData(mainApp->getMouseX(), mainApp->getMouseY(), getColor( commandDescription, mainApp),
                    mainApp->getCurrentCanvasColor()){
            app = mainApp;
        }

        bool execute() override = 0;

        bool undo() override {
            std::vector<Pixel> data = pixelVector.top();
            std::vector<Pixel>::iterator iterator;
            for (iterator = data.begin(); iterator != data.end(); ++iterator) {
                if ((iterator->getX() < app->canvasWidth) &&
                    (iterator->getY() < app->canvasHeight)) {
                    app->GetImage().setPixel(iterator->getX(), iterator->getY(), app->getCurrentCanvasColor());
                }
            }
            pixelVector.pop();
            return true;
        }
};
#endif //APP_ABSTRACTCOMMAND_HPP
