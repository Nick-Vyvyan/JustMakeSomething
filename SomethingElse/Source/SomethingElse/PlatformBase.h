// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformBase.generated.h"

class UBoxComponent;
class UArrowComponent;

UCLASS()
class SOMETHINGELSE_API APlatformBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlatformBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	USceneComponent* RootComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trigger")
	UBoxComponent* KillTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trigger")
	UBoxComponent* EndTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UArrowComponent* NextSpawnLocation;

};
