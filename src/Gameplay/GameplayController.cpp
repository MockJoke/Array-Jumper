#include "../../include/Gameplay/GameplayController.h"
#include "../../include/Global/ServiceLocator.h"
#include "../../include/Level/LevelData.h"
#include "../../include/Sound/SoundService.h"
#include "../../include/Main/GameService.h"

namespace Gameplay
{
	void GameplayController::intialize()
	{
	}

	void GameplayController::update()
	{
	}

	void GameplayController::render()
	{
	}

	void GameplayController::onPositionChanged(int position)
	{
		Level::BlockType value = Global::ServiceLocator::getInstance()->getLevelService()->getCurrentBoxValue(position);

		if (isObstacle(value))
			processObstacle();

		if (isEndBlock(value))
			processEndBlock();
	}

	void GameplayController::onDeath()
	{
		gameOver();
	}

	bool GameplayController::isObstacle(Level::BlockType value)
	{
		if (value == Level::BlockType::OBSTACLE_ONE || value == Level::BlockType::OBSTACLE_TWO)
			return true;

		return false;
	}

	bool GameplayController::isEndBlock(Level::BlockType value)
	{
		if (value == Level::BlockType::TARGET)
			return true;

		return false;
	}

	void GameplayController::processObstacle()
	{
		Global::ServiceLocator::getInstance()->getPlayerService()->takeDamage();
		Global::ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::DEATH);
	}

	void GameplayController::processEndBlock()
	{
		Global::ServiceLocator::getInstance()->getPlayerService()->levelComplete();
		Global::ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::LEVEL_COMPLETE);
		
		if(isLastLevel())
		{
			gameWon();
			return;
		}

		loadNextLevel();
	}

	bool GameplayController::isLastLevel()
	{
		return Global::ServiceLocator::getInstance()->getLevelService()->isLastLevel();
	}

	void GameplayController::startGame()
	{
		Main::GameService::setGameState(Main::GameState::GAMEPLAY);
		return Global::ServiceLocator::getInstance()->getLevelService()->resetLevels();
		return Global::ServiceLocator::getInstance()->getPlayerService()->resetPlayer();
	}

	void GameplayController::gameWon()
	{
		Main::GameService::setGameState(Main::GameState::CREDITS);
		Global::ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::GAME_WON);
	}

	void GameplayController::loadNextLevel()
	{
		Global::ServiceLocator::getInstance()->getLevelService()->loadNextLevel();
	}

	void GameplayController::gameOver()
	{
		Main::GameService::setGameState(Main::GameState::CREDITS);
		Global::ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::DEATH);
	}
}