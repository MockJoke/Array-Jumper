#pragma once
#include "../../include/Event/EventService.h"
#include "MovementDirection.h"

namespace Player
{
	class PlayerView;
	class PlayerModel;
	enum class PlayerState;

	class PlayerController
	{
	private:
		PlayerModel* player_model;
		PlayerView* player_view;

		Event::EventService* event_service;

		void readInput();
		void move(MovementDirection direction);
		void jump(MovementDirection direction);
		bool isPositionInBound(int targetPosition);
		void onDeath();

		void destroy();

	public:
		PlayerController();
		~PlayerController();

		void initialize();
		void update();
		void render();

		PlayerState getPlayerState();
		void setPlayerState(PlayerState new_player_state);

		int getCurrentPosition();
		int getCurrentLives();

		void takeDamage();
		void resetPlayer();
	};
}