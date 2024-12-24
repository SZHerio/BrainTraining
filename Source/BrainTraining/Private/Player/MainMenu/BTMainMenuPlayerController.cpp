// A BrainTraining Game. All Right Reserved.


#include "BTMainMenuPlayerController.h"

void ABTMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetMainMenuInputMode();
}

void ABTMainMenuPlayerController::SetMainMenuInputMode()
{
	bShowMouseCursor = true;
	
	FInputModeUIOnly InputModeUIOnly;
	InputModeUIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputModeUIOnly);
}
