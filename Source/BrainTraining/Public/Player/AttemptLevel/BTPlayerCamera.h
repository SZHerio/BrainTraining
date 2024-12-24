// A BrainTraining Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BTPlayerCamera.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class ABTPlayerController;

UCLASS()
class BRAINTRAINING_API ABTPlayerCamera : public APawn
{
	GENERATED_BODY()

public:
	ABTPlayerCamera();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Main")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Main")
	TObjectPtr<UInputAction> ClickInputAction;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY()
	ABTPlayerController* BTController = nullptr;
	
private:
	void InitPlayerController();
	void AddMappingContext();
	void Click();
};
