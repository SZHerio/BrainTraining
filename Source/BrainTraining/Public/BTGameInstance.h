// A BrainTraining Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BTGameInstance.generated.h"

class ABTAttemptLevelGameModeBase;

UCLASS()
class BRAINTRAINING_API UBTGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void InitDefaultSpawnClickableCirclesParameters();
	
	int32 GetClickableCirclesSpawnAmount() const { return ClickableCirclesSpawnAmount; }
	int32 GetMinClickableCirclesSpawnAmount() const { return MinClickableCirclesSpawnAmount; }
	int32 GetMaxClickableCirclesSpawnAmount() const { return MaxClickableCirclesSpawnAmount; }

	int32 GetMaxClickableCircleViewNumberHidingCountdown() const { return MaxClickableCircleViewNumberHidingCountdown; }
	int32 GetMinMaxClickableCircleViewNumberHidingCountdown() const { return MinMaxClickableCircleViewNumberHidingCountdown; }
	int32 GetMaxMaxClickableCircleViewNumberHidingCountdown() const { return MaxMaxClickableCircleViewNumberHidingCountdown; }

	int32 GetMaxClickableCircleNumber() const { return MaxClickableCircleNumber; }
	int32 GetMinMaxClickableCircleNumber() const { return MinMaxClickableCircleNumber; }
	int32 GetMaxMaxClickableCircleNumber() const { return MaxMaxClickableCircleNumber; }
	
	void SetClickableCirclesSpawnAmount(int32 Value) { ClickableCirclesSpawnAmount = Value; }
	void SetMaxClickableCircleViewNumberHidingCountdown(int32 Value) { MaxClickableCircleViewNumberHidingCountdown = Value; }
	void SetMaxClickableCircleNumber(int32 Value)  { MaxClickableCircleNumber = Value; }

	int32 GetSuccessfulAttemptsAmount() const {return SuccessfulAttemptAmount;}
	void IncreaseSuccessfulAttemptAmount();

	int32 GetFailedAttemptsAmount() const {return FailedAttemptAmount;}
	void IncreaseFailedAttemptAmount();

	int32 GetMostDifficultLevelNumber() const {return MostDifficultLevelNumber;}
	void UpdateMostDifficultLevelNumber();
	
	void PlayMainMusic();
	void StopMainMusic();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Main", meta=(ClampMin = 0))
	int32 ClickableCirclesSpawnAmount = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Main", meta=(ClampMin = 0))
	int32 MaxClickableCircleViewNumberHidingCountdown = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Main", meta=(ClampMin = 0))
	int32 MaxClickableCircleNumber = 25;

	UPROPERTY(EditDefaultsOnly, Category = "Main")
	TObjectPtr<USoundBase> MainBackgroundSoundBase;

	UPROPERTY()
	TObjectPtr<UAudioComponent> MainAudioComponent;
	
private:
	int32 MinClickableCirclesSpawnAmount = 5;
	int32 MaxClickableCirclesSpawnAmount = 25;

	int32 MinMaxClickableCircleViewNumberHidingCountdown = 1;
	int32 MaxMaxClickableCircleViewNumberHidingCountdown = 10;
	
	int32 MinMaxClickableCircleNumber = 0;
	int32 MaxMaxClickableCircleNumber = 40;

	int32 SuccessfulAttemptAmount = 0;
	int32 FailedAttemptAmount = 0;
	int32 MostDifficultLevelNumber = 0;
	
};
