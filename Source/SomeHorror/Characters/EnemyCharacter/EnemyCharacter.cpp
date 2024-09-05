// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "EnhancedInputComponent.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = DefaultEnemySpeed;
}

void AEnemyCharacter::Empower()
{
	if(GetWorld()->GetTimeSeconds() - EmpowerlastTime < EmpowerCooldown) return;

	EmpowerlastTime = GetWorld()->GetTimeSeconds();
	
	GetCharacterMovement()->MaxWalkSpeed = EmpowerEnemySpeed;

	FTimerHandle ResetEmpowerTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(ResetEmpowerTimerHandle , [this]()
	{
		ResetStats();
	} , 1.0f , false , EmpowerDuration);

	
}

void AEnemyCharacter::ResetStats()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultEnemySpeed;
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	RunAction = nullptr;

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(AngryAction, ETriggerEvent::Started, this, &AEnemyCharacter::Empower);
		GEngine->AddOnScreenDebugMessage(-1 , 5.0f , FColor::Purple , FString::FromInt(RunInputBindingHandle));
		EnhancedInputComponent->RemoveBindingByHandle(RunInputBindingHandle);
		EnhancedInputComponent->RemoveBindingByHandle(StopRunInputBindingHandle);
	}

}

