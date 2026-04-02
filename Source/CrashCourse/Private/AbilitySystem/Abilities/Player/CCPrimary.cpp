// 

#include "AbilitySystem/Abilities/Player/CCPrimary.h"

#include "Engine/OverlapResult.h"

void UCCPrimary::HitBoxOverlayTest()
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
	
	GetWorld()->OverlapMultiByChannel(overlapResults,  hitBoxLocation, FQuat::Identity, ECollisionChannel::ECC_Visibility,
		shape, queryParams, collisionResponses);
	
	if (bShowDebug)
	{
		DrawDebugSphere(GetWorld(), hitBoxLocation, HitBoxRadius, 16, FColor::Red, false, 3.0f);
		
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
}

