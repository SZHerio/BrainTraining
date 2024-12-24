// A BrainTraining Game. All Right Reserved.

#include "BTAttemptLevelManager.h"
#include "BTAttemptLevelWidget.h"
#include "BTClickableCirclesSpawnManager.h"
#include "Kismet/GameplayStatics.h"
#include "BTAttemptLevelHUD.h"
#include "BTClickableCircle.h"
#include "BTGameInstance.h"
#include "Components/AudioComponent.h"

ABTAttemptLevelManager::ABTAttemptLevelManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABTAttemptLevelManager::BeginPlay()
{
	Super::BeginPlay();

	check(DifficultBackgroundSoundBase);
	
	InitPlayerController();
	check(PlayerController);
	
	InitBTGameInstance();
	
	InitClickableCirclesSpawnManager();
	check(ClickableCirclesSpawnManager);

	ClickableCirclesSpawnManager->OnClickableCircleSelected.AddUObject(this, &ABTAttemptLevelManager::OnClickableCircleSelected);
	
	InitBTHUD();
	check(AttemptLevelHUD);

	InitAttemptLevelWidget();
	check(AttemptLevelWidget);

	InitDifficultAudioComponent();
	
	AttemptLevelWidget->OnCountdownTimerIsUp.AddUObject(this, &ABTAttemptLevelManager::OnCountdownTimerIsUp);
	AttemptLevelWidget->OnTryAnotherAttemptButtonReleased.AddUObject(this, &ABTAttemptLevelManager::OnTryAnotherAttemptButtonReleased);
	AttemptLevelWidget->OnExitToMainMenuButtonReleased.AddUObject(this, &ABTAttemptLevelManager::OnExitToMainMenuButtonReleased);
	AttemptLevelWidget->OnBackgroundMusicShouldChange.AddUObject(this, &ABTAttemptLevelManager::OnBackgroundMusicShouldChange);
	AttemptLevelHUD->OnClickableCirclesCollisionsChanged.AddUObject(this, &ABTAttemptLevelManager::OnClickableCirclesCollisionsChanged);

	StartAttempt();
}

void ABTAttemptLevelManager::OnClickableCircleSelected(const ABTClickableCircle* ClickableCircle)
{
	const auto FirstClickableCircleArrayElement = ClickableCirclesSpawnManager->GetFirstClickableCircleArrayElement();
	if(!FirstClickableCircleArrayElement) return;

	PlayerController->PlayDynamicForceFeedback(0.3f, 0.1f, true, true, true, true);
	
	if(FirstClickableCircleArrayElement != ClickableCircle)
	{
		UGameplayStatics::PlaySound2D(this, FailPlayerAttemptSound);
		ClickableCirclesSpawnManager->HideAllClickableCirclesBodies();
		ClickableCirclesSpawnManager->DisableAllClickableCirclesCollisions();
		FailPlayerAttempt();
		return;
	}

	ClickableCirclesSpawnManager->DeleteFirstClickableCirclesArrayElement();
	ClickableCircle->DisableCollision();
	
	bool IsClickableCirclesArrayEmpty = ClickableCirclesSpawnManager->IsClickableCirclesArrayEmpty();
	USoundBase* SoundBaseToPlay = IsClickableCirclesArrayEmpty ? SucceedPlayerAttemptSound : ClickSoundBase;

	UGameplayStatics::PlaySound2D(this, SoundBaseToPlay);
	
	if(IsClickableCirclesArrayEmpty)
	{
		SucceedPlayerAttempt();
	}
}

void ABTAttemptLevelManager::OnCountdownTimerIsUp()
{
	if(!ClickableCirclesSpawnManager) return;
	
	ClickableCirclesSpawnManager->InitClickableCircles();
	ClickableCirclesSpawnManager->StartClickableCirclesViewNumberHidingTimer();
}

void ABTAttemptLevelManager::OnTryAnotherAttemptButtonReleased()
{
	if(!ClickableCirclesSpawnManager) return;

	HasPlayerFailed = !HasPlayerFailed;
	
	if(AttemptLevelHUD->ShouldSpawnManagerParametersBeUpdated())
	{
		UpdateSpawnManagerParameters();
		AttemptLevelHUD->SetShouldSpawnManagerParametersBeUpdated(false);
	}
	
	ClickableCirclesSpawnManager->DestroyAllClickableCirclesFromScene();
	ClickableCirclesSpawnManager->EmptyClickableCirclesArray();
	AttemptLevelWidget->HideTryAnotherAttemptButton();
	
	StartAttempt();
}

