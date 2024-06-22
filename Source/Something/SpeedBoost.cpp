// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedBoost.h"
#include "Components/SphereComponent.h"
#include "KartPawn.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpeedBoost::ASpeedBoost()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SetRootComponent(SphereCollider);

	SphereCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SphereCollider->SetCollisionProfileName(FName("OverlapAllDynamic"));

}

// Called when the game starts or when spawned
void ASpeedBoost::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASpeedBoost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> OverlapActors;
	GetOverlappingActors(OverlapActors, AKartPawn::StaticClass());
	if (!OverlapActors.IsEmpty())
	{
		HitKart = Cast<AKartPawn>(OverlapActors[0]);
		ApplySpeedBoost();
	}

}

void ASpeedBoost::ApplySpeedBoost()
{
	if (!HitKart)
	{
		return;
	}

	UBoxComponent* KartBox = HitKart->GetComponentByClass<UBoxComponent>();
	FVector Impulse = HitKart->GetActorForwardVector() * BoostImpulseSpeed;
	KartBox->AddImpulse(Impulse, NAME_None, true);

	HitKart->MaxSpeed += SpeedBoostAmount;

	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);

	FTimerHandle BoostTimer;
	GetWorldTimerManager().SetTimer(
		BoostTimer,
		this,
		&ASpeedBoost::SpeedBoostOver,
		3.0f,
		false
	);


}

void ASpeedBoost::SpeedBoostOver()
{
	HitKart->MaxSpeed -= SpeedBoostAmount;
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

