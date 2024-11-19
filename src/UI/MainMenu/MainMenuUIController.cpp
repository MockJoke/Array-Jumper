#include "../../../include/UI/MainMenu/MainMenuUIController.h"
#include "../../../include/Main/GameService.h"
#include "../../../include/Global/ServiceLocator.h"
#include "../../../include/Graphics/GraphicService.h"
#include "../../../include/Sound/SoundService.h"
#include "../../../include/Event/EventService.h"
#include "../../../include/Global/Config.h"

namespace UI
{
    namespace MainMenu
    {
        MainMenuUIController::MainMenuUIController()
        {
            createImage();
            createButtons();
        }

        MainMenuUIController::~MainMenuUIController()
        {
            destroy();
        }

        void MainMenuUIController::createImage()
        {
            background_image = new UI::UIElement::ImageView();
        }

        void MainMenuUIController::createButtons()
        {
            play_button = new UI::UIElement::ButtonView();
            instructions_button = new UI::UIElement::ButtonView();
            quit_button = new UI::UIElement::ButtonView();
        }

        void MainMenuUIController::initialize()
        {
            initializeBackgroundImage();
            initializeButtons();
            registerButtonCallback();
        }

        void MainMenuUIController::initializeBackgroundImage()
        {
            sf::RenderWindow* game_window = Global::ServiceLocator::getInstance()->getGraphicService()->getGameWindow();

            background_image->initialize(Global::Config::array_jumper_bg_texture_path, game_window->getSize().x, game_window->getSize().y, sf::Vector2f(0, 0));
            background_image->setImageAlpha(background_alpha);
        }

        void MainMenuUIController::initializeButtons()
        {
            play_button->initialize("Play Button", Global::Config::play_button_texture_path, button_width, button_height, sf::Vector2f(0, play_button_y_position));
            instructions_button->initialize("Instructions Button", Global::Config::instructions_button_texture_path, button_width, button_height, sf::Vector2f(0, instructions_button_y_position));
            quit_button->initialize("Quit Button", Global::Config::quit_button_texture_path, button_width, button_height, sf::Vector2f(0, quit_button_y_position));

            play_button->setCentreAlinged();
            instructions_button->setCentreAlinged();
            quit_button->setCentreAlinged();
        }

        void MainMenuUIController::registerButtonCallback()
        {
            play_button->registerCallbackFuntion(std::bind(&MainMenuUIController::playButtonCallback, this));
            instructions_button->registerCallbackFuntion(std::bind(&MainMenuUIController::instructionsButtonCallback, this));
            quit_button->registerCallbackFuntion(std::bind(&MainMenuUIController::quitButtonCallback, this));
        }

        void MainMenuUIController::playButtonCallback()
        {
            Global::ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::BUTTON_CLICK);
            Global::ServiceLocator::getInstance()->getGameplayService()->startGame();
        }

        void MainMenuUIController::instructionsButtonCallback()
        {
            Global::ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::BUTTON_CLICK);
            Main::GameService::setGameState(Main::GameState::INSTRUCTIONS);
        }

        void MainMenuUIController::quitButtonCallback()
        {
            Global::ServiceLocator::getInstance()->getGraphicService()->getGameWindow()->close();
        }

        void MainMenuUIController::update()
        {
            background_image->update();
            play_button->update();
            instructions_button->update();
            quit_button->update();
        }

        void MainMenuUIController::render()
        {
            background_image->render();
            play_button->render();
            instructions_button->render();
            quit_button->render();
        }

        void MainMenuUIController::show()
        {
            background_image->show();
            play_button->show();
            instructions_button->show();
            quit_button->show();
        }

        void MainMenuUIController::destroy()
        {
            delete (play_button);
            delete (instructions_button);
            delete (quit_button);
            delete (background_image);
        }
    }
}