// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyLoaderGameState.h"

#include "GameFramework/Character.h"
#include "SomeHorror/Loaders/AssetLoader.h"
#include "SomeHorror/LobbyClasses/LobbyGameModeBase.h"

void ALobbyLoaderGameState::StartLoadAsset_Implementation(FName AssetName, UDataTable* DataTable , ALobbyCharacter* LoadInstigator)
{
	if (!LoadInstigator)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "LobbyCharacter is nullptr");
		return;
	}

	UAssetLoader::AsyncLoadAsset<UAnimationAsset , FAnimationTableRow>(DataTable , AssetName, [LoadInstigator , this](UAnimationAsset* AnimationAsset)
	{

		
		if(HasAuthority() && AnimationAsset)
		{
			LoadInstigator->GetMesh()->PlayAnimation(AnimationAsset , true);
			LoadInstigator->SetLobbyAnimation(AnimationAsset);
			
		}
		else
		{
			
			if(!LoadInstigator && !AnimationAsset) return;
			LoadInstigator->SetLobbyAnimation(AnimationAsset);
			
		}
		
	});

	
}

ALobbyLoaderGameState::ALobbyLoaderGameState()
{
	bReplicates = true;
}




void ALobbyLoaderGameState::SetNameOnWidgets_Implementation(FName Name, ALobbyCharacter* LobbyCharacter)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Name.ToString());
	if (!LobbyCharacter)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "LobbyCharacter is nullptr");
		return;
	}
	if(HasAuthority())
	{
		LobbyCharacter->SetNameToWidget(Name);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "SetNameOnServer");
	}

	else
	{
		LobbyCharacter->SetNameToWidget(Name);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "SetNameOnClient");
	}
}

void ALobbyLoaderGameState::InitLobbyCharacter_Implementation(FName SkeletalMeshName, UDataTable* MeshDataTable,
                                                              FName AnimationName, UDataTable* AnimationDataTable, ALobbyCharacter* LobbyCharacter)
{
	if (!LobbyCharacter)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "LobbyCharacter is nullptr");
		return;
	}
	UAssetLoader::AsyncLoadAsset<USkeletalMesh, FMeshTableRow>(MeshDataTable, SkeletalMeshName, [LobbyCharacter, this, AnimationDataTable, AnimationName](USkeletalMesh* SkeletalMesh)mutable 
{
	if (HasAuthority() && SkeletalMesh)
	{
		LobbyCharacter->SetSkeletalMesh(SkeletalMesh);
	}
	else
	{
		if (!LobbyCharacter && !SkeletalMesh) return;
		LobbyCharacter->SetSkeletalMesh(SkeletalMesh);
	}

	UAssetLoader::AsyncLoadAsset<UAnimationAsset, FAnimationTableRow>(AnimationDataTable, AnimationName, [LobbyCharacter, this , SkeletalMesh](UAnimationAsset* AnimationAsset)
	{
		if(!AnimationAsset) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "AnimAsset is nullptr");
		if (HasAuthority() && AnimationAsset)
		{
			
			//LobbyCharacter->GetMesh()->PlayAnimation(AnimationAsset, true);
			LobbyCharacter->SetLobbyAnimation(AnimationAsset);
		}
		else
		{
			if (!LobbyCharacter && !AnimationAsset) return;
			//LobbyCharacter->SetSkeletalMesh(SkeletalMesh);
			LobbyCharacter->SetLobbyAnimation(AnimationAsset);
		}
	});
});

	
}

void ALobbyLoaderGameState::LoadAndSetSkeletalMesh_Implementation(FName AssetName, UDataTable* DataTable, ALobbyCharacter* LoadInstigator)
{
	if (!LoadInstigator)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "LobbyCharacter is nullptr");
		return;
	}

	UAssetLoader::AsyncLoadAsset<USkeletalMesh , FMeshTableRow>(DataTable , AssetName, [LoadInstigator , this](USkeletalMesh* SkeletalMesh)
	{

		
		if(HasAuthority() && SkeletalMesh)
		{
			LoadInstigator->GetMesh()->SetSkeletalMeshAsset(SkeletalMesh);
			LoadInstigator->SetSkeletalMesh(SkeletalMesh);
			
			
		}
		else
		{
			if(!LoadInstigator && !SkeletalMesh) return;
			LoadInstigator->SetSkeletalMesh(SkeletalMesh);
			
		}
		
	});
}
