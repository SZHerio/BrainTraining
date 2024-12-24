// A BrainTraining Game. All Right Reserved.

#include "BTBaseHUD.h"
#include "Blueprint/UserWidget.h"
#include "BTOptionsMenuWidget.h"
#include "BTStatisticsMenuWidget.h"
#include "BTUIUtils.h"
#include "Kismet/GameplayStatics.h"

void ABTBaseHUD::BeginPlay()
{
	Super::BeginPlay();
	
	check(OptionsMenuWidgetClass);
	check(StatisticsMenuWidgetClass);
	
	OptionsMenuWidget = BTUIUtils::GetInitializedWidget<UBTOptionsMenuWidget>(GetWorld(), OptionsMenuWidgetClass);
	StatisticsMenuWidget = BTUIUtils::GetInitializedWidget<UBTStatisticsMenuWidget>(GetWorld(), StatisticsMenuWidgetClass);
	
	OptionsMenuWidget->OnApplyChangesButtonReleased.AddUObject(this, &ABTBaseHUD::OnApplyChangesButtonReleased);
	StatisticsMenuWidget->OnProceedButtonReleased.AddUObject(this, &ABTBaseHUD::BaseHUD_OnProceedButtonReleased);

	InitPlayerController();
	check(PlayerController);
}

void ABTBaseHUD::ChangeVisibilitiesOfTwoWidgets(UUserWidget* OneWidget, ESlateVisibility NewOneWidgetVisibility, UUserWidget* OtherWidget,
                                                ESlateVisibility NewOtherWidgetVisibility)
{
	OneWidget->SetVisibility(NewOneWidgetVisibility);
	OtherWidget->SetVisibility(NewOtherWidgetVisibility);
}

void ABTBaseHUD::OnApplyChangesButtonReleased()
{
	PlayerController->PlayDynamicForceFeedback(0.3f, 0.1f, true, true, true, true);
}

void ABTBaseHUD::BaseHUD_OnProceedButtonReleased()
{
	PlayerController->PlayDynamicForceFeedback(0.3f, 0.1f, true, true, true, true);
}

void ABTBaseHUD::InitPlayerController()
{
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}
