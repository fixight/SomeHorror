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
		CurrentEnemy = LobbyCharacter;
		AName = "ZombieIdle";
		MName = "Enemy";
	}

	else
	{
		AName = RandomRowName;
		MName = GetRandomRowName(MeshesDataTable);
	}
	
	
	LoaderGameState->InitLobbyCharacter(MName , MeshesDataTable , AName , AnimationDataTable , LobbyCharacter);
	FName PlayerName = FName(*MyPlayerController->GetName());
	LoaderGameState->SetNameOnWidgets(PlayerName , LobbyCharacter);
	

	
	
	
}

const bool ALobbyGameModeBase::IsHost(APlayerController* Controller)
{
	if (!IsValid(Controller))
	{
		return false;
	}

	return (Controller->HasAuthority() && Controller->IsLocalPlayerController());
}

void ALobbyGameModeBase::ChangeEnemy(ALobbyCharacter* NewEnemy)
{
	FName AName = "ZombieIdle";
	FName MName = "Enemy";
	LobbyLoaderGameState->InitLobbyCharacter(GetRandomRowName(MeshesDataTable) , MeshesDataTable , GetRandomRowName(AnimationDataTable) , AnimationDataTable , CurrentEnemy);
	LobbyLoaderGameState->InitLobbyCharacter(MName , MeshesDataTable , AName , AnimationDataTable , NewEnemy);
	CurrentEnemy = NewEnemy;
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
	RowNames.Remove("Enemy");
	
	if (RowNames.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable is empty"));
		return NAME_None;
	}
	
	int32 RandomIndex = FMath::RandRange(0, RowNames.Num() - 1);
	return RowNames[RandomIndex];
}




ALobbyGameModeBase::ALobbyGameModeBase()
{
	
}

void ALobbyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	LobbyLoaderGameState = GetGameState<ALobbyLoaderGameState>();


}
