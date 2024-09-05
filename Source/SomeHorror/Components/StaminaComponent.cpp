// Fill out your copyright notice in the Description page of Project Settings.

#include "StaminaComponent.h"

#include "Engine/Engine.h"
#include "SomeHorror/Characters/EnemyCharacter/EnemyCharacter.h"

UStaminaComponent::UStaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	if(GetOwner()->IsA(AEnemyCharacter::StaticClass())) PrimaryComponentTick.bCanEverTick = false;
	

	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	
	
}

void UStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(IsRunning) ConsumeStamina(DeltaTime);

	else RegenerateStamina(DeltaTime);
	
}

void UStaminaComponent::StartConsumeStamina()
{
	IsRunning = true;
}

void UStaminaComponent::StartRegenerateStamina()
{
	IsRunning = false;
}

void UStaminaComponent::ConsumeStamina(const float DeltaTime)
{
	SetComponentTickEnabled(true);

	CurrentStamina = FMath::Clamp(CurrentStamina - DeltaTime * ConsumeSpeed , 0.0f , MaxStamina);

	if(CurrentStamina == 0.0f)
	{
		CanRun = false;
		PlayerCharacter->PlayerStopRunning();
	}
		
}

void UStaminaComponent::RegenerateStamina(const float DeltaTime)
{
	CurrentStamina = FMath::Clamp(CurrentStamina + DeltaTime * RegenerateSpeed , 0.0f , MaxStamina);

	if(CurrentStamina  > 10.0f) CanRun = true;

	if(CurrentStamina == MaxStamina) SetComponentTickEnabled(false);
	
}

