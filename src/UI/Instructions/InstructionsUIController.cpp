#include "../../../include/UI/Instructions/InstructionsUIController.h"
#include "../../../include/Main/GameService.h"
#include "../../../include/Graphics/GraphicService.h"
#include "../../../include/Sound/SoundService.h"
#include "../../../include/Event/EventService.h"
#include "../../../include/Global/Config.h"
#include "../../../include/Global/ServiceLocator.h"

namespace UI
{
    namespace Instructions
    {
        using namespace Global;
        using namespace UIElement;
        using namespace Main;
        using namespace Graphics;
        using namespace Sound;

        InstructionsUIController::InstructionsUIController()
        {
            createButtons();
            createImage();
            createText();
        }

        InstructionsUIController::~InstructionsUIController()
        {
            destroy();
        }

        void InstructionsUIController::initialize()
        {
            initializeTexts();
            initializeBackgroundImage();
            initializeButtons();
            registerButtonCallback();
        }

        void InstructionsUIController::createImage()
        {
            background_image = new ImageView();
        }

        void InstructionsUIController::createButtons()
        {
            menu_button = new ButtonView();
        }

        void InstructionsUIController::createText()
        {
            for (int i = 0; i < number_of_instructions; i++)
            {
                instructions_text_list.push_back(new TextView());
            }
        }

        void InstructionsUIController::initializeBackgroundImage()
        {
            sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();

            background_image->initialize(Config::array_jumper_bg_texture_path, game_window->getSize().x, game_window->getSize().y, sf::Vector2f(0, 0));
            background_image->setImageAlpha(background_alpha);
        }

        void InstructionsUIController::initializeButtons()
        {
            menu_button->initialize("Menu Button", Config::menu_button_texture_path, button_width, button_height, sf::Vector2f(0, menu_button_y_position));
            menu_button->setCentreAlinged();
        }

        void InstructionsUIController::initializeTexts()
        {
            for (int i = 0; i < instructions_text_list.size(); i++)
            {
                instructions_text_list[i]->initialize(instructions[i], sf::Vector2f(0, top_offset + (text_spacing * i)), FontType::BUBBLE_BOBBLE, font_size, text_color);
                instructions_text_list[i]->setTextCentreAligned();
            }
        }

        void InstructionsUIController::registerButtonCallback()
        {
            menu_button->registerCallbackFuntion(std::bind(&InstructionsUIController::menuButtonCallback, this));
        }

        void InstructionsUIController::menuButtonCallback()
        {
            ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
            GameService::setGameState(GameState::MAIN_MENU);
        }

        void InstructionsUIController::update()
        {
            background_image->update();
            menu_button->update();

            for (int i = 0; i < instructions_text_list.size(); i++)
            {
                instructions_text_list[i]->update();
            }
        }

        void InstructionsUIController::render()
        {
            background_image->render();
            menu_button->render();

            for (int i = 0; i < instructions_text_list.size(); i++)
            {
                instructions_text_list[i]->render();
            }
        }

        void InstructionsUIController::show()
        {
            background_image->show();
            menu_button->show();

            for (int i = 0; i < instructions_text_list.size(); i++)
            {
                instructions_text_list[i]->show();
            }
        }

        void InstructionsUIController::destroy()
        {
            delete (background_image);
            delete (menu_button);

            for (int i = 0; i < instructions_text_list.size(); i++)
            {
                delete (instructions_text_list[i]);
            }
        }
    }
}