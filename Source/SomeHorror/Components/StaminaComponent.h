// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SomeHorror/Characters/PlayerCharacter.h"
#include "StaminaComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOMEHORROR_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStaminaComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	APlayerCharacter* PlayerCharacter;
	
	UPROPERTY(EditDefaultsOnly , Category = "Parametrs")
	float ConsumeSpeed = 10.0f;

	UPROPERTY(EditDefaultsOnly , Category = "Parametrs")
	float MaxStamina = 100.0f;

	UPROPERTY(EditDefaultsOnly , Category = "Parametrs")
	float RegenerateSpeed = 1.0f;

	float CurrentStamina = MaxStamina;

	bool IsRunning = false;

public:
	void StartConsumeStamina();

	void StartRegenerateStamina();

public:
	bool CanRun = true;


private:
	void ConsumeStamina(const float DeltaTime);

	void RegenerateStamina(const float DeltaTime);
	

		
};
