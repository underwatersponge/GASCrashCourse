// 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagss/CCTags.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CCBlueprintLibrary.generated.h"

struct FGameplayEventData;
struct FGameplayTag;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EHitDirection : uint8
{
	Left,
	Right,
	Front,
	Back
};

USTRUCT(BlueprintType) 
struct FClosestCharacterInfo
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<class AActor> Character = nullptr;
	
	UPROPERTY(BlueprintReadWrite)
	float Distance = 0.f;
};

UCLASS()
class CRASHCOURSE_API UCCBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Crash|Utils")
	static EHitDirection GetHitDirection(const FVector& targetForward, const FVector& toInstigator );
	
	UFUNCTION(BlueprintCallable, Category = "Crash|Utils")
	static FName GetDirectionName(const EHitDirection direction);
	
	UFUNCTION(BlueprintCallable, Category = "Crash|Utils")
	static FClosestCharacterInfo SearchClosestCharacter(UObject* worldContextObject, const FVector& origin, const FName& tag);
	
	UFUNCTION(BlueprintCallable, Category = "Crash|Utils")
	static void SendDamageEventToPlayer(AActor* target, const TSubclassOf<UGameplayEffect>& damageEffect,
		UPARAM(ref) FGameplayEventData& payload, const FGameplayTag& damageTag, float damage, const FGameplayTag& eventTagOverride, UObject* optionalParticleSystem = nullptr);
	
	
	UFUNCTION(BlueprintCallable, Category = "Crash|Utils")
	static void SendDamageEventToPlayers(TArray<AActor*> targets, const TSubclassOf<UGameplayEffect>& damageEffect,
		UPARAM(ref) FGameplayEventData& payload, const FGameplayTag& damageTag, float damage, const FGameplayTag& eventTagOverride, UObject* optionalParticleSystem = nullptr);
	
	
	UFUNCTION(BlueprintCallable, Category = "Crash|Utils")
	static TArray<AActor*> HitBoxOverlayTest(AActor* avatarActor, float hitBoxRadius = 1000.f,
		float forwardOffset=0.f,float hitBoxElevationOffset=0.f, bool bShowDebug = false);
	
	static void DrawHitBoxOverlapDebug( AActor* avatarActor, const TArray<FOverlapResult> & overlayResults,const FVector& hitBoxLocation, float hitBoxRadius,
	float hitBoxElevationOffset);
	
	UFUNCTION(BlueprintCallable, Category = "Crash|Utils")
	static TArray<AActor*> ApplyKnockback(AActor* avatarActor, const TArray<AActor*>& knockbackActors, 
				float innerRadius, float outerRadius, float launchForceMagnitude, float rotationAngle, bool bDrawDebug = false);
};
