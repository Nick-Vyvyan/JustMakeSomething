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

	UPROPERTY(EditAnywhere, Category = "Kart")
	TArray<class UWheelComponent*> WheelComponents;

	UPROPERTY(VisibleAnywhere, Category = "Kart")
	class UBoxComponent* RootComp;

	UPROPERTY(EditAnywhere, Category = "Kart")
	float SteeringStrength = 1000000;

	UPROPERTY(EditAnywhere, Category = "Kart")
	float SuspensionForce = 500000;

	UPROPERTY(EditAnywhere, Category = "Kart")
	float AccelerationRate = 1750;

	UPROPERTY(BlueprintReadWrite)
	bool bHasAccelerationInput = false;

	UFUNCTION(BlueprintCallable)
	void SetAccelerationInput(float InputValue);

	UFUNCTION(BlueprintCallable)
	void ApplyAccelerationForce(UWheelComponent* Wheel);

private:
	float AccelerationInput;
};
