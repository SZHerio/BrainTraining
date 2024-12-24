// A BrainTraining Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BTMenuGameModeBase.generated.h"

UCLASS()
class BRAINTRAINING_API ABTMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABTMenuGameModeBase();
	
protected:
	virtual void BeginPlay() override;
};
