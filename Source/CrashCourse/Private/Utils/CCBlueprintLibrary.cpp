// 


#include "Utils/CCBlueprintLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTagss/CCTags.h"
#include "Engine/OverlapResult.h"

#include "AbilitySystem/CCAttributeSet.h"
#include "Characters/CCBaseCharacter.h"
#include "Characters/CCEnemyCharacter.h"
#include "Characters/CCPlayerCharacter.h"
#include "Engine/OverlapResult.h"
#include "Kismet/GameplayStatics.h"

EHitDirection UCCBlueprintLibrary::GetHitDirection(const FVector& targetForward, const FVector& toInstigator)
{
	float dot = FVector::DotProduct(targetForward, toInstigator);
	if (dot < -0.5)
		return EHitDirection::Back;
	
	if (dot < 0.5)
	{
		FVector crossProduct = FVector::CrossProduct(targetForward, toInstigator);
		if (crossProduct.Z < 0.f)
			return EHitDirection::Left;
		return EHitDirection::Right;
	}
	return EHitDirection::Front;
}

FName UCCBlueprintLibrary::GetDirectionName(const EHitDirection direction)
{
	switch (direction)
	{
	case EHitDirection::Front:
		return FName("Front");
	case EHitDirection::Back:
		return FName("Back");
	case EHitDirection::Left:
		return FName("Left");
	case EHitDirection::Right:
		return FName("Right");
	default:
		return FName("Unknow");
	}
}

FClosestCharacterInfo UCCBlueprintLibrary::SearchClosestCharacter(const UObject* worldContextObject, const FVector& origin,
	const FName& tag)
{
	TArray<AActor*> searchActors;
	UGameplayStatics::GetAllActorsWithTag(worldContextObject, tag, searchActors);
	
	float closestDist = TNumericLimits<float>::Max();
	AActor* closestBaseCharacter = nullptr;
	for (AActor* actor: searchActors)
	{
		if (IsValid(actor))
		{
			ACCBaseCharacter* character = Cast<ACCBaseCharacter>(actor);		
			if (IsValid(character) && character->IsAlivate())
			{
				float dist = FVector::Dist(actor->GetActorLocation(), origin);
				if (dist < closestDist)
				{
					closestDist = dist;
					closestBaseCharacter = actor;
				}
			}
		}
	}
	
	FClosestCharacterInfo result;
	result.Character = closestBaseCharacter;
	result.Distance = closestDist;
	return result;
}

void UCCBlueprintLibrary::SendDamageEventToPlayer(AActor* target, const TSubclassOf<UGameplayEffect>& damageEffect,
	FGameplayEventData& payload, const FGameplayTag& damageTag, float damage,
	UObject* optionalParticleSystem)
{
	ACCPlayerCharacter* character = Cast<ACCPlayerCharacter>(target);
	if (!character || !character->IsAlivate()) return ;
	
	UCCAttributeSet* attributeSet = Cast<UCCAttributeSet>(character->GetAttributeSet());
	if (!attributeSet) return;
	bool bDeath = attributeSet->GetHealth() - damage <= 0.f;
	const FGameplayTag eventTag = bDeath ? CCTags::Events::Player::Death : CCTags::Events::Player::HitReact;
	
	payload.OptionalObject = optionalParticleSystem;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(character, eventTag, payload);
	
	UAbilitySystemComponent* ASC = character->GetAbilitySystemComponent();
	if (!IsValid(ASC)) return;
	FGameplayEffectContextHandle contextHandle = ASC->MakeEffectContext();
	FGameplayEffectSpecHandle effectSpec = ASC->MakeOutgoingSpec(damageEffect,1.0, contextHandle);

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(effectSpec, damageTag, -damage);
	
	ASC->ApplyGameplayEffectSpecToSelf(*effectSpec.Data.Get());
}

