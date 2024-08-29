// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"

#include "SomeHorror/Characters/PlayerCharacter.h"

void UCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(!PlayerCharacter) return;

	PlayerMovementState = PlayerCharacter->GetPlayerMovementState();
	PlayerState = PlayerCharacter->GetPlayerState();

	CalculateDirectionsRates(PlayerForwardDirectionRate , PlayerRightDirectionRate);
}

void UCharacterAnimInstance::CalculateDirectionsRates(float& Forward, float& Right)
{
	FVector VelocitySafe = PlayerCharacter->GetVelocity().GetSafeNormal();
	Right = FVector::DotProduct(PlayerCharacter->GetActorRightVector().GetSafeNormal() , VelocitySafe);
	Forward = FVector::DotProduct(PlayerCharacter->GetActorForwardVector() , VelocitySafe);
}
