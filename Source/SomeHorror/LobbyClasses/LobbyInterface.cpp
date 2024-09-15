// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyInterface.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SomeHorror/GameInstances/LobbyTransferGameInstance.h"

void ULobbyInterface::NativeConstruct()
{
	Super::NativeConstruct();

	ExitButton->OnClicked.AddDynamic(this , &ULobbyInterface::Disconect);
	
}

void ULobbyInterface::Disconect()
{
	FName Name = Cast<ULobbyTransferGameInstance>(GetOwningPlayer()->GetGameInstance())->PlayerMeshInGame;
	
}




