// A BrainTraining Game. All Right Reserved.

#include "BTClickableCircleWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UBTClickableCircleWidget::SetColor(const FLinearColor& BodyImageColor, const FLinearColor& EdgingImageColor) const
{
	BodyImage->SetColorAndOpacity(BodyImageColor);
	EdgingImage->SetColorAndOpacity(EdgingImageColor);
	ViewNumberTextBlock->SetColorAndOpacity(EdgingImageColor);
}

void UBTClickableCircleWidget::ShowBodyImage() const
{
	BodyImage->SetVisibility(ESlateVisibility::Visible);
}

void UBTClickableCircleWidget::HideBodyImage() const
{
	BodyImage->SetVisibility(ESlateVisibility::Hidden);
}

void UBTClickableCircleWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	EdgingImage->SetVisibility(ESlateVisibility::Visible);
	BodyImage->SetVisibility(ESlateVisibility::Visible);
	ViewNumberTextBlock->SetVisibility(ESlateVisibility::Visible);
}
