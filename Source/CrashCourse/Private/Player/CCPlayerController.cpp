#include "Player/CCPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

#include "CrashCourse/Public/GameplayTagss/CCTags.h"

void ACCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(InputSubsystem))
		return;

	for (auto& inputMappingContent : InputMappingContexts)
	{
		InputSubsystem->AddMappingContext(inputMappingContent,0);
	}

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(enhancedInputComponent))
		return;
	
	enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::Jump);
	enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJump);
	enhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	
	enhancedInputComponent->BindAction(PrimaryAbility, ETriggerEvent::Triggered, this, &ThisClass::Primary);
}

void ACCPlayerController::Jump()
{
	if (!IsValid(GetCharacter()))
		return;
	GetCharacter()->Jump();
}

void ACCPlayerController::StopJump()
{
	if(!IsValid(GetCharacter()))
		return;
	GetCharacter()->StopJumping();
}

void ACCPlayerController::Look(const FInputActionValue& InputValue)
{
	const FVector2D lookAxisVector = InputValue.Get<FVector2D>();

	AddYawInput(lookAxisVector.X);
	AddPitchInput(lookAxisVector.Y);
}

void ACCPlayerController::Move(const FInputActionValue& InputValue)
{
	const FVector2D moveVector = InputValue.Get<FVector2D>();
	const FRotator yawRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	GetPawn()->AddMovementInput(forwardDirection, moveVector.Y);
	GetPawn()->AddMovementInput(rightDirection, moveVector.X);
}

void ACCPlayerController::Primary()
{
	UE_LOG(LogTemp, Warning, TEXT("Primary"));
	ActivateAbility(CCTags::CCAbilities::Primary);
}

void ACCPlayerController::ActivateAbility(const FGameplayTag& tag) const
{
	 FGameplayTagContainer tagContainer = tag.GetSingleTagContainer();
	
	 UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	 if (!IsValid(ASC))
		 return;
	 ASC->TryActivateAbilitiesByTag(tagContainer);
}
