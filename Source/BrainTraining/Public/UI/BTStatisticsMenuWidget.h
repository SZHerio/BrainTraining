// A BrainTraining Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTUICoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "BTStatisticsMenuWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class BRAINTRAINING_API UBTStatisticsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnProceedButtonReleasedSignature OnProceedButtonReleased;

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ProceedButton;
	
private:
	TObjectPtr<UBTGameInstance> BTGameInstance = nullptr;
	
protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable, Category = "UI")
	FText GetSuccessfulAttemptsAmount() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	FText GetFailedAttemptsAmount() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	FText GetMostDifficultLevelNumber() const;

private:
	UFUNCTION()
	void Func_OnProceedButtonReleased();
	
	void InitBTGameInstance();
	
};
