// Fill out your copyright notice in the Description page of Project Settings.


#include "KartPawn.h"
#include "Components/BoxComponent.h"
#include "WheelComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

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

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComp);
	SpringArm->bEnableCameraLag = true;
	SpringArm->TargetArmLength = 750;
	SpringArm->SocketOffset.Z = 100;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArm);
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
	bAllWheelsGrounded = true;

	for (UWheelComponent* Wheel : WheelComponents)
	{
		ApplyWheelForces(Wheel);
		if (!Wheel->bIsGrounded)
		{
			bAllWheelsGrounded = false;
		}
	}

	RootComp->AddForceAtLocation(
		FVector::UpVector * -AdditionalDownForce,
		RootComp->GetCenterOfMass()
	);

	Speed = GetVelocity().Length() / 100;

}


void AKartPawn::ApplySteeringTorque(float InputValue)
{
	FVector TorqueVector = FVector(0, 0, InputValue * SteeringStrength * AccelerationInput);
	if (bUseHandbrake)
	{
		TorqueVector = FVector(0, 0, InputValue * SteeringStrength * AccelerationInput * HandbrakeTurnMultiplier);
	}


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


	float Acceleration = FMath::Lerp(0, MaxSpeed, AccelerationInput) * AccelerationInput;

	FVector AccelerationVector = RootComp->GetForwardVector() * AccelerationInput * Acceleration * RootComp->GetMass();
	RootComp->AddForceAtLocation(
		AccelerationVector,
		Wheel->GetComponentLocation()
	);
}

void AKartPawn::ApplyHandbrake()
{
	AccelerationInput = FMath::FInterpTo(AccelerationInput, 0, UGameplayStatics::GetWorldDeltaSeconds(this), 0.05);
	bUseHandbrake = true;
}

void AKartPawn::CameraLookX(float InputValueX)
{
	FRotator XRotation = FRotator(0, InputValueX, 0);
	SpringArm->AddRelativeRotation(XRotation);
}

void AKartPawn::CameraLookY(float InputValueY)
{
	FRotator YRotation = FRotator(InputValueY, 0, 0);
	SpringArm->AddRelativeRotation(YRotation);
}

void AKartPawn::ResetPosition()
{
	if (bAllWheelsGrounded || Speed != 0)
	{
		return;
	}

	FVector CurrentPostion = GetActorLocation();
	FVector NewLocation = CurrentPostion + FVector(0, 0, 25);
	FRotator CurrentRotation = GetActorRotation();
	FRotator NewRotation = FRotator(0, CurrentRotation.Yaw, 0);

	SetActorLocationAndRotation(NewLocation, NewRotation);
}


// Called to bind functionality to input
void AKartPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


