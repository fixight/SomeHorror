// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyCharacter.h"

#include "Net/UnrealNetwork.h"

// Sets default values
ALobbyCharacter::ALobbyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
}

void ALobbyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyCharacter , LobbyAnimation)
	DOREPLIFETIME(ALobbyCharacter , LobbySkeletalMesh)
}

void ALobbyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALobbyCharacter::SetSkeletalMesh(USkeletalMesh* NewMesh)
{
	if(HasAuthority())
	{
		LobbySkeletalMesh = NewMesh;
		SetSkeletalMeshMulticast(NewMesh);
	}
	else
	{
		SetSkeletalMeshOnServer(NewMesh);
	}
}

void ALobbyCharacter::SetSkeletalMeshOnServer_Implementation(USkeletalMesh* NewMesh)
{
	LobbySkeletalMesh = NewMesh;
	SetSkeletalMeshMulticast(NewMesh);
}

void ALobbyCharacter::SetSkeletalMeshMulticast_Implementation(USkeletalMesh* NewMesh)
{
	GetMesh()->SetSkeletalMeshAsset(NewMesh);
}

void ALobbyCharacter::SetLobbyAnimation(UAnimationAsset* AnimationAsset)
{
	if(HasAuthority())
	{
		LobbyAnimation = AnimationAsset;
	}

	else
	{
		SetLobbyAnimationOnServer(AnimationAsset);
	}
}

void ALobbyCharacter::SetLobbyAnimationOnServer_Implementation(UAnimationAsset* AnimationAsset)
{
	LobbyAnimation = AnimationAsset;
}

void ALobbyCharacter::OnRep_LobbyAnimation()
{
	GEngine->AddOnScreenDebugMessage(-1 , 3.0f , FColor::Red , "Replicate");
	GetMesh()->PlayAnimation(LobbyAnimation , true);
}

void ALobbyCharacter::OnRep_SkeletalMesh()
{
	GEngine->AddOnScreenDebugMessage(-1 , 3.0f , FColor::Red , "MeshReplicate");
	GetMesh()->SetSkeletalMesh(LobbySkeletalMesh);
}

void ALobbyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ALobbyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

