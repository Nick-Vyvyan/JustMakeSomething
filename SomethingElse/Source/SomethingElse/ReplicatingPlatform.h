// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReplicatingPlatform.generated.h"

class UBoxComponent;
class UArrowComponent;

UCLASS()
class SOMETHINGELSE_API AReplicatingPlatform : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AReplicatingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Trigger")
	UBoxComponent* KillTrigger;

	UPROPERTY(EditAnywhere, Category = "Trigger")
	UBoxComponent* EndTrigger;

	UArrowComponent* EndLocation;
};
