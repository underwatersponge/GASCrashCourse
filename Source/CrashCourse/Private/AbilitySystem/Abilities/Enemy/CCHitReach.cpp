// 


#include "AbilitySystem/Abilities/Enemy/CCHitReach.h"

void UCCHitReach::CacheHitDirectionVectors(AActor* instigator)
{
	avatarForward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	
	FVector ownLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
	FVector instigatorLocation = instigator->GetActorLocation();
	toInstigator = instigatorLocation - ownLocation;
	toInstigator.Normalize();
}
