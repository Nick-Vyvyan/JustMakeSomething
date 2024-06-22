// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpeedBoost.generated.h"

UCLASS()
class SOMETHING_API ASpeedBoost : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpeedBoost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ApplySpeedBoost();

	void SpeedBoostOver();

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float SpeedBoostAmount = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float BoostImpulseSpeed = 5000;


private:
	class AKartPawn* HitKart;
};
