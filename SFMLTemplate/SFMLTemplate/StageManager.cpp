#include "StageManager.h"
#include "PlanningStage.h"
#include "GameplayStage.h"

StageManager* StageManager::fInstance = 0;
Stage* StageManager::fStage = 0;

StageManager* StageManager::Instance(sf::RenderWindow* aWindow)
{
	if (!fInstance)
	{
		fInstance = new StageManager(StageEnum::Planning, aWindow);
	}
	return fInstance;
}

StageManager::StageManager(StageEnum lState, sf::RenderWindow* aWindow)
{
	fWindow = aWindow;
	isQuit = false;
	SetState(lState);
}

void StageManager::SetState(StageEnum lState)
{
	switch (lState)
	{
	case Planning:
		fStage = PlanningStage::Instance(fWindow);
		break;
	case Gameplay:
		fStage = GameplayStage::Instance(fWindow);
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

void StageManager::HandleInput()
{
	fStage->GetInput();
}

void StageManager::HandleUpdate()
{
	fStage->Update();
}

void StageManager::HandleDraw()
{
	fStage->Draw();
}

StageManager::~StageManager()
{
}
