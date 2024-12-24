// A BrainTraining Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BTAttemptLevelGameModeBase.generated.h"

class ABTAttemptLevelManager;
class UBTGameInstance;

UCLASS()
class BRAINTRAINING_API ABTAttemptLevelGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABTAttemptLevelGameModeBase();

	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Main")
	TSubclassOf<ABTAttemptLevelManager> AttemptLevelManagerClass;
	
	void InitAttemptLevelManager();
};
