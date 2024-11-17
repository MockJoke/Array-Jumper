#include "../../include/UI/UIService.h"
#include "../../include/UI/Instructions/InstructionsUIController.h"
#include "../../include/Main/GameService.h"
#include "../../include/Global/ServiceLocator.h"
#include "../../include/UI/UIElement/TextView.h"

namespace UI
{
    UIService::UIService()
    {
        splash_screen_ui_controller = nullptr;
        main_menu_ui_controller = nullptr;
        credits_screen_ui_controller = nullptr;
        instructions_ui_controller = nullptr;
        gameplay_ui_controller = nullptr;

        createControllers();
    }

    UIService::~UIService()
    {
        onDestroy();
    }

    void UIService::createControllers()
    {
        splash_screen_ui_controller = new UI::SplashScreen::SplashScreenUIController();
        main_menu_ui_controller = new UI::MainMenu::MainMenuUIController();
        credits_screen_ui_controller = new UI::Credits::CreditsScreenUIController();
        instructions_ui_controller = new UI::Instructions::InstructionsUIController();
        gameplay_ui_controller = new UI::GameplayUI::GameplayUIController();
    }

    void UIService::initialize()
    {
        initializeUIElements();
        initializeControllers();
    }

    void UIService::initializeControllers()
    {
        splash_screen_ui_controller->initialize();
        main_menu_ui_controller->initialize();
        credits_screen_ui_controller->initialize();
        instructions_ui_controller->initialize();
        gameplay_ui_controller->initialize();
    }

    void UIService::initializeUIElements()
    {
        UI::UIElement::TextView::initializeTextView();
    }

    void UIService::update()
    {
        switch (Main::GameService::getGameState())
        {
        case Main::GameState::SPLASH_SCREEN:
            splash_screen_ui_controller->update();
            break;
        case Main::GameState::MAIN_MENU:
            main_menu_ui_controller->update();
            break;
        case Main::GameState::INSTRUCTIONS:
            instructions_ui_controller->update();
            break;
        case Main::GameState::CREDITS:
            credits_screen_ui_controller->update();
            break;
        case Main::GameState::GAMEPLAY:
            gameplay_ui_controller->update();
            break;
        }
    }

    void UIService::render()
    {
        switch (Main::GameService::getGameState())
        {
        case Main::GameState::SPLASH_SCREEN:
            splash_screen_ui_controller->render();
            break;
        case Main::GameState::MAIN_MENU:
            main_menu_ui_controller->render();
            break;
        case Main::GameState::INSTRUCTIONS:
            instructions_ui_controller->render();
            break;
        case Main::GameState::CREDITS:
            credits_screen_ui_controller->render();
            break;
        case Main::GameState::GAMEPLAY:
            gameplay_ui_controller->render();
            break;
        }
    }

    void UIService::showSplashScreen()
    {
        splash_screen_ui_controller->show();
    }

    void UIService::onDestroy()
    {
        delete (splash_screen_ui_controller);
        delete (main_menu_ui_controller);
        delete (credits_screen_ui_controller);
        delete (instructions_ui_controller);
        delete (gameplay_ui_controller);
    }
}