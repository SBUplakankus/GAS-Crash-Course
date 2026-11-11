// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/CC_AbilitySystemComponent.h"

#include "GameplayTags/CCTags.h"


void UCC_AbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);
	
	HandleAutoActivatedAbility(AbilitySpec);
}

void UCC_AbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();
	
	FScopedAbilityListLock ActiveScopeLock(*this);
	
	for (const auto& AbilitySpec: GetActivatableAbilities())
	{
		HandleAutoActivatedAbility(AbilitySpec);
	}
}

void UCC_AbilitySystemComponent::SetAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level)
{
	if (!IsValid(GetAvatarActor()) || !GetAvatarActor()->HasAuthority()) return;
	
	FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromClass(AbilityClass);
	
	if (AbilitySpec)
	{
		AbilitySpec->Level = Level;
		MarkAbilitySpecDirty(*AbilitySpec);
	}
}

void UCC_AbilitySystemComponent::AddToAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level)
{
	if (!IsValid(GetAvatarActor()) || !GetAvatarActor()->HasAuthority()) return;
	
	FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromClass(AbilityClass);
	
	if (AbilitySpec)
	{
		AbilitySpec->Level += Level;
		MarkAbilitySpecDirty(*AbilitySpec);
	}
}

void UCC_AbilitySystemComponent::HandleAutoActivatedAbility(const FGameplayAbilitySpec& AbilitySpec)
{
	if (!IsValid(AbilitySpec.Ability)) return;
	
	for (const auto Tag : AbilitySpec.Ability->GetAssetTags())
	{
		if (Tag.MatchesTagExact(CCTags::CCAbilities::ActivateOnGiven))
		{
			TryActivateAbility(AbilitySpec.Handle);
		}
	}
}
