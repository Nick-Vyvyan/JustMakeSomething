// Fill out your copyright notice in the Description page of Project Settings.


#include "KartPawn.h"
#include "Components/BoxComponent.h"
#include "WheelComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AKartPawn::AKartPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);
	RootComp->SetSimulatePhysics(true);
	RootComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComp->SetCollisionProfileName(FName("BlockAll"));
	RootComp->SetLinearDamping(3);
	RootComp->SetAngularDamping(5);

	UWheelComponent* FL_Wheel = CreateDefaultSubobject<UWheelComponent>(TEXT("Front Left Wheel"));
	FL_Wheel->SetupAttachment(RootComp);
	WheelComponents.Add(FL_Wheel);

	UWheelComponent* FR_Wheel = CreateDefaultSubobject<UWheelComponent>(TEXT("Front Right Wheel"));
	FR_Wheel->SetupAttachment(RootComp);
	WheelComponents.Add(FR_Wheel);

	UWheelComponent* BL_Wheel = CreateDefaultSubobject<UWheelComponent>(TEXT("Back Left Wheel"));
	BL_Wheel->SetupAttachment(RootComp);
	WheelComponents.Add(BL_Wheel);

	UWheelComponent* BR_Wheel = CreateDefaultSubobject<UWheelComponent>(TEXT("Back Right Wheel"));
	BR_Wheel->SetupAttachment(RootComp);
	WheelComponents.Add(BR_Wheel);

}

// Called when the game starts or when spawned
void AKartPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AKartPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (UWheelComponent* Wheel : WheelComponents)
	{
		ApplyWheelForces(Wheel);
	}

}


void AKartPawn::ApplySteeringTorque(float InputValue)
{
	FVector TorqueVector = FVector(0, 0, InputValue * SteeringStrength * AccelerationInput);
	RootComp->AddTorqueInRadians(TorqueVector);
}

void AKartPawn::ApplyWheelForces(UWheelComponent* Wheel)
{
	FHitResult HitResult;
	if (Wheel->SuspensionRayCast(HitResult))
	{
		// Normalize Hit distance between 0 and the Max Suspension Distance of the wheel and then flip
		float NormalizedDistance = 1 - (HitResult.Distance - 0) / (FMath::Abs(Wheel->SuspensionRange) - 0);

		FVector DummyDirection = HitResult.TraceStart - HitResult.TraceEnd;
		float DummyDistance;
		FVector UnitDirection;
		DummyDirection.ToDirectionAndLength(UnitDirection, DummyDistance);

		FVector SuspensionVector = UnitDirection * NormalizedDistance * SuspensionForce;

		RootComp->AddForceAtLocation(
			SuspensionVector,
			Wheel->GetComponentLocation()
		);

		//UE_LOG(LogTemp, Warning, TEXT("%s Applied Force: %s"), *Wheel->GetName(), *ForceVector.ToString());

	}

	ApplyAccelerationForce(Wheel);
}


void AKartPawn::SetAccelerationInput(float InputValue)
{
	bHasAccelerationInput = true;
	AccelerationInput = FMath::FInterpTo(AccelerationInput, InputValue, UGameplayStatics::GetWorldDeltaSeconds(this), 0.5);
}

void AKartPawn::ApplyAccelerationForce(UWheelComponent* Wheel)
{
	// Set Default Acceleration Input - This will fight (but lose) against player input
	if (!bHasAccelerationInput || !Wheel->bIsGrounded)
	{
		AccelerationInput = FMath::FInterpTo(AccelerationInput, 0, UGameplayStatics::GetWorldDeltaSeconds(this), 0.05);
	}


	float Acceleration = FMath::Lerp(0, AccelerationRate, AccelerationInput) * AccelerationInput;

	FVector AccelerationVector = RootComp->GetForwardVector() * AccelerationInput * Acceleration * RootComp->GetMass();
	RootComp->AddForceAtLocation(
		AccelerationVector,
		Wheel->GetComponentLocation()
	);
}

// Called to bind functionality to input
void AKartPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


