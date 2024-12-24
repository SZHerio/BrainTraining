// A BrainTraining Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTUICoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "BTOptionsMenuWidget.generated.h"

class UTextBlock;
class UButton;
class USlider;
class UBTGameInstance;

UCLASS()
class BRAINTRAINING_API UBTOptionsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnApplyChangesButtonReleasedSignature OnApplyChangesButtonReleased;
	
public:
	int32 GetClickableCirclesSpawnAmount() const;
	int32 GetMaxClickableCircleNumber() const;
	int32 GetMaxClickableCircleViewNumberHidingCountdown() const;

	void SetClickableCirclesSpawnAmount(int32 Value);
	void SetMaxClickableCircleViewNumberHidingCountdown(int32 Value);
	void SetMaxClickableCircleNumber(int32 Value);

	void SetMinClickableCirclesSpawnAmount(int32 Value);
	void SetMinMaxClickableCircleViewNumberHidingCountdown(int32 Value);
	void SetMinMaxClickableCircleNumber(int32 Value);

	void SetMaxClickableCirclesSpawnAmount(int32 Value);
	void SetMaxMaxClickableCircleViewNumberHidingCountdown(int32 Value);
	void SetMaxMaxClickableCircleNumber(int32 Value);

	bool ShouldSpawnManagerParametersBeUpdated() const { return bShouldSpawnManagerParametersBeUpdated; }
	void SetShouldSpawnManagerParametersBeUpdated(bool Value) { bShouldSpawnManagerParametersBeUpdated = Value; }

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USlider> ClickableCirclesSpawnAmountSlider;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ClickableCirclesSpawnAmountTextBlock;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USlider> MaxClickableCircleViewNumberHidingCountdownSlider;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> MaxClickableCircleViewNumberHidingCountdownTextBlock;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USlider> MaxClickableCircleNumberSlider;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> MaxClickableCircleNumberTextBlock;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ApplyChangesButton;

protected:
	virtual void NativeOnInitialized() override;
	
private:
	UPROPERTY()
	TObjectPtr<UBTGameInstance> BTGameInstance = nullptr;
	
	int32 ClickableCirclesSpawnAmount = 0;
	int32 MaxClickableCircleViewNumberHidingCountdown = 0;
	int32 MaxClickableCircleNumber = 0;

	int32 MinClickableCirclesSpawnAmount = 0;
	int32 MinMaxClickableCircleViewNumberHidingCountdown = 0;
	int32 MinMaxClickableCircleNumber = 0;

	int32 MaxClickableCirclesSpawnAmount = 0;
	int32 MaxMaxClickableCircleViewNumberHidingCountdown = 0;
	int32 MaxMaxClickableCircleNumber = 0;

	bool bShouldSpawnManagerParametersBeUpdated = false;

private:
	UFUNCTION()
	void OnClickableCirclesSpawnAmountSliderValueChanged(float Value);

	UFUNCTION()
	void OnMaxClickableCircleNumberSliderValueChanged(float Value);

	UFUNCTION()
	void OnMaxClickableCircleViewNumberHidingCountdownSliderValueChanged(float Value);

	UFUNCTION()
	void Func_OnApplyChangesButtonReleased();

	void InitBTGameInstance();
	void InitParameters();
	FText GetTextFromInt(int32 Value) const;
	void SetValueAfterSliderTriggering(float Value, UTextBlock* TextBlock, void(UBTOptionsMenuWidget::*SetFuncPtr)(int32));
};
