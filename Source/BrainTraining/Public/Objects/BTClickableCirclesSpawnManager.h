// A BrainTraining Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTObjectsCoreTypes.h"
#include "GameFramework/Actor.h"
#include "BTClickableCirclesSpawnManager.generated.h"

class ABTClickableCircle;

UCLASS()
class BRAINTRAINING_API ABTClickableCirclesSpawnManager : public AActor
{
	GENERATED_BODY()
	
public:
	ABTClickableCirclesSpawnManager();
	
	FOnClickableCircleSelectedSignature OnClickableCircleSelected;

public:
	void InitClickableCircles();
	void StartClickableCirclesViewNumberHidingTimer();
	void DeleteFirstClickableCirclesArrayElement();
	bool IsClickableCirclesArrayEmpty() const;
	void HideAllClickableCirclesBodies();
	void DisableAllClickableCirclesCollisions();
	void EnableAllClickableCirclesCollisions();
	ABTClickableCircle* GetFirstClickableCircleArrayElement();
	void DestroyAllClickableCirclesFromScene();
	void EmptyClickableCirclesArray();
	void SetSpawnClickableCirclesParameters(int32 SpawnAmount, int32 ViewNumberHidingCountdown, int32 MaxNumber);
	void ClearViewNumberHidingClickableCirclesTimer();
	bool AreClickableCirclesCollisionsEnabled();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Main")
	TSubclassOf<ABTClickableCircle> ClickableCircleClass;

private:
	UPROPERTY()
	TArray<ABTClickableCircle*> ClickableCircles;

	int32 ClickableCirclesSpawnAmount = 0;
	int32 MaxClickableCircleViewNumberHidingCountdown = 0;
	int32 MaxClickableCircleNumber = 0;
	
	int32 LastClickedCircleIndex = 0;
	FTimerHandle ViewNumberHidingClickableCirclesTimerHandle{};
	int32 CurrentClickableCircleViewNumberHidingCountdown = 0;
	
private:
	UFUNCTION()
	void OnClickableCircleSphereReleased(const ABTClickableCircle* ClickableCircle);
	
	int32 GetGeneratedClickableCircleNumber(size_t Index);
	FLinearColor GetRandomClickedCirclesBodyColor() const;
	void UpdateClickableCircleViewNumberHidingCountdown();
	FVector GetClickableCircleRandomLocation();
	void ResetCurrentClickableCircleViewNumberHidingCountdown();
	
};
