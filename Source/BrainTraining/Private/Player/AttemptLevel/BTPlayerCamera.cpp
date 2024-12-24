// A BrainTraining Game. All Right Reserved.

#include "AttemptLevel/BTPlayerCamera.h"
#include "BTClickableCircle.h"
#include "InputAction.h"
#include "AttemptLevel/BTPlayerController.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputSubsystemInterface.h"
#include "EnhancedInputComponent.h"

ABTPlayerCamera::ABTPlayerCamera()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	SetRootComponent(SceneComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetProjectionMode(ECameraProjectionMode::Orthographic);
	CameraComponent->bConstrainAspectRatio = true;
	CameraComponent->SetAspectRatio(0.5625f);
	CameraComponent->SetOrthoWidth(1010.0f);
}

void ABTPlayerCamera::BeginPlay()
{
	Super::BeginPlay();

	check(InputMappingContext);
	check(ClickInputAction);
	
	InitPlayerController();
	check(BTController);

	AddMappingContext();
}

void ABTPlayerCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const auto EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(ClickInputAction, ETriggerEvent::Started, this, &ABTPlayerCamera::Click);
}

void ABTPlayerCamera::InitPlayerController()
{
	BTController = CastChecked<ABTPlayerController>(Controller);
}

void ABTPlayerCamera::AddMappingContext()
{
	const auto SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(BTController->GetLocalPlayer());
	SubSystem->AddMappingContext(InputMappingContext, 0);
}

void ABTPlayerCamera::Click()
{
	FHitResult ClickHitResult;
	
	BTController->GetHitResultUnderCursor(ECC_Camera, false, ClickHitResult);

	const auto TracedComponent = ClickHitResult.GetComponent();
	if(!TracedComponent) return;

	const auto TracedClickableCircle = Cast<ABTClickableCircle>(TracedComponent->GetOwner());
	if(!TracedClickableCircle) return;

	TracedClickableCircle->OnSphereReleased.Broadcast(TracedClickableCircle);
}


