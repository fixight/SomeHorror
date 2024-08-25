#pragma once

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	EPS_Alive UMETA(DisplayName = "PlayerAlive") ,
	EPS_KnowDown UMETA(DisplayName = "PlayerKnowDown") ,
	EPS_Dead UMETA(DisplayName = "PlayerDead") ,
	EPS_Max UMETA(DisplayName = "Max")
};

UENUM(BlueprintType)
enum class EPlayerMovementState : uint8
{
	EPMS_Default UMETA(DisplayName = "Default") ,
	EPMS_Crouch UMETA(DisplayName = "Crouch") ,
	EPMS_Lie UMETA(DisplayName = "Lie") ,
	EPMS_Carrying UMETA(DisplayName = "Carrying") ,
	EPMS_LeaningBack UMETA(DisplayName = "Leaning") ,
	EPMS_Dead UMETA(DisplayName = "Dead") ,
	EPMS_Max UMETA(DisplayName = "Max")
};
