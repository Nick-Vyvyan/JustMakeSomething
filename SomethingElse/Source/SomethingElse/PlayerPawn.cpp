// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetLinearDamping(0.25);
	Mesh->SetAngularDamping(0.025);


	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward Arrow"));
	ForwardArrow->SetupAttachment(Mesh);
	ForwardArrow->SetUsingAbsoluteRotation(true);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(Mesh);
	SpringArm->TargetArmLength = 650;
	SpringArm->SocketOffset.Z = 350;
	SpringArm->SetUsingAbsoluteRotation(true);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm);
	CameraComponent->SetRelativeRotation(FRotator(-30, 0, 0));

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(LeftRightAction, ETriggerEvent::Triggered, this, &APlayerPawn::PushLeftRight);
	}

}

void APlayerPawn::PushLeftRight(const FInputActionValue& Value)
{

	FVector Force = ForwardArrow->GetRightVector() * Value.Get<float>() * ForceMultiplier;

	Mesh->AddForce(Force, NAME_None, true);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();


}


// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("Actor Location : %s"), *GetActorLocation().ToString());
	FVector ConstantForce = ForwardArrow->GetForwardVector() * ConstantAcceleration * DeltaTime;
	Mesh->AddForce(ConstantForce, NAME_None, true);
}



