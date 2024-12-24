// A BrainTraining Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTObjectsCoreTypes.h"
#include "GameFramework/Actor.h"
#include "BTClickableCircle.generated.h"

class UWidgetComponent;
class USphereComponent;
class UBTClickableCircleWidget;

UCLASS()
class BRAINTRAINING_API ABTClickableCircle : public AActor
{
	GENERATED_BODY()
	
public:	
	ABTClickableCircle();
	
	FOnClickableCircleSphereReleasedSignature  OnSphereReleased;

public:
	void SetWidgetColor(const FLinearColor& BodyImageColor, const FLinearColor& EdgingImageColor) const;
	void SetViewNumber(int32 Number) const;
	void ShowBodyImage() const;
	void HideBodyImage() const;
	void DisableCollision() const;
	void EnableCollision() const;
	bool IsOverlappingAnotherActor();
	bool IsCollisionEnabled() const;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UWidgetComponent> WidgetComponent;
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	TObjectPtr<UBTClickableCircleWidget> Widget = nullptr;
	
private:
	void InitWidget();
};