TArray<AActor*> UCCBlueprintLibrary::HitBoxOverlayTest(AActor* avatarActor, float hitBoxRadius,
	float forwardOffset,float hitBoxElevationOffset, bool bShowDebug)
{
	TArray<const AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(avatarActor);
	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActors(ActorsToIgnore);
	
	FCollisionResponseParams collisionResponses;
	collisionResponses.CollisionResponse.SetAllChannels(ECR_Ignore);
	collisionResponses.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);
	
	TArray<FOverlapResult> overlapResults;
	
	FCollisionShape shape =  FCollisionShape::MakeSphere(hitBoxRadius);
	const FVector forward = avatarActor->GetActorForwardVector() * forwardOffset;
	const FVector hitBoxLocation  = avatarActor->GetActorLocation() + forward + FVector(0,0,hitBoxElevationOffset);
	
	UWorld* world = GEngine->GetWorldFromContextObject(avatarActor, EGetWorldErrorMode::ReturnNull);
	world->OverlapMultiByChannel(overlapResults,  hitBoxLocation, FQuat::Identity, ECollisionChannel::ECC_Pawn,
		shape, queryParams, collisionResponses);
	
	TArray<AActor*> overlapActors;
	for (const FOverlapResult& result: overlapResults)
	{
		if (!IsValid(result.GetActor()))
			continue;
		overlapActors.Add(result.GetActor());
	}
	
	if (bShowDebug)
		DrawHitBoxOverlapDebug(avatarActor, overlapResults, hitBoxLocation, hitBoxRadius, hitBoxElevationOffset);
	
	return overlapActors;
}

void UCCBlueprintLibrary::DrawHitBoxOverlapDebug(AActor* avatarActor, const TArray<FOverlapResult> & overlayResults,const FVector& hitBoxLocation, float hitBoxRadius,
	float hitBoxElevationOffset)
{
	UWorld* world = GEngine->GetWorldFromContextObject(avatarActor, EGetWorldErrorMode::LogAndReturnNull);
	if (!IsValid(world))
		return;
	DrawDebugSphere(world, hitBoxLocation, hitBoxRadius, 16, FColor::Red, false, 3.0f);
	DrawDebugLine(world, avatarActor->GetActorLocation() + FVector(0, 0, hitBoxElevationOffset),
		hitBoxLocation, FColor::Green, false, 3.0f, 0, 3.7f);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, FString::Printf(TEXT("numOfHit:[%d"), overlayResults.Num()));
	for (const FOverlapResult&  result : overlayResults)
	{
		if (IsValid(result.GetActor()))
		{
			FVector debugLocation  =  result.GetActor()->GetActorLocation();
			debugLocation.Z += 100.0f;
			DrawDebugSphere(world, debugLocation, 30.0f, 16, FColor::Green,  false,  3.0f);
		}
	}

}

TArray<AActor*> UCCBlueprintLibrary::ApplyKnockback(AActor* avatarActor, const TArray<AActor*>& knockbackActors, float innerRadius,
	float outerRadius, float launchForceMagnitude, float rotationAngle, bool bDrawDebug)
{
	for (AActor* actor :knockbackActors)
	{
		ACharacter* character = Cast<ACharacter>(actor);
		if (!character || !IsValid(avatarActor))
			return TArray<AActor*>();
		
		const FVector avatorActorLocation = avatarActor->GetActorLocation();
		const FVector hitActorLocation = actor->GetActorLocation();
		const FVector toHit = hitActorLocation - avatorActorLocation;

		float launchForce = 0.f;
		float dist = toHit.Length();
		if (dist > outerRadius)
			continue;
		if (dist <innerRadius)
			launchForce = launchForceMagnitude;
		else
		{
			const FVector2D fallofRange(innerRadius, outerRadius);
			const FVector2D launchForceRange(launchForceMagnitude, 0.f);
			launchForce = FMath::GetMappedRangeValueClamped(fallofRange, launchForceRange, dist);
		}
		
		if (bDrawDebug)
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("LaunchForce:%f"), launchForce));
		
		FVector knockbackForce = toHit.GetSafeNormal();
		knockbackForce.Z = 0.f;
		
		const FVector right = knockbackForce.RotateAngleAxis(90.0f, FVector::UpVector);
		knockbackForce = knockbackForce.RotateAngleAxis(-rotationAngle, right) * launchForce;
		
		if (bDrawDebug)
		{
			UWorld* world = GEngine->GetWorldFromContextObject(avatarActor, EGetWorldErrorMode::LogAndReturnNull);
			DrawDebugDirectionalArrow(world, hitActorLocation, hitActorLocation + knockbackForce,
				100.0f, FColor::Green, false);
		}
		
		if (ACCEnemyCharacter* enemyCharacter = Cast<ACCEnemyCharacter>(character); IsValid(enemyCharacter))
		{
			enemyCharacter->StopMovementUntilLanded();
		}
		
		character->LaunchCharacter(knockbackForce, true, true);
	}
	return knockbackActors;
}
