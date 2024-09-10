// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimationAsset.h"
#include "Engine/AssetManager.h"
#include "Engine/DataTable.h"
#include "Engine/StreamableManager.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/NoExportTypes.h"
#include "AssetLoader.generated.h"


USTRUCT(Blueprintable)
struct FAnimationTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AnimationName;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TAssetPtr<UAnimationAsset> Asset;
 
	FAnimationTableRow() :
		AnimationName(TEXT("")),
		Asset(nullptr)
	{
	}
};

UCLASS()
class SOMEHORROR_API UAssetLoader : public UObject
{
	GENERATED_BODY()


public:
	
	template <typename T , typename FDataTable>
	static	void AsyncLoadAsset(UDataTable* DataTable , FName& Name  , TFunction<void(T*)> OnLoadedCallback)
	{

		FDataTable* TableRow = DataTable->FindRow<FDataTable>(Name , TEXT(""));

		TAssetPtr<T> LoadedSkeletalMesh =  TableRow->Asset; //It can be use Only for simple Data Table 

		
		if (LoadedSkeletalMesh.IsValid() == false)
		{
			FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
			
			Streamable.RequestAsyncLoad(LoadedSkeletalMesh.ToSoftObjectPath(), [LoadedSkeletalMesh, OnLoadedCallback]()
			{
				if (LoadedSkeletalMesh.IsValid())
				{
					T* LoadedAsset = LoadedSkeletalMesh.Get();
					OnLoadedCallback(LoadedAsset);
				}
			});
		}
		else
		{
			OnLoadedCallback(LoadedSkeletalMesh.Get());
		}
	}

	
};


