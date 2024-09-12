// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "PlayerNameWidget.generated.h"

/**
 * 
 */
UCLASS()
class SOMEHORROR_API UPlayerNameWidget : public UUserWidget
{
	GENERATED_BODY()
	

	virtual void NativeConstruct() override;

public:
	void SetPlayerNameText(FName Name);

protected:
	UPROPERTY(BlueprintReadWrite , meta = (BindWidget))
	UTextBlock* PlayerNameText;
	
	
};
