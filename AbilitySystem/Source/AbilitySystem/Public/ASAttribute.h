// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "ASAttribute.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttributeBaseValueChangedDelegate, float, OldValue, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttributeCurrentValueChangedDelegate, float, OldValue, float, NewValue);

class UASAttributeModifier;

UCLASS(Blueprintable)
class ABILITYSYSTEM_API UASAttribute : public UObject
{
	GENERATED_BODY()

public:
	virtual bool IsSupportedForNetworking() const override { return true; }
	
	UFUNCTION(BlueprintCallable, Category="Attribute")
	FORCEINLINE float GetBaseValue() const {return BaseValue;}

	UFUNCTION(BlueprintCallable, Category="Attribute")
	FORCEINLINE float SetBaseValue(float NewBaseValue)
	{
		float Temp = BaseValue;
		BaseValue = NewBaseValue;
		BaseValueChanged.Broadcast(Temp, BaseValue);
		return BaseValue;
	}

	UFUNCTION(BlueprintCallable, Category="Attribute")
	FORCEINLINE float GetCurrentValue() const {return CurrentValue;}
	
	UFUNCTION(BlueprintCallable, Category="Attribute")
	FORCEINLINE float SetCurrentValue(float NewCurrentValue)
	{
		float Temp = CurrentValue;
		CurrentValue = NewCurrentValue;
		CurrentValueChanged.Broadcast(Temp, CurrentValue);
		return CurrentValue;
	}

	UFUNCTION(BlueprintCallable, Category="Attribute")
	FORCEINLINE FGameplayTag GetGameplayTag() const {return Tag;}

	UFUNCTION(BlueprintCallable, Category="Attribute")
	bool AddModifier(TSubclassOf<UASAttributeModifier> ModifierClass);

	UFUNCTION(BlueprintCallable, Category="Attribute")
	bool RemoveModifier(FGameplayTag ModifierTag);

	UPROPERTY(BlueprintReadWrite, Category="Attribute")
	FAttributeBaseValueChangedDelegate BaseValueChanged;
	
	UPROPERTY(BlueprintReadWrite, Category="Attribute")
	FAttributeBaseValueChangedDelegate CurrentValueChanged;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Attriute")
	FGameplayTag Tag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attriute", meta=(AllowPrivateAccess=true))
	FName Name;

	UPROPERTY(ReplicatedUsing=OnRep_BaseValue, EditAnywhere, Category="Attriute")
	float BaseValue = 0;

	UPROPERTY(ReplicatedUsing=OnRep_CurrentValue, EditAnywhere, Category="Attriute")
	float CurrentValue = 0;

	UPROPERTY()
	TArray<UASAttributeModifier*> Modifiers;

	UFUNCTION()
	void OnRep_BaseValue(float OldValue);

	UFUNCTION()
	void OnRep_CurrentValue(float OldValue);
};
