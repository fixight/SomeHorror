// Fill out your copyright notice in the Description page of Project Settings.


#include "FlashLightActor.h"

#include "Components/SkeletalMeshComponent.h"
#include "Engine/Engine.h"
#include "SomeHorror/Characters/PlayerCharacter.h"

AFlashLightActor::AFlashLightActor()
{
	SpotLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("Light"));
	SpotLightComponent->SetupAttachment(Cast<USceneComponent>(MeshComponent));

}

void AFlashLightActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(!GetOwner())
		return;
	
}

void AFlashLightActor::Interact()
{
	SetActorTickEnabled(true);
	SpotLightComponent->ToggleVisibility(false);
	
	GEngine->AddOnScreenDebugMessage(-1 , 3.0f , FColor::Red , "InteractFlashlight");
}

void AFlashLightActor::TakeObject(ACharacter* Character)
{
	if(Character->IsLocallyControlled() && Character)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Character);

		AttachToComponent(PlayerCharacter->GetCameraComponent() , FAttachmentTransformRules::KeepWorldTransform);

		SetActorLocation(PlayerCharacter->GetMesh()->GetSocketLocation(AttachSocketName));

		SetActorRotation(PlayerCharacter->GetCameraComponent()->GetComponentRotation());
		
	}
	else
	{
		Super::TakeObject(Character);
	}
	
}
