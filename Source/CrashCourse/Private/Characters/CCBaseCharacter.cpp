


#include "Characters/CCBaseCharacter.h"

ACCBaseCharacter::ACCBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

void ACCBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}
