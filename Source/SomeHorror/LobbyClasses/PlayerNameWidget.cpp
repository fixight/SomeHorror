// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerNameWidget.h"


void UPlayerNameWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UPlayerNameWidget::SetPlayerNameText(FName Name)
{
	if(PlayerNameText)
	{
		PlayerNameText->SetText(FText::FromString(Name.ToString()));
	}
}
