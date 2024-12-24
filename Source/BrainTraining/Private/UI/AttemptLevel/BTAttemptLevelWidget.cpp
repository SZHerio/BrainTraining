// A BrainTraining Game. All Right Reserved.

#include "BTAttemptLevelWidget.h"
#include "BTBaseCircleWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UBTAttemptLevelWidget::StartAttempt()
{
	if(!GetWorld()) return;
	
	CountdownCircleWidget->SetVisibility(ESlateVisibility::Visible);
	
	check(CurrentSpawnClickableCirclesCountdown > 0);
	CountdownCircleWidget->SetViewNumber(CurrentSpawnClickableCirclesCountdown);

	if(GetWorld()->GetTimerManager().IsTimerActive(CountdownTimerHandle))
		GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
	
	GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this, &UBTAttemptLevelWidget::UpdateCountdownTimer, 1.0f, true, 1.0f);
}

void UBTAttemptLevelWidget::HideTryAnotherAttemptButton() const
{
	TryAnotherAttemptButton->SetVisibility(ESlateVisibility::Hidden);
}

void UBTAttemptLevelWidget::ShowTryAnotherAttemptButton() const
{
	TryAnotherAttemptButton->SetVisibility(ESlateVisibility::Visible);
}

void UBTAttemptLevelWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	InitPlayerController();
	check(PlayerController);
	
	TryAnotherAttemptButton->OnReleased.AddDynamic(this, &UBTAttemptLevelWidget::Func_OnTryAnotherAttemptButtonReleased);
	ExitToMainMenuButton->OnReleased.AddDynamic(this, &UBTAttemptLevelWidget::Func_OnExitToMainMenuButtonReleased);
	TryAnotherAttemptButton->SetVisibility(ESlateVisibility::Hidden);
	CountdownCircleWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UBTAttemptLevelWidget::Func_OnTryAnotherAttemptButtonReleased()
{
	OnTryAnotherAttemptButtonReleased.Broadcast();
	PlayerController->PlayDynamicForceFeedback(0.3f, 0.1f, true, true, true, true);
}

void UBTAttemptLevelWidget::Func_OnExitToMainMenuButtonReleased()
{
	if(!GetWorld()) return;

	PlayerController->PlayDynamicForceFeedback(0.3f, 0.1f, true, true, true, true);
	GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
	OnExitToMainMenuButtonReleased.Broadcast();
	OnBackgroundMusicShouldChange.Broadcast(EBackgroundMusicType::Main);

	FName MainLevelName = "MainMenuLevel";
	UGameplayStatics::OpenLevel(GetWorld(), MainLevelName);
}

void UBTAttemptLevelWidget::UpdateCountdownTimer()
{
	if(!GetWorld()) return;
	
	CountdownCircleWidget->SetViewNumber(--CurrentSpawnClickableCirclesCountdown);
	
	if(CurrentSpawnClickableCirclesCountdown > 0) return;

	GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
	CountdownCircleWidget->SetVisibility(ESlateVisibility::Collapsed);
	
	OnCountdownTimerIsUp.Broadcast();
}

void UBTAttemptLevelWidget::InitPlayerController()
{
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}
