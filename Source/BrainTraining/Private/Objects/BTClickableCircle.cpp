// A BrainTraining Game. All Right Reserved.

#include "BTClickableCircle.h"
#include "Components/WidgetComponent.h"
#include "BTClickableCircleWidget.h"
#include "Components/SphereComponent.h"

ABTClickableCircle::ABTClickableCircle()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(SphereComponent);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->InitSphereRadius(290.0f);
	
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Widget");
	WidgetComponent->SetupAttachment(GetRootComponent());
}

void ABTClickableCircle::InitWidget()
{
	const auto UserWidget = WidgetComponent->GetWidget();
	check(UserWidget);
	
	Widget = CastChecked<UBTClickableCircleWidget>(UserWidget);
}

void ABTClickableCircle::SetWidgetColor(const FLinearColor& BodyImageColor, const FLinearColor& EdgingImageColor) const
{
	if(!Widget) return;
	
	Widget->SetColor(BodyImageColor, EdgingImageColor);
}

void ABTClickableCircle::SetViewNumber(int32 Number) const
{
	if(!Widget) return;
	
	Widget->SetViewNumber(Number);
}

void ABTClickableCircle::ShowBodyImage() const
{
	if(!Widget) return;
	
	Widget->ShowBodyImage();
}

void ABTClickableCircle::HideBodyImage() const
{
	if(!Widget) return;
	
	Widget->HideBodyImage();
}

void ABTClickableCircle::DisableCollision() const
{
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABTClickableCircle::EnableCollision() const
{
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

bool ABTClickableCircle::IsOverlappingAnotherActor()  
{
	TArray<AActor*> OverlappedActors;
	SphereComponent->GetOverlappingActors(OverlappedActors);
	OverlappedActors.Remove(this);
	
	return !OverlappedActors.IsEmpty();
}

bool ABTClickableCircle::IsCollisionEnabled() const
{
	return SphereComponent->IsCollisionEnabled();
}

void ABTClickableCircle::BeginPlay()
{
	Super::BeginPlay();
	
	InitWidget();
	check(Widget);
}

