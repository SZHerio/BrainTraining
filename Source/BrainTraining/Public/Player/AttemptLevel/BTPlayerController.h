// A BrainTraining Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BTPlayerController.generated.h"

UCLASS()
class BRAINTRAINING_API ABTPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	void SetAttemptLevelInputMode();
};