void ABTAttemptLevelManager::OnExitToMainMenuButtonReleased()
{
	ClickableCirclesSpawnManager->ClearViewNumberHidingClickableCirclesTimer();
}

void ABTAttemptLevelManager::OnBackgroundMusicShouldChange(EBackgroundMusicType Type)
{
	switch (Type)
	{
	case EBackgroundMusicType::Main:
		
		DifficultAudioComponent->Stop();
		BTGameInstance->PlayMainMusic();
		
		break;

	case EBackgroundMusicType::Difficult:

		BTGameInstance->StopMainMusic();
		
		if(!DifficultAudioComponent->IsPlaying())
		{
			DifficultAudioComponent->Play();	
		}
		
		break;
	}
}

void ABTAttemptLevelManager::OnClickableCirclesCollisionsChanged(bool ShouldCollisionsBeEnabled)
{
	if(ShouldCollisionsBeEnabled)
	{
		if(HasPlayerFailed) return;

		ClickableCirclesSpawnManager->EnableAllClickableCirclesCollisions();
	}
	else
	{
		ClickableCirclesSpawnManager->DisableAllClickableCirclesCollisions();
	}
}

void ABTAttemptLevelManager::InitBTGameInstance()
{
	BTGameInstance = CastChecked<UBTGameInstance>(GetGameInstance());
}

void ABTAttemptLevelManager::InitClickableCirclesSpawnManager()
{
	ClickableCirclesSpawnManager = CastChecked<ABTClickableCirclesSpawnManager>(GetWorld()->SpawnActor(ClickableCirclesSpawnManagerClass));
	UpdateSpawnManagerParameters();
}

void ABTAttemptLevelManager::InitBTHUD()
{
	if(!PlayerController) return;
	
	AttemptLevelHUD = Cast<ABTAttemptLevelHUD>(PlayerController->GetHUD());
}

void ABTAttemptLevelManager::InitAttemptLevelWidget()
{
	AttemptLevelWidget = AttemptLevelHUD->GetAttemptLevelWidget();
}

void ABTAttemptLevelManager::StartAttempt()
{
	BTGameInstance->GetClickableCirclesSpawnAmount() >= 20?
	AttemptLevelWidget->OnBackgroundMusicShouldChange.Broadcast(EBackgroundMusicType::Difficult)
		: AttemptLevelWidget->OnBackgroundMusicShouldChange.Broadcast(EBackgroundMusicType::Main);
	
	AttemptLevelWidget->SetCurrentSpawnClickedCirclesCountdown(MaxSpawnClickableCirclesCountdown);
	AttemptLevelWidget->StartAttempt();
}

void ABTAttemptLevelManager::SucceedPlayerAttempt() const
{
	BTGameInstance->IncreaseSuccessfulAttemptAmount();
	BTGameInstance->UpdateMostDifficultLevelNumber();
	AttemptLevelWidget->ShowTryAnotherAttemptButton();
	UGameplayStatics::PlaySound2D(this, SucceedPlayerAttemptSound);
}

void ABTAttemptLevelManager::FailPlayerAttempt()  
{
	HasPlayerFailed = true;
	BTGameInstance->IncreaseFailedAttemptAmount();
	AttemptLevelWidget->ShowTryAnotherAttemptButton();
}

void ABTAttemptLevelManager::UpdateSpawnManagerParameters()
{
	if(!ClickableCirclesSpawnManager) return;
	
	BTGameInstance = CastChecked<UBTGameInstance>(GetGameInstance());

	int32 ClickableCirclesSpawnAmount = BTGameInstance->GetClickableCirclesSpawnAmount();
	int32 MaxClickableCircleViewNumberHidingCountdown = BTGameInstance->GetMaxClickableCircleViewNumberHidingCountdown();
	int32 MaxClickableCircleNumber = BTGameInstance->GetMaxClickableCircleNumber();

	ClickableCirclesSpawnManager->SetSpawnClickableCirclesParameters(ClickableCirclesSpawnAmount, MaxClickableCircleViewNumberHidingCountdown,  MaxClickableCircleNumber);
}

void ABTAttemptLevelManager::InitPlayerController()
{
	if(!GetWorld()) return;
	
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

void ABTAttemptLevelManager::InitDifficultAudioComponent()
{
	DifficultAudioComponent = UGameplayStatics::CreateSound2D(GetWorld(), DifficultBackgroundSoundBase);
}


