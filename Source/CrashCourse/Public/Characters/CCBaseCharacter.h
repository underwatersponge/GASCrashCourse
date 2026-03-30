

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"

#include "CCBaseCharacter.generated.h"

UCLASS(Abstract)
class CRASHCOURSE_API ACCBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACCBaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
protected:
	virtual void BeginPlay() override;
};
