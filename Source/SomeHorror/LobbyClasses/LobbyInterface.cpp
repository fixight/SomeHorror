// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyInterface.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/KismetSystemLibrary.h"

void ULobbyInterface::NativeConstruct()
{
	Super::NativeConstruct();
	
	
}

void ULobbyInterface::Disconect()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			PlayerController->ClientTravel("/Game/Maps/EXIT", ETravelType::TRAVEL_Absolute);
			
		}
	}
}




