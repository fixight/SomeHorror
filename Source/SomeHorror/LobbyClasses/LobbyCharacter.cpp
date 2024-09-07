// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyCharacter.h"

// Sets default values
ALobbyCharacter::ALobbyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	

}

void ALobbyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALobbyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ALobbyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

