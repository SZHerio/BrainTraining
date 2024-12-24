// A BrainTraining Game. All Right Reserved.

#include "AttemptLevel/BTPlayerController.h"

void ABTPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	SetAttemptLevelInputMode();
}

void ABTPlayerController::SetAttemptLevelInputMode()
{
	bShowMouseCursor = true;
	
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
}
