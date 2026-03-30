

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

private:

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FallowCamera;
};
