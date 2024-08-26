// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "CustomPlayerState.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "SomeHorror/Components/HealthComponent.h"
#include "PlayerCharacter.generated.h"



UCLASS()
class SOMEHORROR_API APlayerCharacter : public ACharacter
{
	friend UHealthComponent;

	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(EditDefaultsOnly , Category = DefaultComponents)
	UCameraComponent* PlayerCamera;

	UPROPERTY(EditDefaultsOnly , Category = DefaultComponents)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly , Category = DefaultComponents)
	UHealthComponent* HealthComponent;


protected:
	void Move(const FInputActionValue& Value);
	
	void Look(const FInputActionValue& Value);


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* RunAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* CrouchAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* EquipAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

protected:

	UFUNCTION(Server , Reliable)
	void PlayerKnockDown();

	void PlayerRecovered();

	void PlayerCrouch();
	
	void PlayerStopCrouch();

	UFUNCTION(Server , Reliable)
	void PlayerStartRunning();

	UFUNCTION(Server , Reliable)
	void PlayerStopRunning();

	void PlayerStartCarrying();

	void PlayerStopCarrying();

	void PlayerDead();

	void EquipButtonPressed();



protected:
	UFUNCTION(Server , Reliable)
	void ChangeMaxSpeed_Server(const float Speed);

	UFUNCTION(Server , Reliable)
	void Damage_Server(APlayerCharacter* PlayerCharacter);

	UFUNCTION(Server , Reliable)
	void ChangePlayerMovementState_Server(const EPlayerMovementState MovementState);

	UFUNCTION(Server , Reliable)
	void ChangePlayerState_Server(const EPlayerState State);

	UFUNCTION()
	void OnRep_MaxSpeed();

	UFUNCTION()
	void OnRep_MovementState();

protected:
	UPROPERTY(EditDefaultsOnly , Category = "Movement")
	float MaxWalkSpeed = 400.0f;

	UPROPERTY(EditDefaultsOnly , Category = "Movement")
	float MaxRunSpeed = 650.0f;

	UPROPERTY(ReplicatedUsing = OnRep_MaxSpeed)
	float MaxSpeed = MaxWalkSpeed;


protected:


protected:
	UPROPERTY(Replicated)
	EPlayerState PlayerCustomState = EPlayerState::EPS_Alive;

	UPROPERTY(ReplicatedUsing = OnRep_MovementState)
	EPlayerMovementState PlayerMovementState = EPlayerMovementState::EPMS_Default;

public:
	UFUNCTION(BlueprintCallable)
	EPlayerMovementState GetPlayerMovementState(){return PlayerMovementState;}

	UFUNCTION(BlueprintCallable)
	EPlayerState GetPlayerState(){return PlayerCustomState;}

	UFUNCTION(BlueprintCallable)
	UHealthComponent* GetHealthComponent(){return HealthComponent;}

	

};
