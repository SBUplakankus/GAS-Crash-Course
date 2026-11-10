// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/CC_BlueprintLibrary.h"

EHitDirection UCC_BlueprintLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator)
{
	const float DotProduct = FVector::DotProduct(TargetForward, ToInstigator);
	
	if (DotProduct < -0.5f)
	{
		return EHitDirection::Back;
	}
	
	if (DotProduct < 0.5f)
	{
		const FVector CrossProduct = FVector::CrossProduct(TargetForward, ToInstigator);
		
		if (CrossProduct.Z < 0.f)
		{
			return EHitDirection::Left;
		}
		
		return EHitDirection::Right;
	}
	
	return EHitDirection::Forward;
}

FName UCC_BlueprintLibrary::GetHitDirectionName(const EHitDirection HitDirection)
{
	switch (HitDirection)
	{
		case EHitDirection::Left: return FName("Left");
		case EHitDirection::Right: return FName("Right");
		case EHitDirection::Forward: return FName("Forward");
		case EHitDirection::Back: return FName("Back");
		default: return FName("None");
	}
}
