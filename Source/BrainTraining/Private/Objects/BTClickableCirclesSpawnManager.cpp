// A BrainTraining Game. All Right Reserved.

#include "BTClickableCirclesSpawnManager.h"
#include "BTClickableCircle.h"
#include "Kismet/GameplayStatics.h"

ABTClickableCirclesSpawnManager::ABTClickableCirclesSpawnManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABTClickableCirclesSpawnManager::InitClickableCircles()
{
	const auto ClickableCircleBodyButtonColor = GetRandomClickedCirclesBodyColor();
	const auto ClickableCircleEdgingImageColor = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);

	const FVector2D SizeVector = FVector2D(0.45f, 0.3f);
	const FVector2D SpawnAmountVector = FVector2D(5, 20);
	const FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);
	const auto DesiredSize = FMath::GetMappedRangeValueClamped(SpawnAmountVector, SizeVector, ClickableCirclesSpawnAmount);
	
	for(size_t i = 0; i < ClickableCirclesSpawnAmount; ++i)
	{
		const auto ClickableCircle = GetWorld()->SpawnActor<ABTClickableCircle>(ClickableCircleClass, GetClickableCircleRandomLocation(), Rotation);
		ClickableCircle->SetActorScale3D(FVector(DesiredSize));

		int32 CirclesSpawnIterationIndex = 0;
		
		while (ClickableCircle->IsOverlappingAnotherActor())
		{
			if(++CirclesSpawnIterationIndex >= 500)
			{
				EmptyClickableCirclesArray();
				DestroyAllClickableCirclesFromScene();
				InitClickableCircles();
				return;
			}
			
			ClickableCircle->SetActorLocation(GetClickableCircleRandomLocation());
		}
		
		ClickableCircle->OnSphereReleased.AddUObject(this, &ABTClickableCirclesSpawnManager::OnClickableCircleSphereReleased);
		
		ClickableCircle->SetWidgetColor(ClickableCircleBodyButtonColor, ClickableCircleEdgingImageColor);
		ClickableCircle->HideBodyImage();
		ClickableCircle->DisableCollision();
		
		ClickableCircles.Add(ClickableCircle);
	}

	for(size_t i = 0; i < ClickableCircles.Num(); ++i)
	{
		const auto ViewNumber = GetGeneratedClickableCircleNumber(i);
		ClickableCircles[i]->SetViewNumber(ViewNumber);
	}

	LastClickedCircleIndex = 0;
}

void ABTClickableCirclesSpawnManager::StartClickableCirclesViewNumberHidingTimer()
{
	if(GetWorld()->GetTimerManager().IsTimerActive(ViewNumberHidingClickableCirclesTimerHandle))
		GetWorld()->GetTimerManager().ClearTimer(ViewNumberHidingClickableCirclesTimerHandle);

	GetWorld()->GetTimerManager().SetTimer(ViewNumberHidingClickableCirclesTimerHandle, this, &ABTClickableCirclesSpawnManager::UpdateClickableCircleViewNumberHidingCountdown, 1.0f, true, 1.0f);
}

void ABTClickableCirclesSpawnManager::DeleteFirstClickableCirclesArrayElement()
{
	if(IsClickableCirclesArrayEmpty())  return;

	ClickableCircles.RemoveAt(0);
}

bool ABTClickableCirclesSpawnManager::IsClickableCirclesArrayEmpty() const
{
	return ClickableCircles.IsEmpty();
}

void ABTClickableCirclesSpawnManager::HideAllClickableCirclesBodies()
{
	if(ClickableCircles.IsEmpty()) return;

	for(auto ClickableCircle : ClickableCircles)
	{
		ClickableCircle->HideBodyImage();
	}
}

void ABTClickableCirclesSpawnManager::DisableAllClickableCirclesCollisions()
{
	if(ClickableCircles.IsEmpty()) return;

	for(auto ClickableCircle : ClickableCircles)
	{
		ClickableCircle->DisableCollision();
	}
}

void ABTClickableCirclesSpawnManager::EnableAllClickableCirclesCollisions()
{
	if(ClickableCircles.IsEmpty()) return;

	for(auto ClickableCircle : ClickableCircles)
	{
		ClickableCircle->EnableCollision();
	}
}

