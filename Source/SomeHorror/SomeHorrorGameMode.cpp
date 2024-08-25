// Copyright Epic Games, Inc. All Rights Reserved.

#include "SomeHorrorGameMode.h"
#include "SomeHorrorCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASomeHorrorGameMode::ASomeHorrorGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
