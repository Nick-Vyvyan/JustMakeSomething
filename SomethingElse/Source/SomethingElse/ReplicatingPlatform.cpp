// Fill out your copyright notice in the Description page of Project Settings.


#include "ReplicatingPlatform.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AReplicatingPlatform::AReplicatingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EndLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("End Location"));
	EndLocation->SetupAttachment(RootComponent);

	KillTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Kill Trigger"));
	KillTrigger->SetupAttachment(RootComponent);

	EndTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("End Trigger"));
	EndTrigger->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AReplicatingPlatform::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AReplicatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

