// A BrainTraining Game. All Right Reserved.

#include "BTOptionsMenuWidget.h"
#include "BTGameInstance.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

int32 UBTOptionsMenuWidget::GetClickableCirclesSpawnAmount() const
{
	return ClickableCirclesSpawnAmount;
}

int32 UBTOptionsMenuWidget::GetMaxClickableCircleNumber() const
{
	return MaxClickableCircleNumber;
}

int32 UBTOptionsMenuWidget::GetMaxClickableCircleViewNumberHidingCountdown() const
{
	return MaxClickableCircleViewNumberHidingCountdown;
}

void UBTOptionsMenuWidget::SetClickableCirclesSpawnAmount(int32 Value) 
{
	ClickableCirclesSpawnAmount = Value;
	ClickableCirclesSpawnAmountTextBlock->SetText(GetTextFromInt(Value));
	ClickableCirclesSpawnAmountSlider->SetValue(Value);
}

void UBTOptionsMenuWidget::SetMaxClickableCircleNumber(int32 Value) 
{
	MaxClickableCircleNumber = Value;
	MaxClickableCircleNumberTextBlock->SetText(GetTextFromInt(Value));
	MaxClickableCircleNumberSlider->SetValue(Value);
}

void UBTOptionsMenuWidget::SetMaxClickableCircleViewNumberHidingCountdown(int32 Value) 
{
	MaxClickableCircleViewNumberHidingCountdown = Value;
	MaxClickableCircleViewNumberHidingCountdownTextBlock->SetText(GetTextFromInt(Value));
	MaxClickableCircleViewNumberHidingCountdownSlider->SetValue(Value);
}

void UBTOptionsMenuWidget::SetMinClickableCirclesSpawnAmount(int32 Value)
{
	MinClickableCirclesSpawnAmount = Value;
	ClickableCirclesSpawnAmountSlider->SetMinValue(Value);
}

void UBTOptionsMenuWidget::SetMinMaxClickableCircleNumber(int32 Value)
{
	MinMaxClickableCircleNumber = Value;
	MaxClickableCircleNumberSlider->SetMinValue(Value);
}

void UBTOptionsMenuWidget::SetMinMaxClickableCircleViewNumberHidingCountdown(int32 Value)
{
	MinMaxClickableCircleViewNumberHidingCountdown = Value;
	MaxClickableCircleViewNumberHidingCountdownSlider->SetMinValue(Value);
}

void UBTOptionsMenuWidget::SetMaxClickableCirclesSpawnAmount(int32 Value)
{
	MaxClickableCirclesSpawnAmount = Value;
	ClickableCirclesSpawnAmountSlider->SetMaxValue(Value);
}

void UBTOptionsMenuWidget::SetMaxMaxClickableCircleNumber(int32 Value)
{
	MaxMaxClickableCircleNumber = Value;
	MaxClickableCircleNumberSlider->SetMaxValue(Value);
}

void UBTOptionsMenuWidget::SetMaxMaxClickableCircleViewNumberHidingCountdown(int32 Value)
{
	MaxMaxClickableCircleViewNumberHidingCountdown = Value;
	MaxClickableCircleViewNumberHidingCountdownSlider->SetMaxValue(Value);
}

void UBTOptionsMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ClickableCirclesSpawnAmountSlider->OnValueChanged.AddDynamic(this, &UBTOptionsMenuWidget::OnClickableCirclesSpawnAmountSliderValueChanged);
	MaxClickableCircleNumberSlider->OnValueChanged.AddDynamic(this, &UBTOptionsMenuWidget::OnMaxClickableCircleNumberSliderValueChanged);
	MaxClickableCircleViewNumberHidingCountdownSlider->OnValueChanged.AddDynamic(this, &UBTOptionsMenuWidget::OnMaxClickableCircleViewNumberHidingCountdownSliderValueChanged);

	ApplyChangesButton->OnReleased.AddDynamic(this, &UBTOptionsMenuWidget::Func_OnApplyChangesButtonReleased);

	InitBTGameInstance();
	InitParameters();
}

void UBTOptionsMenuWidget::OnClickableCirclesSpawnAmountSliderValueChanged(float Value) 
{
	if(Value > MaxClickableCircleNumber) return;
	
	SetValueAfterSliderTriggering(Value, ClickableCirclesSpawnAmountTextBlock, &UBTOptionsMenuWidget::SetClickableCirclesSpawnAmount);
}

