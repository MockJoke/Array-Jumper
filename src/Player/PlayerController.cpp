#include "../../include/Player/PlayerController.h"
#include "../../include/Player/PlayerView.h"
#include "../../include/Player/PlayerModel.h"
#include "../../include/Global/ServiceLocator.h"
#include "../../include/Level/LevelModel.h"
#include "../../include/Sound/SoundService.h"

namespace Player
{
	PlayerController::PlayerController()
	{
		player_model = new PlayerModel();
		player_view = new PlayerView(this);
	}

	PlayerController::~PlayerController() { destroy(); }

	void PlayerController::initialize()
	{
		player_model->initialize();
		player_view->initialize();

		event_service = Global::ServiceLocator::getInstance()->getEventService();

		resetPlayer();
	}

	void PlayerController::update()
	{
		player_view->update();
	}

	void PlayerController::render()
	{
		player_view->render();
	}

	void PlayerController::readInput()
	{
		if (event_service->pressedRightArrowKey() || event_service->pressedDKey())
		{
			if (event_service->heldSpaceKey())
				jump(MovementDirection::FORWARD);
			else
				move(MovementDirection::FORWARD);
		}

		if (event_service->pressedLeftArrowKey() || event_service->pressedAKey())
		{
			if (event_service->heldSpaceKey())
				jump(MovementDirection::BACKWARD);
			else
				move(MovementDirection::BACKWARD);
		}
	}

	void PlayerController::move(MovementDirection direction)
	{
		int steps, targetPosition;

		switch (direction)
		{
		case MovementDirection::FORWARD:
			steps = 1;
			break;
		case MovementDirection::BACKWARD:
			steps = -1;
			break;
		default:
			steps = 0;
			break;
		}
		
		targetPosition = player_model->getCurrentPosition() + steps;

		if (!isPositionInBound(targetPosition))
			return;

		player_model->setCurrentPosition(targetPosition);
		Global::ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::MOVE);
		Global::ServiceLocator::getInstance()->getGameplayService()->onPositionChanged(targetPosition);
	}

	void PlayerController::jump(MovementDirection direction)
	{
		int current_position = player_model->getCurrentPosition();
		BlockType box_value = ServiceLocator::getInstance()->getLevelService()->getCurrentBoxValue(current_position);
		int steps, targetPosition;

		switch (direction)
		{
		case MovementDirection::FORWARD:
			steps = box_value;
			break;
		case MovementDirection::BACKWARD:
			steps = -box_value;
			break;
		default:
			steps = 0;
			break;
		}

		targetPosition = current_position + steps;

		if (!isPositionInBound(targetPosition))
			return;

		player_model->setCurrentPosition(targetPosition);

		Global::ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::JUMP);
		Global::ServiceLocator::getInstance()->getGameplayService()->onPositionChanged(targetPosition);
	}

	bool PlayerController::isPositionInBound(int targetPosition)
	{
		if(targetPosition >= 0 && targetPosition < Level::LevelData::NUMBER_OF_BOXES)
			return true;

		return false;
	}

	void PlayerController::takeDamage()
	{
		player_model->decreamentLife();

		if (player_model->getCurrentLives() <= 0)
			onDeath();
		else
			player_model->resetPosition();
	}

	void PlayerController::onDeath()
	{
		Global::ServiceLocator::getInstance()->getGameplayService()->onDeath();
		player_model->resetPlayer();
	}

	PlayerState PlayerController::getPlayerState()
	{
		return player_model->getPlayerState();
	}

	void PlayerController::setPlayerState(PlayerState new_player_state)
	{
		player_model->setPlayerState(new_player_state);
	}

	int PlayerController::getCurrentPosition()
	{
		return player_model->getCurrentPosition();
	}

	int PlayerController::getCurrentLives()
	{
		return player_model->getCurrentLives();
	}

	void PlayerController::resetPlayer()
	{
		player_model->setCurrentPosition(0);
		player_model->setPlayerState(PlayerState::ALIVE);
	}

	void PlayerController::destroy()
	{
		delete (player_model);
		delete (player_view);
	}
}