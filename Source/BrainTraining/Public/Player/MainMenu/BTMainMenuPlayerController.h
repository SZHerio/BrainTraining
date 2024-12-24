// A BrainTraining Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BTMainMenuPlayerController.generated.h"

UCLASS()
class BRAINTRAINING_API ABTMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	void SetMainMenuInputMode();
};
