// A BrainTraining Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BTBaseCircleWidget.generated.h"

class UTextBlock;

UCLASS()
class BRAINTRAINING_API UBTBaseCircleWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetViewNumber(int32 Value) const;

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ViewNumberTextBlock;
};
