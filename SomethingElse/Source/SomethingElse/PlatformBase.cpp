// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformBase.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
APlatformBase::APlatformBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(RootComp);
	RootComp->bVisualizeComponent = true;

	NextSpawnLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("Next Spawn Location"));
	NextSpawnLocation->SetupAttachment(RootComp);
	NextSpawnLocation->SetRelativeLocation(FVector(1750, 0, -400));

	EndTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("End Trigger"));
	EndTrigger->SetupAttachment(RootComp);
	EndTrigger->SetRelativeLocation(FVector(1650, 0, 0));
	EndTrigger->SetBoxExtent(FVector(32, 2000, 2000));

	KillTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Kill Trigger"));
	KillTrigger->SetupAttachment(RootComp);
	KillTrigger->SetRelativeLocation(FVector(550, 0, -550));
	KillTrigger->SetBoxExtent(FVector(1000, 3000, 32));

}

// Called when the game starts or when spawned
void APlatformBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlatformBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


