// A BrainTraining Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BTUICoreTypes.h"
#include "BTAttemptLevelWidget.generated.h"

class UBTOptionsMenuWidget;
class UBTBaseCircleWidget;
class UBTClickableCircleWidget;
class UBTCountdownCircleWidget;
class UBTClickableCirclesManagerWidget;
class UButton;

UCLASS()
class BRAINTRAINING_API UBTAttemptLevelWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnBackgroundMusicShouldChangeSignature  OnBackgroundMusicShouldChange;
	FOnCountdownTimerIsUpSignature OnCountdownTimerIsUp;
	FOnTryAnotherAttemptButtonReleasedSignature OnTryAnotherAttemptButtonReleased;
	FOnExitToMainMenuButtonReleasedSignature OnExitToMainMenuButtonReleased;
	
	UButton* GetOptionsMenuButton() const { return OptionsMenuButton; }
	UButton* GetStatisticsMenuButton() const { return StatisticsMenuButton; }
	
public:
	void StartAttempt();
	void SetCurrentSpawnClickedCirclesCountdown(int32 Value) { CurrentSpawnClickableCirclesCountdown = Value; }
	void HideTryAnotherAttemptButton() const; 
	void ShowTryAnotherAttemptButton() const;
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> TryAnotherAttemptButton = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ExitToMainMenuButton = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> OptionsMenuButton = nullptr;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UBTBaseCircleWidget> CountdownCircleWidget = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> StatisticsMenuButton = nullptr;
	
	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;

protected:
	virtual void NativeOnInitialized() override;
	
private:
	FTimerHandle CountdownTimerHandle{};
	int32 CurrentSpawnClickableCirclesCountdown = 3;

private:
	UFUNCTION()
	void Func_OnTryAnotherAttemptButtonReleased();

	UFUNCTION()
	void Func_OnExitToMainMenuButtonReleased();
	
	void UpdateCountdownTimer();
	void InitPlayerController();
};
