// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/EnemyCharacter/EnemyCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "SomeHorrorGameMode.generated.h"

UCLASS(minimalapi)
class ASomeHorrorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASomeHorrorGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

protected:
	const bool IsHost(APlayerController* PlayerController);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemyCharacter> EnemyCharacter;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APlayerCharacter> PlayerCharacter;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APlayerController> PlayerController;
};



