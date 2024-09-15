// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyHud.h"


#include "DrawDebugHelpers.h"
#include "LobbyCharacter.h"
#include "LobbyGameModeBase.h"
#include "Engine/Engine.h"
#include "Engine/HitResult.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

void ALobbyHud::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
    
	 APlayerController* PC = Cast<APlayerController>(GetOwner());
    if (!PC) return;
    
    float MouseX, MouseY;
    PC->GetMousePosition(MouseX, MouseY);

    FVector WorldLocation, WorldDirection;
    if (PC->DeprojectScreenPositionToWorld(MouseX, MouseY, WorldLocation, WorldDirection))
    {
        FVector Start = PC->PlayerCameraManager->GetCameraLocation();
        FVector End = Start + (WorldDirection * 10000.0f);

        FHitResult HitResult;

        FCollisionQueryParams Params;
        Params.AddIgnoredActor(this);
        Params.bTraceComplex = true;

        bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);
        
        if (bHit)
        {
            ALobbyCharacter* HitCharacter = Cast<ALobbyCharacter>(HitResult.GetActor());
            if (HitCharacter)
            {
                if (LastHighLightCharacter && LastHighLightCharacter != HitCharacter)
                {
                    LastHighLightCharacter->SetHighLightCharacter(false);
                }
                
                HitCharacter->SetHighLightCharacter(true);
                LastHighLightCharacter = HitCharacter;
                
                CurrentHoveredCharacter = HitCharacter;
                
            }
            else
            {
                if (LastHighLightCharacter)
                {
                    LastHighLightCharacter->SetHighLightCharacter(false); 
                    LastHighLightCharacter = nullptr;
                }
                
                CurrentHoveredCharacter = nullptr;
            }
        }
        else
        {
            DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 2.0f);

            if (LastHighLightCharacter)
            {
                LastHighLightCharacter->SetHighLightCharacter(false);
                LastHighLightCharacter = nullptr;
            }
            
            CurrentHoveredCharacter = nullptr;
            
        }
    }
    
}

void ALobbyHud::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PC = Cast<APlayerController>(GetOwner());
    PC->SetShowMouseCursor(true);

   
    if (LobbyInterfaceClass)
    {
        LobbyInterface = CreateWidget<UUserWidget>(GetWorld(), LobbyInterfaceClass);
            
        if (LobbyInterface)
        {
            LobbyInterface->AddToViewport();

        }
    }
    

	

    
}

void ALobbyHud::OnPlayerMouseInteract()
{
    if(Owner->HasAuthority() && CurrentHoveredCharacter)
    {
        APlayerController* PC = Cast<APlayerController>(GetOwner());
        Cast<ALobbyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->ChangeEnemy(CurrentHoveredCharacter);
    }
}
