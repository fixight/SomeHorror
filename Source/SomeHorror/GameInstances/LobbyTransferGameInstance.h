// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/SkeletalMesh.h"
#include "LobbyTransferGameInstance.generated.h"


UCLASS()
class SOMEHORROR_API ULobbyTransferGameInstance : public UGameInstance
{
	GENERATED_BODY()

	ULobbyTransferGameInstance();

	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;

public:
	UPROPERTY()
	FName PlayerMeshInGame;

public:
	void SetPlayerMeshInGame(FName Mesh)
	{
		GEngine->AddOnScreenDebugMessage(-1 , 3.0f , FColor::Blue , Mesh.ToString());
		
		PlayerMeshInGame = Mesh;
	};
	
};
