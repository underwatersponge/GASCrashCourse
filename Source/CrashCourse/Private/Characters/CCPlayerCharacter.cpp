#include "Characters/CCPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "AbilitySystemComponent.h"

#include "CrashCourse/Public/Player/CCPlayerState.h"
ACCPlayerCharacter::ACCPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//GetCapsuleComponent()->SetCapsuleSize(42.0f, 97.0f);
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 97.0f);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.0f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.37f;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CamerBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FallowCamera = CreateDefaultSubobject<UCameraComponent>("FallowCamera");
	FallowCamera->SetupAttachment(CameraBoom);
	FallowCamera->bUsePawnControlRotation = false;
}

UAbilitySystemComponent* ACCPlayerCharacter::GetAbilitySystemComponent() const
{
	ACCPlayerState* playerState = Cast<ACCPlayerState>(GetPlayerState());
	if (!IsValid(playerState))
		return nullptr;

	return playerState->GetAbilitySystemComponent();
}

void ACCPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!IsValid(GetAbilitySystemComponent()) || !HasAuthority())
		return;

	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	GiveStartupAbilities();
	InitializeAttributes();
}

void ACCPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (!IsValid(GetAbilitySystemComponent()))
		return;

	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	GiveStartupAbilities();
}
