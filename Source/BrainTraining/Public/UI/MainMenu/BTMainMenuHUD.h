// A BrainTraining Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBaseHUD.h"
#include "BTMainMenuHUD.generated.h"

class UBTMainMenuWidget;
class UBTOptionsMenuWidget;
class UBTGameInstance;

UCLASS()
class BRAINTRAINING_API ABTMainMenuHUD : public ABTBaseHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Main")
	TSubclassOf<UUserWidget> MainMenuWidgetClass = nullptr;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UBTGameInstance> BTGameInstance = nullptr;
	
	UPROPERTY()
	TObjectPtr<UBTMainMenuWidget> MainMenuWidget = nullptr;
	
private:
	UFUNCTION()
	void OnOptionsMenuButtonReleased();

	UFUNCTION()
	void OnOptionApplyChangesButtonReleased();

	UFUNCTION()
	void OnStatisticsMenuProceedButtonReleased();
	
	void InitMainMenuWidget();
};
