// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASAbility.h"
#include "UObject/Object.h"
#include "ASAbilityEffect.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSYSTEM_API UASAbilityEffect : public UASAbility
{
	GENERATED_BODY()

public:
	UASAbilityEffect();
	virtual bool Start_Implementation(AActor* Instigator) override;
	virtual bool Stop_Implementation(AActor* Instigator) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Effect")
	float Duration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Effect")
	float Period;

	FTimerHandle PeriodHandle;
	FTimerHandle DurationHandle;

	UFUNCTION(BlueprintNativeEvent, Category= "Effect")
	void ExecutePeriodicEffect(AActor* Instigator);
};
