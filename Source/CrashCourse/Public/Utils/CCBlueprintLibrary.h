// 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CCBlueprintLibrary.generated.h"

UENUM(BlueprintType)
enum class EHitDirection : uint8
{
	Left,
	Right,
	Front,
	Back
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
};
