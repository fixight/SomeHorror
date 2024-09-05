// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultEquipeActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"

ADefaultEquipeActor::ADefaultEquipeActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	SetRootComponent(SceneComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCompoent"));
	MeshComponent->SetupAttachment(SceneComponent);

	bReplicates = true;
	
	
}

void ADefaultEquipeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADefaultEquipeActor::Interact()
{
	checkf(true , TEXT("FunctionMustBeOverride"))
}

void ADefaultEquipeActor::ThrowObject(ACharacter* Character)
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	FVector CharacterForwardVector = Character->GetActorForwardVector();

	CharacterForwardVector.Z = 0;
	
	SetActorLocation(Character->GetActorLocation() + CharacterForwardVector * 150.0f);

	SetActorEnableCollision(true);
	
}

void ADefaultEquipeActor::TakeObject(ACharacter* Character)
{
	FAttachmentTransformRules AttachmentRules(
			EAttachmentRule::KeepWorld,
			EAttachmentRule::KeepRelative,     
			EAttachmentRule::KeepRelative,  
			true                          
		);
	
	SetActorLocation(Character->GetMesh()->GetSocketLocation(AttachSocketName));
	AttachToComponent(Character->GetMesh(), AttachmentRules, AttachSocketName);
	SetActorEnableCollision(false);

}

void ADefaultEquipeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

