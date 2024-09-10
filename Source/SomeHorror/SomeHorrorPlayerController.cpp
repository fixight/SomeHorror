// Copyright Epic Games, Inc. All Rights Reserved.


#include "SomeHorrorPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/Engine.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"


ASomeHorrorPlayerController::ASomeHorrorPlayerController()
{
	bReplicates = true;
	bAutoManageActiveCameraTarget = false;
}

void ASomeHorrorPlayerController::PossesLobbyCamera()
{
	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundCameras);

	if (FoundCameras.Num() > 0)
	{
		ACameraActor* LobbyCamera = Cast<ACameraActor>(FoundCameras[0]);
		if (LobbyCamera)
		{
			SetViewTarget(LobbyCamera);
		}
	}
}

void ASomeHorrorPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

void ASomeHorrorPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	
	
	
}


void ASomeHorrorPlayerController::SendRequstToServer_Implementation()
{
	SetLobbyIdleAnimation(nullptr);
}

void ASomeHorrorPlayerController::PlayAnimation()
{
	

	if (ACharacter* Charr = Cast<ACharacter>(this->GetPawn()))
	{
		// Получаем SkeletalMeshComponent
		USkeletalMeshComponent* SkeletalMesh = Charr->GetMesh();
        
		if (SkeletalMesh)
		{
			
			GEngine->AddOnScreenDebugMessage(-1 , 3.0f , FColor::Red , "PlayAnimation");
			SkeletalMesh->PlayAnimation(LobbyIdleAnimation, true);
		}
	}
}

void ASomeHorrorPlayerController::SetLobbyIdleAnimation(UAnimationAsset* AnimSequence)
{
	//if(AnimSequence)
		//LobbyIdleAnimation = AnimSequence;
	
}

void ASomeHorrorPlayerController::BeginPlay()
{
	Super::BeginPlay();
	


	
}


void ASomeHorrorPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


}
