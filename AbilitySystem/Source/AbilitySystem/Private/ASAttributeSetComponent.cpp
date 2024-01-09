// Fill out your copyright notice in the Description page of Project Settings.


#include "ASAttributeSetComponent.h"
#include "ASAttribute.h"
#include "Engine/ActorChannel.h"

UASAttributeSetComponent::UASAttributeSetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);
}

bool UASAttributeSetComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool result = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for(auto* Attr : Attributes)
	{
		if(!Attr) continue;

		result |= Channel->ReplicateSubobject(Attr, *Bunch, *RepFlags);
	}
	
	return result;
}

void UASAttributeSetComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!GetOwner()->HasAuthority()) return;

	for (const auto Attr : DefaultAttributes)
	{
		AddAttribute(Attr);
	}
}

UASAttribute* UASAttributeSetComponent::GetAttribute(FGameplayTag Tag)
{
	for (auto Attr : Attributes)
	{
		if (Attr == nullptr || Attr->GetGameplayTag() != Tag) continue;
		return Attr;
	}
	
	return nullptr;
}

const UASAttribute* UASAttributeSetComponent::GetAttribute(FGameplayTag Tag) const
{
	for (auto Attr : Attributes)
	{
		if (Attr == nullptr || Attr->GetGameplayTag() != Tag) continue;
		return Attr;
	}
	
	return nullptr;
}

bool UASAttributeSetComponent::GetAttributeBase(FGameplayTag Tag, float& OutValue) const
{
	const auto* Attr = GetAttribute(Tag);
	if (Attr == nullptr) return false;
	OutValue = Attr->GetBaseValue();
	return true;
}

bool UASAttributeSetComponent::GetAttributeCurrent(FGameplayTag Tag, float& OutValue) const
{
	const auto* Attr = GetAttribute(Tag);
	if (Attr == nullptr) return false;
	OutValue = Attr->GetCurrentValue();
	return true;
}

void UASAttributeSetComponent::AddAttribute(TSubclassOf<UASAttribute> AttributeClass)
{
	if (!ensure(AttributeClass)) return;

	if (!GetOwner()->HasAuthority()) return;
	
	auto* NewAttribute = NewObject<UASAttribute>(this, AttributeClass);
	if (!ensure(NewAttribute)) return;

	Attributes.Add(NewAttribute);
}

void UASAttributeSetComponent::RemoveAttribute(FGameplayTag Tag)
{
	if (!GetOwner()->HasAuthority()) return;
	
	auto* Attr = GetAttribute(Tag);
	if(Attr == nullptr) return;
	Attributes.Remove(Attr);	
}

bool UASAttributeSetComponent::AddToCurrentValue(FGameplayTag Tag, float Value, float& NewValue)
{
	if (!GetOwner()->HasAuthority()) return false;;
	
	auto* Attr = GetAttribute(Tag);
	if(Attr == nullptr) return false;
	NewValue = Attr->SetCurrentValue(Attr->GetCurrentValue() + Value);
	return true;
}

bool UASAttributeSetComponent::AddToBaseValue(FGameplayTag Tag, float Value, float& NewValue)
{
	if (!GetOwner()->HasAuthority()) return false;
	
	auto* Attr = GetAttribute(Tag);
	if(Attr == nullptr) return false;
	NewValue = Attr->SetBaseValue(Attr->GetBaseValue() + Value);
	return true;
}

bool UASAttributeSetComponent::SubtractToCurrentValue(FGameplayTag Tag, float Value, float& NewValue)
{
	if (!GetOwner()->HasAuthority()) return false;;
	
	auto* Attr = GetAttribute(Tag);
	if(Attr == nullptr) return false;
	NewValue = Attr->SetCurrentValue(Attr->GetCurrentValue() - Value);
	return true;
}

bool UASAttributeSetComponent::SubtractToBaseValue(FGameplayTag Tag, float Value, float& NewValue)
{
	if (!GetOwner()->HasAuthority()) return false;
	
	auto* Attr = GetAttribute(Tag);
	if(Attr == nullptr) return false;
	NewValue = Attr->SetBaseValue(Attr->GetBaseValue() - Value);
	return true;
}

bool UASAttributeSetComponent::AddModifier(FGameplayTag AttributeTag, TSubclassOf<UASAttributeModifier> ModifierClass)
{
	if (!GetOwner()->HasAuthority()) return false;
 	
	auto* Attr = GetAttribute(AttributeTag);
	if (Attr == nullptr) return false;
	return Attr->AddModifier(ModifierClass);
}

bool UASAttributeSetComponent::RemoveModifier(FGameplayTag AttributeTag, FGameplayTag ModifierTag)
{
	if (!GetOwner()->HasAuthority()) return false;
	
	auto* Attr = GetAttribute(AttributeTag);
	if (Attr == nullptr) return false;
	return Attr->RemoveModifier(ModifierTag);
}
