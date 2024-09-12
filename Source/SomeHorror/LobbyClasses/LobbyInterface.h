// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "LobbyInterface.generated.h"

/**
 * 
 */
UCLASS()
class SOMEHORROR_API ULobbyInterface : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void Disconect();


protected:
	UPROPERTY(EditDefaultsOnly , meta=(BindWidget))
	UButton* ExitButton;

	
};
