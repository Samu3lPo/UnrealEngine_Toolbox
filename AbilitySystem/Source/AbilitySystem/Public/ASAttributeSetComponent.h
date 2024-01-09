// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ASAttributeSetComponent.generated.h"

class UASAttribute;
class UASAttributeModifier;

UCLASS()
class ABILITYSYSTEM_API UASAttributeSetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UASAttributeSetComponent();

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	UASAttribute* GetAttribute(FGameplayTag Tag);

	const UASAttribute* GetAttribute(FGameplayTag Tag) const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool GetAttributeBase(FGameplayTag Tag, float& OutValue) const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool GetAttributeCurrent(FGameplayTag Tag, float& OutValue) const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void AddAttribute(TSubclassOf<UASAttribute> AttributeClass);
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void RemoveAttribute(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool AddToCurrentValue(FGameplayTag Tag, float Value, float& NewValue);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool AddToBaseValue(FGameplayTag Tag, float Value, float& NewValue);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool SubtractToCurrentValue(FGameplayTag Tag, float Value, float& NewValue);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool SubtractToBaseValue(FGameplayTag Tag, float Value, float& NewValue);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	TArray<TSubclassOf<UASAttribute>> DefaultAttributes;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool AddModifier(FGameplayTag AttributeTag, TSubclassOf<UASAttributeModifier> ModifierClass);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool RemoveModifier(FGameplayTag AttributeTag, FGameplayTag ModifierTag);
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<UASAttribute*> Attributes;
};
