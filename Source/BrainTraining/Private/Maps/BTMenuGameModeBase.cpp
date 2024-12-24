// A BrainTraining Game. All Right Reserved.

#include "BTMenuGameModeBase.h"

#include "BTGameInstance.h"
#include "BTMainMenuHUD.h"
#include "BTMainMenuPlayerController.h"

ABTMenuGameModeBase::ABTMenuGameModeBase()
{
	HUDClass = ABTMainMenuHUD::StaticClass();
	PlayerControllerClass = ABTMainMenuPlayerController::StaticClass();
}

void ABTMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	const auto BTGameInstance = CastChecked<UBTGameInstance>(GetGameInstance());
	BTGameInstance->PlayMainMusic();
}
