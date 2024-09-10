// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LobbyCharacter.generated.h"

UCLASS()
class SOMEHORROR_API ALobbyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALobbyCharacter();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(ReplicatedUsing = OnRep_LobbyAnimation)
	UAnimationAsset* LobbyAnimation;

	UPROPERTY(ReplicatedUsing = OnRep_SkeletalMesh)
	USkeletalMesh* LobbySkeletalMesh;

	void SetSkeletalMesh(USkeletalMesh* LobbyMesh);

	UFUNCTION(Server , Reliable)
	void SetSkeletalMeshOnServer(USkeletalMesh* NewMesh);

	UFUNCTION(NetMulticast , Reliable)
	void SetSkeletalMeshMulticast(USkeletalMesh* NewMesh);

	void SetLobbyAnimation(UAnimationAsset* AnimationAsset);

	UFUNCTION(Server , Reliable)
	void SetLobbyAnimationOnServer(UAnimationAsset* AnimationAsset);

	
	UFUNCTION()
	void OnRep_LobbyAnimation();

	UFUNCTION()
	void OnRep_SkeletalMesh();

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
