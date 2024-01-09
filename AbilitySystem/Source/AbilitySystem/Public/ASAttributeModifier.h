// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "ASAttributeModifier.generated.h"

UENUM(BlueprintType)
enum class EModifierOperation : uint8
{
	Add,
	Multuply,
	Divide,
	Subtract
};

UCLASS(BlueprintType, Blueprintable)
class ABILITYSYSTEM_API UASAttributeModifier : public UObject
{
	GENERATED_BODY()

public:
	virtual bool IsSupportedForNetworking() const override { return true; }
	
	UFUNCTION(BlueprintCallable, Category="Attribute Modifier")
	FORCEINLINE FGameplayTag GetGameplayTag() const { return Tag; }

	UFUNCTION(BlueprintCallable, Category="Attribute Modifier")
	FORCEINLINE EModifierOperation GetOperation() const { return ModifierOperation; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attribute Modififer")
	float ModifierValue;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute Modififer", meta=(AllowPrivateAccess=true))
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute Modififer", meta=(AllowPrivateAccess=true))
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute Modififer", meta=(AllowPrivateAccess=true))
	EModifierOperation ModifierOperation;
};
