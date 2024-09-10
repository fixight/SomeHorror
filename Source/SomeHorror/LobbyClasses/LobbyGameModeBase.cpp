// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameModeBase.h"
#include "Camera/CameraActor.h"
#include "Engine/Engine.h"
#include "SomeHorror/SomeHorrorPlayerController.h"
#include "SomeHorror/GameStates/LobbyLoaderGameState.h"
#include "SomeHorror/Loaders/AssetLoader.h"

void ALobbyGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	

	ASomeHorrorPlayerController* MyPlayerController = Cast<ASomeHorrorPlayerController>(NewPlayer);

	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundCameras);
	
	FName RandomRowName = GetRandomRowName(AnimationDataTable);
	
	MyPlayerController->PossesLobbyCamera();

	ALobbyCharacter* LobbyCharacter = Cast<ALobbyCharacter>(MyPlayerController->GetPawn());

	
	FName AName;
	FName MName;

	ALobbyLoaderGameState* LoaderGameState = GetGameState<ALobbyLoaderGameState>();

	if(IsHost(NewPlayer))
	{
		AName = "ZombieIdle";
		MName = "Enemy";
	}

	else
	{
		AName = RandomRowName;
		MName = "Amanda";
	}
	
	
	LoaderGameState->InitLobbyCharacter(MName , MeshesDataTable , AName , AnimationDataTable , LobbyCharacter);
	

	
	
	
}

const bool ALobbyGameModeBase::IsHost(APlayerController* Controller)
{
	if (!IsValid(Controller))
	{
		return false;
	}

	return (Controller->HasAuthority() && Controller->IsLocalPlayerController());
}



void ALobbyGameModeBase::LoadAnimationAllClient(FName AnimationName , ASomeHorrorPlayerController* LoadInstigator)
{
	
	UAssetLoader::AsyncLoadAsset<UAnimationAsset , FAnimationTableRow>(AnimationDataTable , AnimationName, [LoadInstigator](UAnimationAsset* AnimationAsset)
	{
		LoadInstigator->SetLobbyIdleAnimation(AnimationAsset);
	});
}

UAnimationAsset* ALobbyGameModeBase::GetRandomAnimAsset()
{
	const int RandomIndex = FMath::RandRange(0 , AnimAssets.Num() - 1);

	if(AnimAssets[RandomIndex]) return AnimAssets[RandomIndex];

	return nullptr;
}

FName ALobbyGameModeBase::GetRandomRowName(UDataTable* DataTable)
{
	if (!DataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable is null"));
		return NAME_None;
	}
	
	TArray<FName> RowNames = DataTable->GetRowNames();

	RowNames.Remove("ZombieIdle");
	
	if (RowNames.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable is empty"));
		return NAME_None;
	}
	
	int32 RandomIndex = FMath::RandRange(0, RowNames.Num() - 1);
	return RowNames[RandomIndex];
}

void ALobbyGameModeBase::LoadMeshesOnAllMachines_Implementation()
{
	FName RowName = FName("Amanda");
 
	UAssetLoader::AsyncLoadAsset<USkeletalMesh , FMeshTableRow>(MeshesDataTable , RowName, [](USkeletalMesh* SkeletalMesh)
	{
		
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

void ALobbyGameModeBase::BeginPlay()
{
	Super::BeginPlay();


}
