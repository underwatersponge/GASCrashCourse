

#pragma once

#include "CoreMinimal.h"
#include "Characters/CCBaseCharacter.h"
#include "CCPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class CRASHCOURSE_API ACCPlayerCharacter : public ACCBaseCharacter
{
	GENERATED_BODY()

public:
	ACCPlayerCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
private:

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FallowCamera;
};
