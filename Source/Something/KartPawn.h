// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "KartPawn.generated.h"

UCLASS()
class SOMETHING_API AKartPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AKartPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void ApplyWheelForces(class UWheelComponent* Wheel);

	UFUNCTION(BlueprintCallable)
	void ApplySteeringTorque(float InputValue);

	UPROPERTY(VisibleAnywhere, Category = "Kart")
	TArray<class UWheelComponent*> WheelComponents;

	UPROPERTY(VisibleAnywhere, Category = "Kart")
	class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, Category = "Kart")
	class UBoxComponent* RootComp;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, Category = "Kart")
	float SteeringStrength = 1000000;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kart")
	float SteeringInput;

	UPROPERTY(EditAnywhere, Category = "Kart")
	float SuspensionForce = 500000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kart")
	float MaxSpeed = 1750;

	UPROPERTY(EditAnywhere, Category = "Kart")
	float AdditionalDownForce = 50000;

	UPROPERTY(BlueprintReadWrite)
	bool bHasAccelerationInput = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kart")
	int Speed;

	UPROPERTY(EditAnywhere, Category = "Kart")
	float HandbrakeTurnMultiplier = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUseHandbrake = false;

	UFUNCTION(BlueprintCallable)
	void SetAccelerationInput(float InputValue);

	UFUNCTION(BlueprintCallable)
	void ApplyAccelerationForce(UWheelComponent* Wheel);

	UFUNCTION(BlueprintCallable)
	void ApplyHandbrake();

	UFUNCTION(BlueprintCallable)
	void CameraLookX(float InputValueX);

	UFUNCTION(BlueprintCallable)
	void CameraLookY(float InputValueY);

	UFUNCTION(BlueprintCallable)
	void ResetPosition();


private:
	float AccelerationInput;
	bool bAllWheelsGrounded;
};
