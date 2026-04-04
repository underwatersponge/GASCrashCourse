// 

#include "AbilitySystem/Abilities/Player/CCPrimary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Engine/OverlapResult.h"
#include "GameplayTagss/CCTags.h"

TArray<AActor*> UCCPrimary::HitBoxOverlayTest()
{
	TArray<const AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActors(ActorsToIgnore);
	
	FCollisionResponseParams collisionResponses;
	collisionResponses.CollisionResponse.SetAllChannels(ECR_Ignore);
	collisionResponses.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);
	
	TArray<FOverlapResult> overlapResults;
	
	FCollisionShape shape =  FCollisionShape::MakeSphere(HitBoxRadius);
	const FVector forward = GetAvatarActorFromActorInfo()->GetActorForwardVector() * HitBoxForwardOffset;;
	const FVector hitBoxLocation  = GetAvatarActorFromActorInfo()->GetActorLocation() + forward + FVector(0,0,HitBoxElevationOffset);
	
	GetWorld()->OverlapMultiByChannel(overlapResults,  hitBoxLocation, FQuat::Identity, ECollisionChannel::ECC_Pawn,
		shape, queryParams, collisionResponses);
	
	TArray<AActor*> overlapActors;
	for (const FOverlapResult& result: overlapResults)
	{
		if (!IsValid(result.GetActor()))
			continue;
		overlapActors.Add(result.GetActor());
	}
	
	if (bShowDebug)
		DrawHitBoxOverlapDebug(overlapResults, hitBoxLocation);
	
	return overlapActors;
}

void UCCPrimary::SendHitReactEventToActor(const TArray<AActor*>& actorHit)
{
	for (AActor* hitActor: actorHit)
	{
		FGameplayEventData payload;
		payload.Instigator = GetAvatarActorFromActorInfo();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(hitActor, CCTags::Events::Enemy::HitReact, payload);
	}
}

void UCCPrimary::DrawHitBoxOverlapDebug(const TArray<FOverlapResult>& overlapResults, const FVector& hitBoxLocation) const
{
	DrawDebugSphere(GetWorld(), hitBoxLocation, HitBoxRadius, 16, FColor::Red, false, 3.0f);
	DrawDebugLine(GetWorld(), GetAvatarActorFromActorInfo()->GetActorLocation() + FVector(0, 0, HitBoxElevationOffset),
		hitBoxLocation, FColor::Green, false, 3.0f, 0, 3.7f);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, FString::Printf(TEXT("numOfHit:[%d"), overlapResults.Num()));
	for (const FOverlapResult&  result : overlapResults)
	{
		if (IsValid(result.GetActor()))
		{
			FVector debugLocation  =  result.GetActor()->GetActorLocation();
			debugLocation.Z += 100.0f;
			DrawDebugSphere(GetWorld(), debugLocation, 30.0f, 16, FColor::Green,  false,  3.0f);
		}
	}
}

