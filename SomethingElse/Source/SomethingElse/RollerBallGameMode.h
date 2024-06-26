// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlatformBase.h"
#include "RollerBallGameMode.generated.h"

/**
 *
 */
UCLASS()
class SOMETHINGELSE_API ARollerBallGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<APlatformBase>> PlatformClassArray;

};
