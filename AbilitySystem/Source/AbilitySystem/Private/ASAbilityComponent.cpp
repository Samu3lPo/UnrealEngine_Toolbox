// Fill out your copyright notice in the Description page of Project Settings.


#include "ASAbilityComponent.h"
#include "Engine/ActorChannel.h"

UASAbilityComponent::UASAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);
}

bool UASAbilityComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool result = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for(auto* Ability : Abilities)
	{
		if(!Ability) continue;

		result |= Channel->ReplicateSubobject(Ability, *Bunch, *RepFlags);
	}
	
	return result;
}

void UASAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	if(!GetOwner()->HasAuthority()) return;
	
	for(const auto Ability : DefaultAbilities)
	{
		AddAbility(Ability,GetOwner());
	}
}

void UASAbilityComponent::ServerStart_Implementation(FGameplayTag AbilityTag, AActor* Instigator)
{
	StartAbility(AbilityTag, Instigator);
}

void UASAbilityComponent::ServerStop_Implementation(FGameplayTag AbilityTag, AActor* Instigator)
{
	StopAbility(AbilityTag, Instigator);
}

void UASAbilityComponent::ServerAddAbility_Implementation(TSubclassOf<UASAbility> AbilityClass, AActor* Instigator)
{
	AddAbility(AbilityClass, Instigator);
}

void UASAbilityComponent::ServerRemoveAbility_Implementation(FGameplayTag AbilityTag)
{
	RemoveAbility(AbilityTag);
}

void UASAbilityComponent::AddAbility(TSubclassOf<UASAbility> AbilityClass, AActor* Instigator)
{
	if(!ensure(AbilityClass)) return;

	if (!GetOwner()->HasAuthority())
	{
		ServerAddAbility(AbilityClass, Instigator);
		return;
	}

	auto* NewAbility = NewObject<UASAbility>(this,AbilityClass);
	if(!ensure(NewAbility)) return;
	
	Abilities.Add(NewAbility);

	if(NewAbility->bAutoStart && ensure(NewAbility->CanStart(Instigator)))
	{
		NewAbility->Start(Instigator);
	}
}

bool UASAbilityComponent::RemoveAbility(FGameplayTag AbilityTag)
{
	if (!GetOwner()->HasAuthority())
	{
		ServerRemoveAbility(AbilityTag);
		return true;
	}
	
	UASAbility* AbilityToRemove = nullptr;
	for (auto* Ability : Abilities)
	{
		if(!Ability || Ability->GetGameplayTag() != AbilityTag) continue;
		if(Ability->IsRunning()) return false;
		AbilityToRemove = Ability;
		break;
	}

	return Abilities.Remove(AbilityToRemove) != 0;
}

bool UASAbilityComponent::StartAbility(FGameplayTag AbilityTag, AActor* Instigator)
{
	if (!GetOwner()->HasAuthority())
	{
		ServerStart(AbilityTag, Instigator);
		return true;
	}
	
	for (auto* Ability : Abilities)
	{
		if(!Ability || Ability->GetGameplayTag() != AbilityTag) continue;
		if(!Ability->CanStart(Instigator)) return false;
		Ability->Start(Instigator);
		return true;
	}
	return false;
}

bool UASAbilityComponent::StopAbility(FGameplayTag AbilityTag, AActor* Instigator)
{
	if (!GetOwner()->HasAuthority())
	{
		ServerStop(AbilityTag, Instigator);
		return true;
	}
	
	for (auto* Ability : Abilities)
	{
		if(!Ability || Ability->GetGameplayTag() != AbilityTag) continue;
		if(!Ability->IsRunning()) return false;
		Ability->Stop(Instigator);
		return true;
	}
	return false;
}
