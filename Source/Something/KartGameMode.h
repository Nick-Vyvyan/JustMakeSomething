// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KartPawn.h"
#include "KartGameMode.generated.h"

/**
 *
 */
UCLASS()
class SOMETHING_API AKartGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Karts")
	TArray<TSubclassOf<AKartPawn>> KartTypes;

};
