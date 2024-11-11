#include "../../include/Global/ServiceLocator.h"
#include "../../include/Main/GameService.h"
#include "../../include/Event/EventService.h"

namespace Global
{
	ServiceLocator::ServiceLocator()
	{
		graphic_service = nullptr;
		event_service = nullptr;
		sound_service = nullptr;
		ui_service = nullptr;
		level_service = nullptr;
		player_service = nullptr;

		createServices();
	}

	ServiceLocator::~ServiceLocator() { clearAllServices(); }

	void ServiceLocator::createServices()
	{
		graphic_service = new Graphics::GraphicService();
		event_service = new Event::EventService();
		sound_service = new Sound::SoundService();
		ui_service = new UI::UIService();
		level_service = new Level::LevelService();
		player_service = new Player::PlayerService();
	}

	void ServiceLocator::initialize()
	{
		graphic_service->initialize();
		event_service->initialize();
		sound_service->initialize();
		ui_service->initialize();
		level_service->intialize();
		player_service->initialize();
	}

	void ServiceLocator::update()
	{
		graphic_service->update();
		event_service->update();
		ui_service->update();

		if (Main::GameService::getGameState() == Main::GameState::GAMEPLAY)
		{
			level_service->update();
			player_service->update();
		}
	}

	void ServiceLocator::render()
	{
		graphic_service->render();
		ui_service->render();

		if (Main::GameService::getGameState() == Main::GameState::GAMEPLAY)
		{
			level_service->render();
			player_service->render();
		}
	}

	void ServiceLocator::clearAllServices()
	{
		delete(graphic_service);
		delete(event_service);
		delete(sound_service);
		delete(ui_service);
		delete(level_service);
		delete(player_service);
	}

	ServiceLocator* ServiceLocator::getInstance()
	{
		static ServiceLocator instance;
		return &instance;
	}

	Graphics::GraphicService* ServiceLocator::getGraphicService() { return graphic_service; }

	Event::EventService* ServiceLocator::getEventService() { return event_service; }

	Sound::SoundService* ServiceLocator::getSoundService() { return sound_service; }

	UI::UIService* ServiceLocator::getUIService() { return ui_service; }

	Level::LevelService* ServiceLocator::getLevelService() { return level_service; }

	Player::PlayerService* ServiceLocator::getPlayerService() { return player_service; }
}