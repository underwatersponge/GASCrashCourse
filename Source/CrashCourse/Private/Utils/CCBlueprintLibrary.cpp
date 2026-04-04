// 


#include "Utils/CCBlueprintLibrary.h"

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
