


#include "Characters/CCBaseCharacter.h"

ACCBaseCharacter::ACCBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

UAbilitySystemComponent* ACCBaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

void ACCBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}
