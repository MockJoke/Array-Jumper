#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "../../include/Graphics/GraphicService.h"
#include "../../include/UI/UIService.h"
#include "../../include/Sound/SoundService.h"
#include "../../include/Global/ServiceLocator.h"

namespace Main
{

	enum class GameState
	{
		BOOT,
		SPLASH_SCREEN,
		MAIN_MENU,
		GAMEPLAY,
		INSTRUCTIONS,
		CREDITS,
	};

	class GameService
	{
	private:

		static GameState current_state;
		Global::ServiceLocator* service_locator;
		sf::RenderWindow* game_window;

		void initialize();
		void showSplashScreen();

	public:
		GameService();
		virtual ~GameService();

		void ignite();
		void update();
		void render();
		bool isRunning();

		static void setGameState(GameState new_state);
		static GameState getGameState();
	};
}