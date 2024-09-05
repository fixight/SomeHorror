// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefaultEquipeActor.h"
#include "Components/SpotLightComponent.h"
#include "FlashLightActor.generated.h"

/**
 * 
 */
UCLASS()
class SOMEHORROR_API AFlashLightActor : public ADefaultEquipeActor
{
	GENERATED_BODY()

	AFlashLightActor();

	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	USpotLightComponent* SpotLightComponent;

	virtual void Interact() override;

	virtual void TakeObject(ACharacter* Character) override;
	
};
