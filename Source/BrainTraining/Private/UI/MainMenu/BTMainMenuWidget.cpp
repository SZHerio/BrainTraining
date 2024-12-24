// A BrainTraining Game. All Right Reserved.

#include "BTMainMenuWidget.h"
#include "Components/Button.h"
#include "BTOptionsMenuWidget.h"
#include "MediaPlayer.h"
#include "Kismet/GameplayStatics.h"

void UBTMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	InitPlayerController();
	check(PlayerController);
	
	StartAttemptButton->OnReleased.AddDynamic(this, &UBTMainMenuWidget::OnStartAttemptButtonReleased);
	OptionsButton->OnReleased.AddDynamic(this, &UBTMainMenuWidget::OnOptionsButtonReleased);
	OptionsMenuWidget->OnApplyChangesButtonReleased.AddUObject(this, &UBTMainMenuWidget::OnApplyChangesButtonReleased);
	OptionsMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	
	TitleMediaPlayer->OpenSource(TitleSource);
	TitleMediaPlayer->Rewind();
	TitleMediaPlayer->SetRate(1.0f);
	TitleMediaPlayer->Play();
}

void UBTMainMenuWidget::OnStartAttemptButtonReleased()
{
	PlayerController->PlayDynamicForceFeedback(0.3f, 0.1f, true, true, true, true);

	FName AttemptLevelName = "AttemptLevel";
	UGameplayStatics::OpenLevel(this, AttemptLevelName);
}

void UBTMainMenuWidget::OnApplyChangesButtonReleased()
{
	PlayerController->PlayDynamicForceFeedback(0.3f, 0.1f, true, true, true, true);
	OptionsMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UBTMainMenuWidget::InitPlayerController()
{
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

void UBTMainMenuWidget::OnOptionsButtonReleased()
{
	PlayerController->PlayDynamicForceFeedback(0.3f, 0.1f, true, true, true, true);
	OptionsMenuWidget->SetVisibility(ESlateVisibility::Visible);
}

