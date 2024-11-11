#pragma once
#include "../../include/Graphics/GraphicService.h"
#include "../../include/Event/EventService.h"
#include "../../include/UI/UIService.h"
#include "../../include/Sound/SoundService.h"
#include "../../include/Level/LevelService.h"
#include "../../include/Player/PlayerService.h"

namespace Global
{
    class ServiceLocator
    {
    private:
        Graphics::GraphicService* graphic_service;
        Event::EventService* event_service;
        Sound::SoundService* sound_service;
        UI::UIService* ui_service;
        Level::LevelService* level_service;
        Player::PlayerService* player_service;

        ~ServiceLocator();

        void createServices();
        void clearAllServices();

    public:
        ServiceLocator();
        static ServiceLocator* getInstance();

        void initialize();
        void update();
        void render();

        Graphics::GraphicService* getGraphicService();
        Event::EventService* getEventService();
        Sound::SoundService* getSoundService();
        UI::UIService* getUIService();
        Level::LevelService* getLevelService();
        Player::PlayerService* getPlayerService();
    };
}