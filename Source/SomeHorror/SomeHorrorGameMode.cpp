// Copyright Epic Games, Inc. All Rights Reserved.

#include "SomeHorrorGameMode.h"
#include "SomeHorrorCharacter.h"
#include "Characters/PlayerCharacter.h"
#include "Characters/EnemyCharacter/EnemyCharacter.h"
#include "Characters/EnemyCharacter/PlayerEnemyCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASomeHorrorGameMode::ASomeHorrorGameMode()
	: Super()
{
	//static ConstructorHelpers::FClassFinder<APawn> PlayerCharacterBPClass(TEXT("/Game/CharactersBP/BPPlayerCharacter"));
	DefaultPawnClass = EnemyCharacter;
	
	//static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonPlayerController"));

}

void ASomeHorrorGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	//static ConstructorHelpers::FClassFinder<APawn> PlayerCharacterBPClass(TEXT("/Game/CharactersBP/BPPlayerCharacter"));
	//DefaultPawnClass = PlayerCharacterBPClass.Class;
	
	//static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonPlayerController"));
	//PlayerControllerClass = PlayerControllerBPClass.Class;

	AActor* PlayerStart = ChoosePlayerStart(NewPlayer);
	
	FVector SpawnLocation = PlayerStart->GetActorLocation();
	FRotator SpawnRotation = PlayerStart->GetActorRotation();
	

	if(IsHost(NewPlayer))
	{
		FActorSpawnParameters SpawnParams;
		APlayerEnemyCharacter* Pawn = GetWorld()->SpawnActor<APlayerEnemyCharacter>(EnemyCharacter, SpawnLocation, SpawnRotation, SpawnParams);
		if (Pawn)
		{
			NewPlayer->Possess(Pawn);
		}
	}

	else
	{
		FActorSpawnParameters SpawnParams;
		APlayerCharacter* Pawn = GetWorld()->SpawnActor<APlayerCharacter>(PlayerCharacter, SpawnLocation, SpawnRotation, SpawnParams);
		if (Pawn)
		{
			NewPlayer->Possess(Pawn);
		}
	}
	
	
	
}

const bool ASomeHorrorGameMode::IsHost(APlayerController* Controller)
{
	
	if (!IsValid(Controller))
	{
		return false;
	}

	return (Controller->HasAuthority() && Controller->IsLocalPlayerController());	

}
