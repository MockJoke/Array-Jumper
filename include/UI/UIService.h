#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "../../include/UI/SplashScreen/SplashScreenUIController.h"
#include "../../include/UI/MainMenu/MainMenuUIController.h"
#include "../../include/UI/Instructions/InstructionsUIController.h"
#include "../../include/UI/Credits/CreditsScreenUIController.h"
#include "../../include/UI/Gameplay/GameplayUIController.h"

namespace UI
{
	class UIService
	{
	private:
		SplashScreen::SplashScreenUIController* splash_screen_ui_controller;
		MainMenu::MainMenuUIController* main_menu_ui_controller;
		Credits::CreditsScreenUIController* credits_screen_ui_controller;
		Instructions::InstructionsUIController* instructions_ui_controller;
		GameplayUI::GameplayUIController* gameplay_ui_controller;

		void createControllers();
		void initializeUIElements();
		void initializeControllers();
		void onDestroy();

	public:
		UIService();
		~UIService();

		void initialize();
		void update();
		void render();

		void showSplashScreen();
	};
}