void UBTOptionsMenuWidget::OnMaxClickableCircleNumberSliderValueChanged(float Value)  
{
	if(Value < ClickableCirclesSpawnAmount) return;
	
	SetValueAfterSliderTriggering(Value, MaxClickableCircleNumberTextBlock, &UBTOptionsMenuWidget::SetMaxClickableCircleNumber);
}

void UBTOptionsMenuWidget::OnMaxClickableCircleViewNumberHidingCountdownSliderValueChanged(float Value) 
{
	SetValueAfterSliderTriggering(Value, MaxClickableCircleViewNumberHidingCountdownTextBlock, &UBTOptionsMenuWidget::SetMaxClickableCircleViewNumberHidingCountdown);
}

void UBTOptionsMenuWidget::Func_OnApplyChangesButtonReleased()
{
	if(!BTGameInstance || !GetWorld()) return;
	
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayDynamicForceFeedback(0.5f, 0.1f, true, true, true, true);

	BTGameInstance->SetClickableCirclesSpawnAmount(ClickableCirclesSpawnAmount);
	BTGameInstance->SetMaxClickableCircleViewNumberHidingCountdown(MaxClickableCircleViewNumberHidingCountdown);
	BTGameInstance->SetMaxClickableCircleNumber(MaxClickableCircleNumber);

	bShouldSpawnManagerParametersBeUpdated = true;
	OnApplyChangesButtonReleased.Broadcast();
}

void UBTOptionsMenuWidget::InitBTGameInstance()
{
	BTGameInstance = CastChecked<UBTGameInstance>(GetGameInstance());
}

void UBTOptionsMenuWidget::InitParameters()
{
	const auto SpawnAmount = BTGameInstance->GetClickableCirclesSpawnAmount();
	const auto MinSpawnAmount = BTGameInstance->GetMinClickableCirclesSpawnAmount();
	const auto MaxSpawnAmount = BTGameInstance->GetMaxClickableCirclesSpawnAmount();
	
	const auto MaxViewNumberHidingCountdown = BTGameInstance->GetMaxClickableCircleViewNumberHidingCountdown();
	const auto MinMaxViewNumberHidingCountdown = BTGameInstance->GetMinMaxClickableCircleViewNumberHidingCountdown();
	const auto MaxMaxViewNumberHidingCountdown = BTGameInstance->GetMaxMaxClickableCircleViewNumberHidingCountdown();
	
	const auto MaxNumber = BTGameInstance->GetMaxClickableCircleNumber();
	const auto MinMaxNumber = BTGameInstance->GetMinMaxClickableCircleNumber();
	const auto MaxMaxNumber = BTGameInstance->GetMaxMaxClickableCircleNumber();

	SetMinClickableCirclesSpawnAmount(MinSpawnAmount);
	SetMaxClickableCirclesSpawnAmount(MaxSpawnAmount);
	SetClickableCirclesSpawnAmount(SpawnAmount);

	SetMinMaxClickableCircleViewNumberHidingCountdown(MinMaxViewNumberHidingCountdown);
	SetMaxMaxClickableCircleViewNumberHidingCountdown(MaxMaxViewNumberHidingCountdown);
	SetMaxClickableCircleViewNumberHidingCountdown(MaxViewNumberHidingCountdown);

	SetMinMaxClickableCircleNumber(MinMaxNumber);
	SetMaxMaxClickableCircleNumber(MaxMaxNumber);
	SetMaxClickableCircleNumber(MaxNumber);
}

FText UBTOptionsMenuWidget::GetTextFromInt(int32 Value) const 
{
	return FText::FromString(FString::FromInt(Value));
}

void UBTOptionsMenuWidget::SetValueAfterSliderTriggering(float Value, UTextBlock* TextBlock, void(UBTOptionsMenuWidget::*SetFuncPtr)(int32))
{
	const auto ResultValue = FMath::RoundToInt32(Value);
	if(ResultValue == Value) return;
	
	(this->*SetFuncPtr)(ResultValue);
	TextBlock->SetText(GetTextFromInt(ResultValue));
}
