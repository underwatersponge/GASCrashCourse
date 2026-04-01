

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CCPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
struct FGameplayTag;

UCLASS()
class CRASHCOURSE_API ACCPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

private:
	void Jump();
	void StopJump();
	void Look(const FInputActionValue& InputValue);
	void Move(const FInputActionValue& InputValue);
	void Primary();
	void Secondary();
	void Thirdary();
	
	void ActivateAbility(const FGameplayTag& tag) const;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Crash|Input")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContexts;

	// base move
	UPROPERTY(EditDefaultsOnly, Category = "Crash|Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Crash|Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Crash|Input")
	TObjectPtr<UInputAction> MoveAction;

	// ability
	UPROPERTY(EditDefaultsOnly, Category = "Crash|Ability")
	TObjectPtr<UInputAction> PrimaryAbility;
	
	UPROPERTY(EditDefaultsOnly, Category = "Crash|Ability")
	TObjectPtr<UInputAction> SecondAbility;
	
	UPROPERTY(EditDefaultsOnly, Category = "Crash|Ability");
	TObjectPtr<UInputAction> ThirdAbility;
};
