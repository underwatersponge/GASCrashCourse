

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CCBaseCharacter.generated.h"

UCLASS(Abstract)
class CRASHCOURSE_API ACCBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACCBaseCharacter();

protected:
	virtual void BeginPlay() override;
};
