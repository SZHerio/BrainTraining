// A BrainTraining Game. All Right Reserved.

#include "BTMainMenuHUD.h"
#include "BTUIUtils.h"
#include "BTMainMenuWidget.h"
#include "BTOptionsMenuWidget.h"
#include "BTStatisticsMenuWidget.h"
#include "Components/Button.h"

void ABTMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	check(MainMenuWidgetClass);

	InitMainMenuWidget();
	
	MainMenuWidget->GetOptionsMenuButton()->OnReleased.AddDynamic(this, &ABTMainMenuHUD::OnOptionsMenuButtonReleased);
	OptionsMenuWidget->OnApplyChangesButtonReleased.AddUObject(this, &ABTMainMenuHUD::OnOptionApplyChangesButtonReleased);
	StatisticsMenuWidget->OnProceedButtonReleased.AddUObject(this, &ABTMainMenuHUD::OnStatisticsMenuProceedButtonReleased);
}

void ABTMainMenuHUD::OnOptionsMenuButtonReleased()
{
	ChangeVisibilitiesOfTwoWidgets(MainMenuWidget, ESlateVisibility::HitTestInvisible, OptionsMenuWidget, ESlateVisibility::Visible);
	PlayerController->PlayDynamicForceFeedback(0.5f, 0.1f, true, true, true, true);
}

void ABTMainMenuHUD::OnOptionApplyChangesButtonReleased()
{
	ChangeVisibilitiesOfTwoWidgets(MainMenuWidget, ESlateVisibility::Visible, OptionsMenuWidget, ESlateVisibility::Collapsed);
}

void ABTMainMenuHUD::OnStatisticsMenuProceedButtonReleased()
{
	ChangeVisibilitiesOfTwoWidgets(MainMenuWidget, ESlateVisibility::HitTestInvisible, OptionsMenuWidget, ESlateVisibility::Visible);
}

void ABTMainMenuHUD::InitMainMenuWidget()
{
	MainMenuWidget = BTUIUtils::GetInitializedWidget<UBTMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
	MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
}
