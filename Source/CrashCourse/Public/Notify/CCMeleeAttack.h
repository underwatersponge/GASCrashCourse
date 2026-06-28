// 

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CCMeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class CRASHCOURSE_API UCCMeleeAttack : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	
private:
	TArray<FHitResult> PerformSphereTrace(USkeletalMeshComponent* MeshComp) const;
	void SendEventsToActors(USkeletalMeshComponent* meshComp, const TArray<FHitResult>& hits) const;

public:
	UPROPERTY(EditAnywhere, Category = "Crash|Debug")
	bool bDrawDebug;
	
	UPROPERTY(BlueprintReadWrite, Category = "Crash")
	FName SocketName{"FX_Trail_01_R"};
	UPROPERTY(EditAnywhere, Category = "Crash")
	float SocketExtensionLen = 37.0f;
	UPROPERTY(EditAnywhere, Category = "Crash")
	float SphereTraceRadians = 50.f;
};
