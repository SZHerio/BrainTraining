// A BrainTraining Game. All Right Reserved.

#include "BTAttemptLevelGameModeBase.h"
#include "BTAttemptLevelHUD.h"
#include "BTAttemptLevelManager.h"
#include "BTPlayerCamera.h"
#include "BTPlayerController.h"

ABTAttemptLevelGameModeBase::ABTAttemptLevelGameModeBase()
{
	PlayerControllerClass = ABTPlayerController::StaticClass();
	DefaultPawnClass = ABTPlayerCamera::StaticClass();
	HUDClass = ABTAttemptLevelHUD::StaticClass();
}

void ABTAttemptLevelGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	check(AttemptLevelManagerClass);
	InitAttemptLevelManager();
}

void ABTAttemptLevelGameModeBase::InitAttemptLevelManager()
{
	GetWorld()->SpawnActor(AttemptLevelManagerClass);
}

