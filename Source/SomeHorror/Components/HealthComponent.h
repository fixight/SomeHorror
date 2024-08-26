// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOMEHORROR_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;
	
	UPROPERTY(EditDefaultsOnly , Category = "Health")
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly , Category = "Health")
	float RecoverHealth = 50.0f;

	UPROPERTY(EditDefaultsOnly , Category = "Health")
	float KnockHealth = 100.0f;

	UPROPERTY()
	float CurrentHealth = MaxHealth;

	FTimerHandle DeadTimerHandle;

private:
	void KnockDown();

public:
	void TakeDamage(const float Damage);

	void RegenerateHealth(const float Health);

	float GetCurrentHealth(){return CurrentHealth;}

		
};


