
#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "VectorTypes.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "SomeHorror/Components/StaminaComponent.h"


constexpr float InteractDistance = 250.0f;

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment( Cast<USceneComponent>(GetCapsuleComponent()));

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraCompoent"));
	PlayerCamera->SetupAttachment(StaticMeshComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthCompoent"));

	StaminaComponent = CreateDefaultSubobject<UStaminaComponent>(TEXT("StaminaComponent"));
	

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
		EnhancedInputComponent->BindAction(EquipAction , ETriggerEvent::Started , this , &APlayerCharacter::EquipButtonPressed);
	}
	

}

void APlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerCharacter, MaxSpeed);
	DOREPLIFETIME(APlayerCharacter , PlayerMovementState);
	DOREPLIFETIME(APlayerCharacter , PlayerCustomState);
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	if(PlayerCustomState == EPlayerState::EPS_Alive)
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
	if(PlayerCustomState != EPlayerState::EPS_Alive) return;

	FHitResult HitResult;
	const FVector CameraLocation = PlayerCamera->GetComponentLocation();

	GetWorld()->LineTraceSingleByChannel(HitResult , CameraLocation , CameraLocation + PlayerCamera->GetForwardVector() * InteractDistance , ECC_Visibility);

	if(!HitResult.bBlockingHit) return;

	GEngine->AddOnScreenDebugMessage(-1 , 3.0f , FColor::Red , HitResult.GetActor()->GetName());

	
}

void APlayerCharacter::Damage_Server_Implementation(APlayerCharacter* PlayerCharacter)
{
	PlayerCharacter->GetHealthComponent()->TakeDamage(100.0f);
}


void APlayerCharacter::PlayerKnockDown_Implementation()
{
	PlayerCustomState = EPlayerState::EPS_KnockDown;
	PlayerMovementState = EPlayerMovementState::EPMS_Lie;
	
	MaxSpeed = 150.0f;

	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
}

void APlayerCharacter::PlayerRecovered()
{
	if(PlayerCustomState != EPlayerState::EPS_KnockDown) return;

	PlayerCustomState = EPlayerState::EPS_Alive;
	PlayerMovementState = EPlayerMovementState::EPMS_Default;
}

void APlayerCharacter::PlayerCrouch()
{
	if(PlayerCustomState != EPlayerState::EPS_Alive || PlayerCustomState == EPlayerState::EPS_KnockDown) return;

	if(CanCrouch())
	{
		Crouch();

		if(HasAuthority())
		{
			PlayerMovementState = EPlayerMovementState::EPMS_Crouch;
		}

		else
		{
			ChangePlayerMovementState_Server(EPlayerMovementState::EPMS_Crouch);
		}
	}

	
}

void APlayerCharacter::PlayerStopCrouch()
{
	if(PlayerCustomState != EPlayerState::EPS_Alive || PlayerCustomState == EPlayerState::EPS_KnockDown) return;

	UnCrouch();

	if(HasAuthority())
		PlayerMovementState = EPlayerMovementState::EPMS_Default;
	else
	{
		ChangePlayerMovementState_Server(EPlayerMovementState::EPMS_Default);
	}
}

void APlayerCharacter::PlayerStartRunning_Implementation()
{
	if(PlayerCustomState != EPlayerState::EPS_Alive || PlayerCustomState == EPlayerState::EPS_KnockDown || GetCharacterMovement()->IsCrouching()) return;

	if(StaminaComponent && !StaminaComponent->CanRun) return;

	StaminaComponent->StartConsumeStamina();
		
	
	PlayerMovementState = EPlayerMovementState::EPMS_Default;

	GEngine->AddOnScreenDebugMessage(-1 , 10.0f , FColor::Red , "Running");
	
	MaxSpeed = MaxRunSpeed;

	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
	
	
}

void APlayerCharacter::PlayerStopRunning_Implementation()
{
	if(PlayerCustomState != EPlayerState::EPS_Alive || PlayerCustomState == EPlayerState::EPS_KnockDown || GetCharacterMovement()->IsCrouching()) return;

	if(StaminaComponent)
		StaminaComponent->StartRegenerateStamina();
	
	PlayerMovementState = EPlayerMovementState::EPMS_Default;
	
	MaxSpeed = MaxWalkSpeed;

	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
}
	


void APlayerCharacter::PlayerStartCarrying()
{
	if(PlayerCustomState != EPlayerState::EPS_Alive) return;

	PlayerMovementState = EPlayerMovementState::EPMS_Carrying;
	ChangePlayerMovementState_Server(PlayerMovementState);
}

void APlayerCharacter::PlayerStopCarrying()
{
	if(PlayerCustomState != EPlayerState::EPS_Alive || PlayerMovementState != EPlayerMovementState::EPMS_Carrying) return;

	PlayerMovementState = EPlayerMovementState::EPMS_Default;
	ChangePlayerMovementState_Server(PlayerMovementState);
}

void APlayerCharacter::PlayerDead()
{
	if(PlayerCustomState == EPlayerState::EPS_Dead) return;

	PlayerCustomState = EPlayerState::EPS_Dead;
	PlayerMovementState = EPlayerMovementState::EPMS_Dead;
	ChangePlayerMovementState_Server(PlayerMovementState);
	ChangePlayerState_Server(PlayerCustomState);
}

void APlayerCharacter::ChangeMaxSpeed_Server_Implementation(const float Speed)
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void APlayerCharacter::ChangePlayerMovementState_Server_Implementation(const EPlayerMovementState MovementState)
{
	PlayerMovementState = MovementState;
}

void APlayerCharacter::ChangePlayerState_Server_Implementation(const EPlayerState State)
{
	PlayerCustomState = State;
}

void APlayerCharacter::OnRep_MaxSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
}

void APlayerCharacter::OnRep_MovementState()
{
	GEngine->AddOnScreenDebugMessage(-1 , 10.0f , FColor::Orange , "MovementReplication");
}


