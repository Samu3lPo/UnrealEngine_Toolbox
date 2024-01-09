// Fill out your copyright notice in the Description page of Project Settings.


#include "ASAttribute.h"
#include "ASAttributeModifier.h"
#include "Net/UnrealNetwork.h"

void UASAttribute::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UASAttribute, BaseValue);
	DOREPLIFETIME(UASAttribute, CurrentValue);
}

bool UASAttribute::AddModifier(TSubclassOf<UASAttributeModifier> ModifierClass)
{
	if (!ensure(ModifierClass)) return false;

	auto* NewModifier = NewObject<UASAttributeModifier>(this, ModifierClass);
	if (!ensure(NewModifier)) return false;

	Modifiers.Add(NewModifier);

	switch (NewModifier->GetOperation())
	{
	case EModifierOperation::Add:
		SetCurrentValue(GetCurrentValue() + NewModifier->ModifierValue);
		break;
	case EModifierOperation::Multuply:
		SetCurrentValue(GetCurrentValue() * NewModifier->ModifierValue);
		break;
	case EModifierOperation::Divide:
		SetCurrentValue(GetCurrentValue() / NewModifier->ModifierValue);
		break;
	case EModifierOperation::Subtract:
		SetCurrentValue(GetCurrentValue() - NewModifier->ModifierValue);
		break;
	default: ;	
	}

	return true;
}

bool UASAttribute::RemoveModifier(FGameplayTag ModifierTag)
{
	UASAttributeModifier* ModifierToRemove = nullptr;
	for (auto* Modifier : Modifiers)
	{
		if(!Modifier || Modifier->GetGameplayTag() != ModifierTag) continue;
		ModifierToRemove = Modifier;
		break;
	}
	
	if(ModifierToRemove == nullptr) return false;
	Modifiers.Remove(ModifierToRemove);
	
	switch (ModifierToRemove->GetOperation())
	{
	case EModifierOperation::Add:
		SetCurrentValue(GetCurrentValue() - ModifierToRemove->ModifierValue);
		break;
	case EModifierOperation::Multuply:
		SetCurrentValue(GetCurrentValue() / ModifierToRemove->ModifierValue);
		break;
	case EModifierOperation::Divide:
		SetCurrentValue(GetCurrentValue() * ModifierToRemove->ModifierValue);
		break;
	case EModifierOperation::Subtract:
		SetCurrentValue(GetCurrentValue() + ModifierToRemove->ModifierValue);
		break;
		default: ;	
	}

	return true;
}

void UASAttribute::OnRep_BaseValue(float OldValue)
{
	BaseValueChanged.Broadcast(OldValue, BaseValue);
}

void UASAttribute::OnRep_CurrentValue(float OldValue)
{
	CurrentValueChanged.Broadcast(OldValue, CurrentValue);
}
