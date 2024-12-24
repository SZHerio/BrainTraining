// A BrainTraining Game. All Right Reserved.

#include "BTBaseCircleWidget.h"
#include "Components/TextBlock.h"

void UBTBaseCircleWidget::SetViewNumber(int32 Value) const
{
	ViewNumberTextBlock->SetText(FText::FromString(FString::FromInt(Value)));
}
