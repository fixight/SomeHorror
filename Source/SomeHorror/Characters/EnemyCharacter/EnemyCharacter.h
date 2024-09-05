// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SomeHorror/Characters/PlayerCharacter.h"
#include "EnemyCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnEnemyBecomeAngry);

UCLASS()
class SOMEHORROR_API AEnemyCharacter : public APlayerCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;

protected:
	void Empower();

	void ResetStats();

protected:
	UPROPERTY(EditDefaultsOnly , Category = "Movement")
	float DefaultEnemySpeed = 800.0f;
	
	UPROPERTY(EditDefaultsOnly , Category = "Movement")
	float EmpowerEnemySpeed = 900.0f;

	UPROPERTY(EditDefaultsOnly , Category = "Stats")
	float EmpowerDuration = 40.0f;

	UPROPERTY(EditDefaultsOnly , Category = "Stats")
	float EmpowerCooldown = 40.0f;

	
protected:
	float EmpowerlastTime = 0.0f;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* AngryAction;

public:
	FOnEnemyBecomeAngry OnEnemyBecomeAngryDelegate;

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
