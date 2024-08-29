// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SomeHorror/Characters/CustomPlayerState.h"
#include "CharacterAnimInstance.generated.h"


UCLASS()
class SOMEHORROR_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;


protected:
	UPROPERTY(BlueprintReadOnly)
	EPlayerMovementState PlayerMovementState = EPlayerMovementState::EPMS_Default;

	UPROPERTY(BlueprintReadOnly)
	EPlayerState PlayerState = EPlayerState::EPS_Alive;

	UPROPERTY(BlueprintReadOnly)
	float PlayerForwardDirectionRate = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	float PlayerRightDirectionRate = 0.0f;

private:
	void CalculateDirectionsRates(float& Forward , float& Right);
	
};
