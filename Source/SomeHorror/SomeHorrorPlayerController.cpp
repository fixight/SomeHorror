// Copyright Epic Games, Inc. All Rights Reserved.


#include "SomeHorrorPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraActor.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"


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

	//SetActorTickInterval(3.0f);
	

	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundCameras);

	if (FoundCameras.Num() > 0)
	{
		ACameraActor* LobbyCamera = Cast<ACameraActor>(FoundCameras[0]);
		if (LobbyCamera)
		{
			//SetViewTarget(LobbyCamera);
		}
	}
	
}

void ASomeHorrorPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundCameras);

	if (FoundCameras.Num() > 0)
	{
		ACameraActor* LobbyCamera = Cast<ACameraActor>(FoundCameras[0]);
		if (LobbyCamera)
		{
			GEngine->AddOnScreenDebugMessage(-1 , 4.0f , FColor::Red , "Valid");
			//SetViewTarget(LobbyCamera);
		}
	}
	
}

void ASomeHorrorPlayerController::Client_SetLobbyCamera(ACameraActor* LobbyCamera)
{
	if (LobbyCamera)
	{
		SetViewTarget(LobbyCamera);
	}
}

void ASomeHorrorPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//SetActorTickEnabled(false);

	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundCameras);

	if (FoundCameras.Num() > 0)
	{
		ACameraActor* LobbyCamera = Cast<ACameraActor>(FoundCameras[0]);
		if (LobbyCamera)
		{
			GEngine->AddOnScreenDebugMessage(-1 , 4.0f , FColor::Red , "Valid");
			//SetViewTarget(LobbyCamera);
		}
	}
	
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	
}
