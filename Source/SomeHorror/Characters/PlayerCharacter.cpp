
#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"


constexpr float InteractDistance = 250.0f;

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment( Cast<USceneComponent>(GetCapsuleComponent()));

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraCompoent"));
	PlayerCamera->SetupAttachment(StaticMeshComponent);
	

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 250.0f;
	
	
	
}


void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//GEngine->AddOnScreenDebugMessage(-1 , 10.0f , FColor::Red , FString::FromInt(StaticCast<int32>(PlayerMovementState)));

	

	//if(GetVelocity().IsNearlyZero() && PlayerState == EPlayerState::EPS_Alive) PlayerMovementState = EPlayerMovementState::EPMS_Default;

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(RunAction , ETriggerEvent::Started , this , &APlayerCharacter::PlayerStartRunning);
		EnhancedInputComponent->BindAction(RunAction , ETriggerEvent::Completed , this , &APlayerCharacter::PlayerStopRunning);
		EnhancedInputComponent->BindAction(CrouchAction , ETriggerEvent::Started , this , &APlayerCharacter::PlayerCrouch);
		EnhancedInputComponent->BindAction(CrouchAction , ETriggerEvent::Completed , this , &APlayerCharacter::PlayerStopCrouch);
	}
	

}

void APlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerCharacter, MaxSpeed);
	DOREPLIFETIME(APlayerCharacter , PlayerMovementState)
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	if(PlayerState == EPlayerState::EPS_Alive)
	{
		
	}

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::EquipButtonPressed()
{
	if(PlayerState != EPlayerState::EPS_Alive) return;

	FHitResult HitResult;
	const FVector CameraLocation = PlayerCamera->GetComponentLocation();

	GetWorld()->LineTraceSingleByChannel(HitResult , CameraLocation , CameraLocation + PlayerCamera->GetForwardVector() * InteractDistance , ECC_Visibility);

	if(!HitResult.bBlockingHit) return;
}

void APlayerCharacter::PlayerKnowDown()
{
	PlayerState = EPlayerState::EPS_KnowDown;
	PlayerMovementState = EPlayerMovementState::EPMS_Lie;

	ChangePlayerMovementState_Server(EPlayerMovementState::EPMS_Lie);

	GetCharacterMovement()->MaxWalkSpeed = 150.0f;

	ChangeMaxSpeed_Server(150.0f);
}

void APlayerCharacter::PlayerRecovered()
{
	if(PlayerState != EPlayerState::EPS_KnowDown) return;

	PlayerState = EPlayerState::EPS_Alive;
	PlayerMovementState = EPlayerMovementState::EPMS_Default;
}

void APlayerCharacter::PlayerCrouch()
{
	if(PlayerState != EPlayerState::EPS_Alive || PlayerState == EPlayerState::EPS_KnowDown) return;

	if(CanCrouch())
	{
		Crouch();
		PlayerMovementState = EPlayerMovementState::EPMS_Crouch;
		ChangePlayerMovementState_Server(PlayerMovementState);
	}

	
}

void APlayerCharacter::PlayerStopCrouch()
{
	if(PlayerState != EPlayerState::EPS_Alive || PlayerState == EPlayerState::EPS_KnowDown) return;

	UnCrouch();
	PlayerMovementState = EPlayerMovementState::EPMS_Default;
	ChangePlayerMovementState_Server(PlayerMovementState);
}

void APlayerCharacter::PlayerStartRunning()
{
	if(PlayerState != EPlayerState::EPS_Alive || PlayerState == EPlayerState::EPS_KnowDown) return;
	
	PlayerMovementState = EPlayerMovementState::EPMS_Default;
	
	ChangeMaxSpeed_Server(MaxRunSpeed);
	
}

void APlayerCharacter::PlayerStopRunning()
{
	if(PlayerState != EPlayerState::EPS_Alive || PlayerState == EPlayerState::EPS_KnowDown) return;
	
	PlayerMovementState = EPlayerMovementState::EPMS_Default;
	
	ChangeMaxSpeed_Server(MaxWalkSpeed);
}
	


void APlayerCharacter::PlayerStartCarrying()
{
	if(PlayerState != EPlayerState::EPS_Alive) return;

	PlayerMovementState = EPlayerMovementState::EPMS_Carrying;
	ChangePlayerMovementState_Server(PlayerMovementState);
}

void APlayerCharacter::PlayerStopCarrying()
{
	if(PlayerState != EPlayerState::EPS_Alive || PlayerMovementState != EPlayerMovementState::EPMS_Carrying) return;

	PlayerMovementState = EPlayerMovementState::EPMS_Default;
	ChangePlayerMovementState_Server(PlayerMovementState);
}

void APlayerCharacter::PlayerDead()
{
	if(PlayerState == EPlayerState::EPS_Dead) return;

	PlayerState = EPlayerState::EPS_Dead;
	PlayerMovementState = EPlayerMovementState::EPMS_Dead;
	ChangePlayerMovementState_Server(PlayerMovementState);
}

void APlayerCharacter::ChangeMaxSpeed_Server_Implementation(const float Speed)
{
	if(HasAuthority()) GetCharacterMovement()->MaxWalkSpeed = Speed;

	MaxSpeed = Speed;
}

void APlayerCharacter::ChangePlayerMovementState_Server_Implementation(const EPlayerMovementState MovementState)
{
	PlayerMovementState = MovementState;
}

void APlayerCharacter::OnRep_MaxSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
}

void APlayerCharacter::OnRep_MovementState()
{
	
}


