#include "../../../include/UI/Gameplay/GameplayUIController.h"
#include "../../../include/Global/ServiceLocator.h"

#include <sstream>
#include <iomanip>
#include <iostream>

namespace UI
{
	namespace GameplayUI
	{
		GameplayUIController::GameplayUIController()
		{
			createTexts();
		}

		GameplayUIController::~GameplayUIController()
		{
			destroy();
		}

		void GameplayUIController::initialize()
		{
			initializeTexts();
		}

		void GameplayUIController::update()
		{
			updateLifeCountText();
		}

		void GameplayUIController::render()
		{
			life_count_text->render();
		}

		void GameplayUIController::createTexts()
		{
			life_count_text = new UI::UIElement::TextView();
		}

		void GameplayUIController::initializeTexts()
		{
			initializeLifeCountText();
		}

		void GameplayUIController::initializeLifeCountText()
		{
			float windowWidth = Global::ServiceLocator::getInstance()->getGraphicService()->getGameWindow()->getSize().x;
			float x_position = (static_cast<float>(windowWidth) - right_offset);
			float y_position = top_offset;

			life_count_text->initialize("0", sf::Vector2f(x_position, y_position), UI::UIElement::FontType::BUBBLE_BOBBLE, font_size, sf::Color::White);
		}

		void GameplayUIController::updateLifeCountText()
		{
			int life_count = Global::ServiceLocator::getInstance()->getPlayerService()->getCurrentLives();

			std::string life_count_string = "LIFE: " + std::to_string(life_count);

			life_count_text->setText(life_count_string);
			life_count_text->update();
		}

		void GameplayUIController::destroy()
		{
			delete(life_count_text);
		}

	}
}