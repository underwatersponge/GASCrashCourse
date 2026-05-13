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
	static FClosestCharacterInfo SearchClosestCharacter(const UObject* worldContextObject, const FVector& origin, const FName& tag);
};
