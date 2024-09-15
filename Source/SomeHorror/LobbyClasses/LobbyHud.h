// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LobbyCharacter.h"
#include "LobbyInterface.h"
#include "GameFramework/HUD.h"
#include "LobbyHud.generated.h"


UCLASS()
class SOMEHORROR_API ALobbyHud : public AHUD
{
	GENERATED_BODY()

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;


private:
	UPROPERTY()
	ALobbyCharacter* LastHighLightCharacter;

	UPROPERTY()
	ALobbyCharacter* HudOwner;
	
	UPROPERTY()
	ALobbyCharacter* CurrentHoveredCharacter;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULobbyInterface> LobbyInterfaceClass;

	UPROPERTY()
	UUserWidget* LobbyInterface;

public:
	UFUNCTION()
	void OnPlayerMouseInteract();
	
};
