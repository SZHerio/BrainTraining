// A BrainTraining Game. All Right Reserved.

#include "BTStatisticsMenuWidget.h"
#include "Components/TextBlock.h"
#include "BTGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UBTStatisticsMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitBTGameInstance();
	check(BTGameInstance);

	ProceedButton->OnReleased.AddDynamic(this, &UBTStatisticsMenuWidget::Func_OnProceedButtonReleased);
}

FText UBTStatisticsMenuWidget::GetSuccessfulAttemptsAmount() const
{
	int32 SuccessfulAttemptsAmount = BTGameInstance->GetSuccessfulAttemptsAmount();
	return FText::FromString(FString::FromInt(SuccessfulAttemptsAmount));
}

FText UBTStatisticsMenuWidget::GetFailedAttemptsAmount() const
{
	int32 FailedAttemptsAmount = BTGameInstance->GetFailedAttemptsAmount();
	return FText::FromString(FString::FromInt(FailedAttemptsAmount));
}

FText UBTStatisticsMenuWidget::GetMostDifficultLevelNumber() const
{
	int32 MostDifficultLevelNumber = BTGameInstance->GetMostDifficultLevelNumber();
	return FText::FromString(FString::FromInt(MostDifficultLevelNumber));
}

void UBTStatisticsMenuWidget::Func_OnProceedButtonReleased()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayDynamicForceFeedback(0.5f, 0.1f, true, true, true, true);
	OnProceedButtonReleased.Broadcast();
}

void UBTStatisticsMenuWidget::InitBTGameInstance()
{
	BTGameInstance = Cast<::UBTGameInstance>(GetGameInstance());
}
