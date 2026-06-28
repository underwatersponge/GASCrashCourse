// 

#include "AbilitySystem/Abilities/Player/CCPrimary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Engine/OverlapResult.h"
#include "GameplayTagss/CCTags.h"

void UCCPrimary::SendHitReactEventToActor(const TArray<AActor*>& actorHit)
{
	for (AActor* hitActor: actorHit)
	{
		FGameplayEventData payload;
		payload.Instigator = GetAvatarActorFromActorInfo();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(hitActor, CCTags::Events::Enemy::HitReact, payload);
	}
}
