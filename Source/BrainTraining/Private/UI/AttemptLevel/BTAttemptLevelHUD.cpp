// A BrainTraining Game. All Right Reserved.

#include "BTAttemptLevelHUD.h"
#include "BTAttemptLevelWidget.h"
#include "BTUIUtils.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "BTOptionsMenuWidget.h"
#include "BTStatisticsMenuWidget.h"

UBTAttemptLevelWidget* ABTAttemptLevelHUD::GetAttemptLevelWidget()
{
	if(!AttemptLevelWidget)
	{
		InitAttemptLevelWidgets();
	}

	return AttemptLevelWidget;
}

bool ABTAttemptLevelHUD::ShouldSpawnManagerParametersBeUpdated() const
{
	return OptionsMenuWidget->ShouldSpawnManagerParametersBeUpdated();
}

void ABTAttemptLevelHUD::SetShouldSpawnManagerParametersBeUpdated(bool Value)
{
	OptionsMenuWidget->SetShouldSpawnManagerParametersBeUpdated(Value);
}

void ABTAttemptLevelHUD::BeginPlay()
{
	Super::BeginPlay();
	
	check(AttemptLevelWidgetClass);
	
	AttemptLevelWidget->GetOptionsMenuButton()->OnReleased.AddDynamic(this, &ABTAttemptLevelHUD::OnOptionsMenuButtonReleased);
	AttemptLevelWidget->GetStatisticsMenuButton()->OnReleased.AddDynamic(this, &ABTAttemptLevelHUD::OnStatisticsButtonReleased);

	StatisticsMenuWidget->OnProceedButtonReleased.AddUObject(this, &ABTAttemptLevelHUD::OnStatisticsProceedButtonReleased);
	OptionsMenuWidget->OnApplyChangesButtonReleased.AddUObject(this, &ABTAttemptLevelHUD::OnOptionsApplyChangesButtonReleased);
}

void ABTAttemptLevelHUD::OnOptionsMenuButtonReleased()
{
	OnClickableCirclesCollisionsChanged.Broadcast(false);
	ChangeVisibilitiesOfTwoWidgets(AttemptLevelWidget, ESlateVisibility::HitTestInvisible, OptionsMenuWidget, ESlateVisibility::Visible);
	PlayerController->PlayDynamicForceFeedback(0.3f, 0.1f, true, true, true, true);
}

void ABTAttemptLevelHUD::OnStatisticsButtonReleased()
{
	OnClickableCirclesCollisionsChanged.Broadcast(false);
	ChangeVisibilitiesOfTwoWidgets(AttemptLevelWidget, ESlateVisibility::HitTestInvisible, StatisticsMenuWidget, ESlateVisibility::Visible);
	PlayerController->PlayDynamicForceFeedback(0.3f, 0.1f, true, true, true, true);
}

void ABTAttemptLevelHUD::OnStatisticsProceedButtonReleased()
{
	OnClickableCirclesCollisionsChanged.Broadcast(true);
	ChangeVisibilitiesOfTwoWidgets(AttemptLevelWidget, ESlateVisibility::Visible, StatisticsMenuWidget, ESlateVisibility::Collapsed);
}

void ABTAttemptLevelHUD::OnOptionsApplyChangesButtonReleased()
{
	OnClickableCirclesCollisionsChanged.Broadcast(true);
	ChangeVisibilitiesOfTwoWidgets(AttemptLevelWidget, ESlateVisibility::Visible, OptionsMenuWidget, ESlateVisibility::Collapsed);
}

void ABTAttemptLevelHUD::InitAttemptLevelWidgets()
{
	AttemptLevelWidget = BTUIUtils::GetInitializedWidget<UBTAttemptLevelWidget>(GetWorld(), AttemptLevelWidgetClass);
	AttemptLevelWidget->SetVisibility(ESlateVisibility::Visible);
}


