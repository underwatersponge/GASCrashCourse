// 


#include "GameObjects/CCProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Characters/CCBaseCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "Characters/CCPlayerCharacter.h"
#include "GameplayTagss/CCTags.h"
#include "Utils/CCBlueprintLibrary.h"

ACCProjectile::ACCProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");
}

void ACCProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Overlay"));
	Super::NotifyActorBeginOverlap(OtherActor);
	
	ACCBaseCharacter* character = Cast<ACCPlayerCharacter>(OtherActor);
	if (!IsValid(character) || !character->IsAlivate())
		return;
	
	UAbilitySystemComponent* ASC = character->GetAbilitySystemComponent();
	if (!IsValid(ASC) || !HasAuthority())
		return;
	
	FGameplayEventData payload;
	payload.Instigator = GetOwner();
	payload.Target = character;
	UCCBlueprintLibrary::SendDamageEventToPlayer(character, DamageEffect, payload, CCTags::SetByCaller::Projectile, Damage, CCTags::None);
	
	SpawnImpactEffects();
	Destroy();
}
