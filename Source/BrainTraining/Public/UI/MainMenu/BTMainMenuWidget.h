// A BrainTraining Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BTMainMenuWidget.generated.h"

class UBTOptionsMenuWidget;
class UButton;
class UImage;
class UMediaSource;
class UMediaPlayer;

UCLASS()
class BRAINTRAINING_API UBTMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UButton* GetOptionsMenuButton() const { return OptionsButton; }
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> StartAttemptButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> OptionsButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UBTOptionsMenuWidget> OptionsMenuWidget;
	
	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMediaSource> TitleSource;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMediaPlayer> TitleMediaPlayer;
	
protected:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnStartAttemptButtonReleased();

	UFUNCTION()
	void OnOptionsButtonReleased();

	UFUNCTION()
	void OnApplyChangesButtonReleased();

	void InitPlayerController();
};
