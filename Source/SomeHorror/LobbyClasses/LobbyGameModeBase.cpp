// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameModeBase.h"
#include "Camera/CameraActor.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "Rendering/RenderCommandPipes.h"
#include "SomeHorror/SomeHorrorPlayerController.h"
#include "SomeHorror/Loaders/AssetLoader.h"

void ALobbyGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ASomeHorrorPlayerController* MyPlayerController = Cast<ASomeHorrorPlayerController>(NewPlayer);

	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundCameras);
	
	MyPlayerController->PossesLobbyCamera();

	
	LoadMeshesOnAllMachines();
	//GEngine->AddOnScreenDebugMessage(-1 , 4.0f , FColor::Red , LoadedMesh->GetName());
			
	
}

const bool ALobbyGameModeBase::IsHost(APlayerController* Controller)
{
	if (!IsValid(Controller))
	{
		return false;
	}

	return (Controller->HasAuthority() && Controller->IsLocalPlayerController());
}

void ALobbyGameModeBase::LoadMeshesOnAllMachines_Implementation()
{
	FName RowName = FName("Amanda");
 
	UAssetLoader::AsyncLoadAsset<USkeletalMesh , FMeshTableRow>(MeshesDataTable , RowName, [](USkeletalMesh* SkeletalMesh)
	{
		GEngine->AddOnScreenDebugMessage(-1 , 4.0f , FColor::Red , SkeletalMesh->GetName());
	});
}

void ALobbyGameModeBase::ChangeView_Implementation(APlayerController* Controller)
{
	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraActors);

	ACameraActor* LobbyCamera = Cast<ACameraActor>(CameraActors[0]);

	Controller->SetViewTarget(LobbyCamera);
}


ALobbyGameModeBase::ALobbyGameModeBase()
{

	//DefaultPawnClass = LobbyCharacter;
}
