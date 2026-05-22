// 


#include "GameObjects/CCProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Characters/CCBaseCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagss/CCTags.h"

ACCProjectile::ACCProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");
}

void ACCProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Overlay"));
	Super::NotifyActorBeginOverlap(OtherActor);
	
	ACCBaseCharacter* character = Cast<ACCBaseCharacter>(OtherActor);
	if (!IsValid(character) || !character->IsAlivate())
		return;
	
	UAbilitySystemComponent* ASC = character->GetAbilitySystemComponent();
	if (!IsValid(ASC) || !HasAuthority())
		return;
	FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
	FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(DamageEffect, 1.0f, EffectContextHandle);
	
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(EffectSpecHandle, CCTags::SetByCaller::Projectile, Damage);
	ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	
	SpawnImpactEffects();
	Destroy();
}
