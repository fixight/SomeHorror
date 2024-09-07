// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LobbyCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameModeBase.generated.h"

USTRUCT(Blueprintable)
struct FMeshTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MeshName;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TAssetPtr<USkeletalMesh> Asset;
 
	FMeshTableRow() :
		MeshName(TEXT("")),
		Asset(nullptr)
	{
	}
};

UCLASS()
class SOMEHORROR_API ALobbyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	ALobbyGameModeBase();

protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	const bool IsHost(APlayerController* PlayerController);

protected:
	//void LoadMeshOnAllMachin

protected:
	//UPROPERTY(EditDefaultsOnly)
	//TSubclassOf<ALobbyCharacter> LobbyCharacter;

	UFUNCTION(Client , Reliable)
	void LoadMeshesOnAllMachines();

	UFUNCTION(Client , Reliable)
	void ChangeView(APlayerController* PlayerController);

protected:
	UPROPERTY(EditDefaultsOnly)
	UDataTable* MeshesDataTable;
};


