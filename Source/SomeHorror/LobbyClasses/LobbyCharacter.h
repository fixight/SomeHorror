// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "PlayerNameWidget.h"
#include "Components/SpotLightComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "SomeHorror/GameInstances/LobbyTransferGameInstance.h"
#include "LobbyCharacter.generated.h"

DECLARE_DELEGATE(FOnInteract)

class UInputMappingContext;
UCLASS()
class SOMEHORROR_API ALobbyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALobbyCharacter();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(ReplicatedUsing = OnRep_LobbyAnimation)
	UAnimationAsset* LobbyAnimation;

	UPROPERTY(ReplicatedUsing = OnRep_SkeletalMesh)
	USkeletalMesh* LobbySkeletalMesh;

	void SetSkeletalMesh(USkeletalMesh* LobbyMesh);

	void SetLobbyAnimation(UAnimationAsset* AnimationAsset);

	void SetNameToWidget(FName Name);

	UFUNCTION(Server , Reliable)
	void SetNameToWidgetOnServer(FName Name);

	UFUNCTION(Server , Reliable)
	void SetSkeletalMeshOnServer(USkeletalMesh* NewMesh);

	UFUNCTION(Server , Reliable)
	void SetLobbyAnimationOnServer(UAnimationAsset* AnimationAsset);

	
	UFUNCTION()
	void OnRep_LobbyAnimation();

	UFUNCTION()
	void OnRep_SkeletalMesh();

	UFUNCTION()
	void OnRep_PlayerName();

protected:
	UPROPERTY(EditDefaultsOnly)
	UWidgetComponent* PlayerNameWidgetComponent;

	UPROPERTY()
	UPlayerNameWidget* PlayerNameWidget;

	UPROPERTY()
	ULobbyTransferGameInstance* LocalGameInstance;

	UPROPERTY(ReplicatedUsing = OnRep_PlayerName)
	FName PlayerName;

	UPROPERTY(EditDefaultsOnly)
	USpotLightComponent* HighLightComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* RightClickAction;

public:
	void SetHighLightCharacter(const bool IsHightLight);


protected:
	void RightClick();

public:
	FOnInteract OnInteract;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};


