// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "LobbyHud.h"
#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ALobbyCharacter::ALobbyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	PlayerNameWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayerName"));
	PlayerNameWidgetComponent->SetupAttachment(GetRootComponent());

	HighLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("HLComponent"));
	HighLightComponent->SetupAttachment(GetRootComponent());

	HighLightComponent->SetVisibility(false);
	
}

void ALobbyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyCharacter , LobbyAnimation)
	DOREPLIFETIME(ALobbyCharacter , LobbySkeletalMesh)
	DOREPLIFETIME(ALobbyCharacter , PlayerName)
}

void ALobbyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		// Получаем Enhanced Input Subsystem
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (Subsystem)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	UUserWidget* UserWidget = PlayerNameWidgetComponent->GetUserWidgetObject();
	if(UserWidget)
	{
		PlayerNameWidget = Cast<UPlayerNameWidget>(UserWidget);
	};
}

void ALobbyCharacter::SetSkeletalMesh(USkeletalMesh* LobbyMesh)
{
	if(HasAuthority())
	{
		GetMesh()->SetSkeletalMesh(LobbyMesh , false);
		LobbySkeletalMesh = LobbyMesh;
	}

	else
	{
		SetSkeletalMeshOnServer(LobbyMesh);
	}
}

void ALobbyCharacter::SetLobbyAnimation(UAnimationAsset* AnimationAsset)
{
	if(HasAuthority())
	{
		LobbyAnimation = AnimationAsset;
		GetMesh()->PlayAnimation(AnimationAsset , true);
	}

	else
	{
		SetLobbyAnimationOnServer(AnimationAsset);
	}
}

void ALobbyCharacter::SetSkeletalMeshOnServer_Implementation(USkeletalMesh* NewMesh)
{
	LobbySkeletalMesh = NewMesh;
}

void ALobbyCharacter::SetLobbyAnimationOnServer_Implementation(UAnimationAsset* AnimationAsset)
{
	LobbyAnimation = AnimationAsset;
}

void ALobbyCharacter::OnRep_LobbyAnimation()
{
	GetMesh()->PlayAnimation(LobbyAnimation , true);
	
}

void ALobbyCharacter::OnRep_SkeletalMesh()
{
	GetMesh()->SetSkeletalMesh(LobbySkeletalMesh , false);

	OnRep_LobbyAnimation();
}

void ALobbyCharacter::OnRep_PlayerName()
{
	if(PlayerNameWidget)
	{
		GEngine->AddOnScreenDebugMessage(-1 , 4.0f , FColor::Green , "TextRepl");
		PlayerNameWidget->SetPlayerNameText(PlayerName);
	}
}

void ALobbyCharacter::SetNameToWidget(FName Name)
{
	if(HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "SetNameOnServer");
		if(PlayerNameWidget)
		{
			PlayerName = Name;
			PlayerNameWidget->SetPlayerNameText(Name);
		}
	}

	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "SetNameOnClient");
		SetNameToWidgetOnServer(Name);
	}
}

void ALobbyCharacter::SetNameToWidgetOnServer_Implementation(FName Name)
{
	
	PlayerName = Name;
}

void ALobbyCharacter::SetHighLightCharacter(const bool IsHightLight)
{
	HighLightComponent->SetVisibility(IsHightLight);
}

void ALobbyCharacter::RightClick()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "RightClick");

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	
	Cast<ALobbyHud>(PlayerController->GetHUD())->OnPlayerMouseInteract();
}

void ALobbyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	//if(LobbyAnimation) OnRep_LobbyAnimation();
}

void ALobbyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(RightClickAction , ETriggerEvent::Started , this , &ALobbyCharacter::RightClick);
	}
}


