// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/PlayerController.h"
#include "SomeHorrorPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class SOMEHORROR_API ASomeHorrorPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

protected:
	

	ASomeHorrorPlayerController();

public:

	

	
	void PossesLobbyCamera();

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(Server , Reliable)
	void SendRequstToServer();

	void PlayAnimation();
	
	void SetLobbyIdleAnimation(UAnimationAsset* AnimSequence);

protected:

	virtual void BeginPlay() override;



	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


public:
	UPROPERTY()
	UAnimationAsset* LobbyIdleAnimation;
	
};
