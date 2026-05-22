// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCProjectile.generated.h"

class UProjectileMovementComponent;
class UGameplayEffect;

UCLASS()
class CRASHCOURSE_API ACCProjectile : public AActor
{
	GENERATED_BODY()

public:
	ACCProjectile();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnImpactEffects();
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crash|Damage", meta = (ExposeOnSpawn, ClampMin = "0.0"))
	float Damage{-10.0f};
private:
	UPROPERTY(VisibleAnywhere, Category = "Crash|Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	
	UPROPERTY(EditDefaultsOnly, Category = "Crash|Damage")
	TSubclassOf<UGameplayEffect> DamageEffect;
};
