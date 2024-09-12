// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/GameState.h"
#include "SomeHorror/LobbyClasses/LobbyCharacter.h"
#include "LobbyLoaderGameState.generated.h"

/**
 * 
 */
UCLASS()
class SOMEHORROR_API ALobbyLoaderGameState : public AGameStateBase
{
	GENERATED_BODY()

	ALobbyLoaderGameState();

public:
	UFUNCTION(NetMulticast , Reliable , BlueprintCallable)
	void StartLoadAsset(FName AssetName , UDataTable* DataTable , ALobbyCharacter* LoadInstigator);

	UFUNCTION(NetMulticast , Reliable)
	void LoadAndSetSkeletalMesh(FName AssetName , UDataTable* DataTable , ALobbyCharacter* LoadInstigator);

	UFUNCTION(NetMulticast , Reliable)
	void InitLobbyCharacter(FName SkeletalMeshName , UDataTable* MeshDataTable , FName AnimationName , UDataTable* AnimationDataTable , ALobbyCharacter* LobbyCharacter);

	UFUNCTION(NetMulticast , Reliable)
	void SetNameOnWidgets(FName Name , ALobbyCharacter* LobbyCharacter);

	
	
};


