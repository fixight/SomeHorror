// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipComponent.h"

UEquipComponent::UEquipComponent()
{
	PrimaryComponentTick.bCanEverTick = true;


}



void UEquipComponent::BeginPlay()
{
	Super::BeginPlay();


	
}


void UEquipComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

