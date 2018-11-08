#include "StageManager.h"
#include "PlanningStage.h"
#include "GameplayStage.h"

StageManager* StageManager::fInstance = 0;
Stage* StageManager::fStage = 0;

StageManager* StageManager::Instance()
{
	if (!fInstance)
	{
		fInstance = new StageManager(StageEnum::Planning);
	}
	return fInstance;
}

StageManager::StageManager(StageEnum lState)
{
	isQuit = false;
	SetState(lState);
}

void StageManager::SetState(StageEnum lState)
{
	switch (lState)
	{
	case Planning:
		fStage = PlanningStage::Instance();
		break;
	case Gameplay:
		fStage = GameplayStage::Instance();
		break;
	case QuitState:
		isQuit = true;
		break;
	default:
		break;
	}
}

bool StageManager::GetIsQuit()
{
	return isQuit;
}

void StageManager::HandleInput(sf::RenderWindow* aWindow)
{
	fStage->GetInput(aWindow);
}

void StageManager::HandleUpdate()
{
	fStage->Update();
}

void StageManager::HandleDraw(sf::RenderWindow* aWindow)
{
	fStage->Draw(aWindow);
}

StageManager::~StageManager()
{
}
