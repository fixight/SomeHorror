// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "SomeHorror/Characters/PlayerCharacter.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	

	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	
	
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}


void UHealthComponent::KnockDown()
{
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle , [this]()
	{
		CurrentHealth -= 1.0f;

		if(PlayerCharacter->GetPlayerState() == EPlayerState::EPS_Alive)
		{
			CurrentHealth = RecoverHealth;
			GetWorld()->GetTimerManager().ClearTimer(DeadTimerHandle);
		}

	}, 1.0f , true  , -1.0f);
}

void UHealthComponent::TakeDamage(const float Damage)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage , 0.0f , MaxHealth);

	if(CurrentHealth == 0.0f)
	{
		switch (PlayerCharacter->GetPlayerState())
		{
		case EPlayerState::EPS_Alive :
			PlayerCharacter->PlayerKnockDown();
			GEngine->AddOnScreenDebugMessage(-1 , 3.0f , FColor::Red , "TakeDamage");
			CurrentHealth = KnockHealth;
			break;

		case EPlayerState::EPS_KnockDown :
			PlayerCharacter->PlayerDead();
			break;

		default:
			break;
		}
	}
}

void UHealthComponent::RegenerateHealth(const float Health)
{
	CurrentHealth = FMath::Clamp(CurrentHealth += Health , 0.0f , MaxHealth);
}
