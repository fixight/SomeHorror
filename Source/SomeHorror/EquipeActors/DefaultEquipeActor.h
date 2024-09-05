// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "SomeHorror/Interfaces/EquiptableInterface.h"
#include "DefaultEquipeActor.generated.h"

UCLASS(Abstract)
class SOMEHORROR_API ADefaultEquipeActor : public AActor , public IEquiptableInterface
{
	GENERATED_BODY()
	
public:	
	ADefaultEquipeActor();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly)
	FName AttachSocketName;

public:
	virtual void Interact() override;

	virtual void ThrowObject(ACharacter* Character) override;

	virtual void TakeObject(ACharacter* Character) override;

public:	
	virtual void Tick(float DeltaTime) override;

};
