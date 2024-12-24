// A BrainTraining Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BTBaseHUD.generated.h"

class UBTOptionsMenuWidget;
class UBTStatisticsMenuWidget;

UCLASS()
class BRAINTRAINING_API ABTBaseHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Main")
	TSubclassOf<UUserWidget> OptionsMenuWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Main")
	TSubclassOf<UUserWidget> StatisticsMenuWidgetClass = nullptr;
	
	UPROPERTY()
	TObjectPtr<UBTOptionsMenuWidget> OptionsMenuWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UBTStatisticsMenuWidget> StatisticsMenuWidget = nullptr;

	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController = nullptr;
	
protected:
	virtual void BeginPlay() override;
	
	void ChangeVisibilitiesOfTwoWidgets(UUserWidget* OneWidget, ESlateVisibility NewOneWidgetVisibility, UUserWidget* OtherWidget, ESlateVisibility NewOtherWidgetVisibility);

private:
	UFUNCTION()
	void OnApplyChangesButtonReleased();

	UFUNCTION()
	void BaseHUD_OnProceedButtonReleased();

	void InitPlayerController();
};
