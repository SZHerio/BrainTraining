// A BrainTraining Game. All Right Reserved.

#pragma once
#include "CoreMinimal.h"
#include "BTBaseCircleWidget.h"
#include "BTClickableCircleWidget.generated.h"

class UImage;
class UTextBlock;
class UButton;

UCLASS()
class BRAINTRAINING_API UBTClickableCircleWidget : public UBTBaseCircleWidget
{
	GENERATED_BODY()
	
public:
	void SetColor(const FLinearColor& BodyImageColor, const FLinearColor& EdgingImageColor) const;
	void ShowBodyImage() const;
	void HideBodyImage() const;

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> EdgingImage;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> BodyImage;

protected:
	virtual void NativeOnInitialized() override;
};
