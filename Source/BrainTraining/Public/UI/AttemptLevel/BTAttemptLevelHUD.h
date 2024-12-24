// A BrainTraining Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBaseHUD.h"
#include "BTUICoreTypes.h"
#include "BTAttemptLevelHUD.generated.h"

class UBTAttemptLevelWidget;
class UBTOptionsMenuWidget;
class ABTPlayerController;

UCLASS()
class BRAINTRAINING_API ABTAttemptLevelHUD : public ABTBaseHUD
{
	GENERATED_BODY()

public:
	FOnClickableCirclesCollisionsChangedSignature OnClickableCirclesCollisionsChanged;
	UBTAttemptLevelWidget* GetAttemptLevelWidget();

public:
	bool ShouldSpawnManagerParametersBeUpdated() const;
	void SetShouldSpawnManagerParametersBeUpdated(bool Value);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Main")
	TSubclassOf<UUserWidget> AttemptLevelWidgetClass = nullptr;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UBTAttemptLevelWidget> AttemptLevelWidget = nullptr;
	
private:
	UFUNCTION()
	void OnOptionsMenuButtonReleased();

	UFUNCTION()
	void OnStatisticsButtonReleased();

	UFUNCTION()
	void OnStatisticsProceedButtonReleased();

	UFUNCTION()
	void OnOptionsApplyChangesButtonReleased();
	
	void InitAttemptLevelWidgets();
};
