// A BrainTraining Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTObjectsCoreTypes.h"
#include "GameFramework/Actor.h"
#include "BTAttemptLevelManager.generated.h"

class ABTAttemptLevelHUD;
class ABTClickableCircle;
class UBTAttemptLevelWidget;
class ABTClickableCirclesSpawnManager;

UCLASS()
class BRAINTRAINING_API ABTAttemptLevelManager : public AActor
{
	GENERATED_BODY()
	
public:
	ABTAttemptLevelManager();
	
	UBTAttemptLevelWidget* GetAttemptLevelWidget() const { return AttemptLevelWidget; }
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Main", meta=(ClampMin = 1, ClampMax = 10))
	int32 MaxSpawnClickableCirclesCountdown = 3;
	
	UPROPERTY(EditDefaultsOnly, Category = "Main")
	TSubclassOf<ABTClickableCirclesSpawnManager> ClickableCirclesSpawnManagerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Main")
	TObjectPtr<USoundBase> ClickSoundBase;

	UPROPERTY(EditDefaultsOnly, Category = "Main")
	TObjectPtr<USoundBase> SucceedPlayerAttemptSound;

	UPROPERTY(EditDefaultsOnly, Category = "Main")
	TObjectPtr<USoundBase> DifficultBackgroundSoundBase;
	
	UPROPERTY(EditDefaultsOnly, Category = "Main")
	TObjectPtr<USoundBase> FailPlayerAttemptSound;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<ABTClickableCirclesSpawnManager> ClickableCirclesSpawnManager = nullptr;

	UPROPERTY()
	TObjectPtr<ABTAttemptLevelHUD> AttemptLevelHUD = nullptr;
	
	UPROPERTY()
	TObjectPtr<UBTAttemptLevelWidget> AttemptLevelWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UBTGameInstance> BTGameInstance = nullptr;

	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY()
	TObjectPtr<UAudioComponent> DifficultAudioComponent;
	
	bool ShouldSpawnManagerParametersBeUpdated = false;
	bool HasPlayerFailed = false;
	
private:
	UFUNCTION()
	void OnClickableCircleSelected(const ABTClickableCircle* ClickableCircle);

	UFUNCTION()
	void OnCountdownTimerIsUp();

	UFUNCTION()
	void OnTryAnotherAttemptButtonReleased();

	UFUNCTION()
	void OnExitToMainMenuButtonReleased();

	UFUNCTION()
	void OnBackgroundMusicShouldChange(EBackgroundMusicType Type);

	UFUNCTION()
	void OnClickableCirclesCollisionsChanged(bool ShouldCollisionsBeEnabled);
	
	void InitBTGameInstance();
	void InitClickableCirclesSpawnManager();
	void InitBTHUD();
	void InitAttemptLevelWidget();
	void StartAttempt();
	void SucceedPlayerAttempt() const;
	void FailPlayerAttempt();
	void UpdateSpawnManagerParameters();
	void InitPlayerController();
	void InitDifficultAudioComponent();
};