ABTClickableCircle* ABTClickableCirclesSpawnManager::GetFirstClickableCircleArrayElement()
{
	if(ClickableCircles.IsEmpty()) return nullptr;
	
	return ClickableCircles[0];
}

void ABTClickableCirclesSpawnManager::DestroyAllClickableCirclesFromScene()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClickableCircleClass, Actors);

	for(auto Actor : Actors)
	{
		Actor->Destroy();
	}
}

void ABTClickableCirclesSpawnManager::EmptyClickableCirclesArray()
{
	if(ClickableCircles.IsEmpty()) return;
	
	ClickableCircles.Empty();
}

void ABTClickableCirclesSpawnManager::SetSpawnClickableCirclesParameters(int32 SpawnAmount, int32 ViewNumberHidingCountdown, int32 MaxNumber)
{
	ClickableCirclesSpawnAmount = SpawnAmount;
	
	MaxClickableCircleViewNumberHidingCountdown = ViewNumberHidingCountdown;
	ResetCurrentClickableCircleViewNumberHidingCountdown();
	
	MaxClickableCircleNumber = MaxNumber;
}

void ABTClickableCirclesSpawnManager::ClearViewNumberHidingClickableCirclesTimer()
{
	if(!GetWorld()) return;

	GetWorld()->GetTimerManager().ClearTimer(ViewNumberHidingClickableCirclesTimerHandle);
}

bool ABTClickableCirclesSpawnManager::AreClickableCirclesCollisionsEnabled()
{
	for(const auto ClickableCircle : ClickableCircles)
	{
		if(!ClickableCircle->IsCollisionEnabled())
			return false;
	}

	return true;
}

void ABTClickableCirclesSpawnManager::OnClickableCircleSphereReleased(const ABTClickableCircle* ClickableCircle)
{
	ClickableCircle->HideBodyImage();
	OnClickableCircleSelected.Broadcast(ClickableCircle);
}

FLinearColor ABTClickableCirclesSpawnManager::GetRandomClickedCirclesBodyColor() const
{
	const auto ClickedCircleInR = FMath::RandRange(0.4f, 0.9f);
	const auto ClickedCircleInG = FMath::RandRange(0.4f, 0.9f);
	const auto ClickedCircleInB = FMath::RandRange(0.4f, 0.9f);

	return FLinearColor(ClickedCircleInR, ClickedCircleInG, ClickedCircleInB, 1.0f);
}

int32 ABTClickableCirclesSpawnManager::GetGeneratedClickableCircleNumber(size_t Index)
{
	const auto MaxDesiredNumber = MaxClickableCircleNumber - ClickableCircles.Num() + 1 + Index;
	const auto DesiredNumber = FMath::RandRange(LastClickedCircleIndex, MaxDesiredNumber);

	LastClickedCircleIndex = DesiredNumber + 1;
	return DesiredNumber;
}

void ABTClickableCirclesSpawnManager::UpdateClickableCircleViewNumberHidingCountdown()
{
	if(--CurrentClickableCircleViewNumberHidingCountdown > 0) return;

	GetWorld()->GetTimerManager().ClearTimer(ViewNumberHidingClickableCirclesTimerHandle);
	ResetCurrentClickableCircleViewNumberHidingCountdown();
	
	for(auto ClickableCircle : ClickableCircles)
	{
		ClickableCircle->EnableCollision();
		ClickableCircle->ShowBodyImage();
	}
}

FVector ABTClickableCirclesSpawnManager::GetClickableCircleRandomLocation()
{
	const auto LocationBorderX = FVector2D(-380.0f, 380.0f);
	const auto LocationBorderZ = FVector2D(-600.0f, 650.0f);

	const auto RandomLocationX = FMath::RandRange(LocationBorderX.X, LocationBorderX.Y);
	const auto RandomLocationZ = FMath::RandRange(LocationBorderZ.X, LocationBorderZ.Y);
	
	return FVector(RandomLocationX, 1.0f, RandomLocationZ);
}

void ABTClickableCirclesSpawnManager::ResetCurrentClickableCircleViewNumberHidingCountdown()
{
	CurrentClickableCircleViewNumberHidingCountdown = MaxClickableCircleViewNumberHidingCountdown;
}



