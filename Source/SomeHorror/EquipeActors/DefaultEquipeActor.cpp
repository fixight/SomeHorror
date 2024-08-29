// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipeActors/DefaultEquipeActor.h"

// Sets default values
ADefaultEquipeActor::ADefaultEquipeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADefaultEquipeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultEquipeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

