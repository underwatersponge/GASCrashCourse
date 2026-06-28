// 
#include "Notify/CCMeleeAttack.h"

#include "CrashCourse/Public/Characters/CCPlayerCharacter.h"
#include "GameplayTagss/CCTags.h"

#include "Kismet/KismetMathLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "KismetTraceUtils.h"

void UCCMeleeAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
                                const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	
	if (!IsValid(MeshComp))
		return;
	if (!IsValid(MeshComp->GetOwner()))
		return;
	
	TArray<FHitResult> Hits = PerformSphereTrace(MeshComp);
	SendEventsToActors(MeshComp, Hits);
	
}

TArray<FHitResult> UCCMeleeAttack::PerformSphereTrace(USkeletalMeshComponent* MeshComp) const
{
	FTransform transform = MeshComp->GetSocketTransform(SocketName);
	FVector start = transform.GetLocation();
	FVector dir = UKismetMathLibrary::GetForwardVector(transform.GetRotation().Rotator());
	FVector end = start - dir * SocketExtensionLen;
	
	FCollisionQueryParams params;
	params.AddIgnoredActor(MeshComp->GetOwner());
	
	FCollisionResponseParams responseParams;
	responseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	responseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);
	
	TArray<FHitResult> outHits;
	UWorld* world = GEngine->GetWorldFromContextObject(MeshComp, EGetWorldErrorMode::LogAndReturnNull);
	if (world)
	{
		bool const bHit = world->SweepMultiByChannel(
		outHits, start, end, FQuat::Identity, ECC_Visibility, 
		FCollisionShape::MakeSphere(SocketExtensionLen),
		params, responseParams
		);
		
		if (bDrawDebug)
		{
			DrawDebugSphereTraceMulti(world, start, end, SphereTraceRadians, EDrawDebugTrace::ForDuration, 
				bHit, outHits, FColor::Green, FColor::Red, 5.f);
		}
	}
	
	return outHits;
}

void UCCMeleeAttack::SendEventsToActors(USkeletalMeshComponent* meshComp, const TArray<FHitResult>& hits) const
{
	for ( const FHitResult& hitResult: hits)
	{
		ACCPlayerCharacter* playerCharacter = Cast<ACCPlayerCharacter>(hitResult.GetActor());
		if (IsValid(playerCharacter))
		{
			if (playerCharacter->IsAlivate())
			{
				UAbilitySystemComponent* ASC = playerCharacter->GetAbilitySystemComponent();
				if (ASC)
				{
					FGameplayEffectContextHandle contextHandle = ASC->MakeEffectContext();
					contextHandle.AddHitResult(hitResult);
					
					FGameplayEventData payload;
					payload.Target = playerCharacter;
					payload.ContextHandle = contextHandle;
					payload.Instigator = meshComp->GetOwner();
					
					UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(meshComp->GetOwner(),CCTags::Events::Enemy::MeleeTraceHit, payload);
				}
			}
		}
	}
}









