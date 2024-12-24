// A BrainTraining Game. All Right Reserved.

#include "BTGameInstance.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

void UBTGameInstance::InitDefaultSpawnClickableCirclesParameters()
{
	ClickableCirclesSpawnAmount = FMath::Clamp(ClickableCirclesSpawnAmount, MinClickableCirclesSpawnAmount, MaxClickableCirclesSpawnAmount);
	MaxClickableCircleViewNumberHidingCountdown = FMath::Clamp(MaxClickableCircleViewNumberHidingCountdown, MinMaxClickableCircleViewNumberHidingCountdown, MaxMaxClickableCircleViewNumberHidingCountdown);
	MaxClickableCircleNumber = FMath::Clamp(MaxClickableCircleNumber, MinMaxClickableCircleNumber, MaxMaxClickableCircleNumber);
}

void UBTGameInstance::IncreaseSuccessfulAttemptAmount()
{
	++SuccessfulAttemptAmount;
}

void UBTGameInstance::IncreaseFailedAttemptAmount()
{
	++FailedAttemptAmount;
}

void UBTGameInstance::UpdateMostDifficultLevelNumber()
{
	if(MostDifficultLevelNumber >= ClickableCirclesSpawnAmount) return;
	
	MostDifficultLevelNumber = ClickableCirclesSpawnAmount;
}

void UBTGameInstance::PlayMainMusic()
{
	if(!MainAudioComponent)
	{
		MainAudioComponent = UGameplayStatics::CreateSound2D(GetWorld(), MainBackgroundSoundBase, 1.0f, 1.0, 0.0f, nullptr, true);	
	}
	
	if(MainAudioComponent->IsPlaying()) return;

	MainAudioComponent->Play();
}

void UBTGameInstance::StopMainMusic()
{
	MainAudioComponent->Stop();
}
