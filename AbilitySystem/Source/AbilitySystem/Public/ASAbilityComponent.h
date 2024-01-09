// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASAbility.h"
#include "ASAbilityComponent.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSYSTEM_API UASAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//Set default values for this component's properties
	UASAbilityComponent();

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	UFUNCTION(BlueprintCallable, Category="Ability")
	void AddAbility(TSubclassOf<UASAbility> AbilityClass, AActor* Instigator);

	UFUNCTION(BlueprintCallable, Category="Ability")
	bool RemoveAbility(FGameplayTag AbilityTag);

	UFUNCTION(BlueprintCallable, Category="Ability")
	bool StartAbility(FGameplayTag AbilityTag, AActor* Instigator);

	UFUNCTION(BlueprintCallable, Category="Ability")
	bool StopAbility(FGameplayTag AbilityTag, AActor* Instigator);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tags")
	FGameplayTagContainer ActiveGameplayTags;

protected:
	//Called when the game starts
	virtual void BeginPlay() override;

	//Here we are tagging with UPROPERTY since this allow Unreal
	//to track this object and its subobjects (pointer of USAction)
	//in the garbage collector
	UPROPERTY(BlueprintReadOnly, Category = "Ability")
	TArray<UASAbility*> Abilities;

	UFUNCTION(Server, Reliable)
	void ServerStart(FGameplayTag AbilityTag, AActor* Instigator);

	UFUNCTION(Server, Reliable)
	void ServerStop(FGameplayTag AbilityTag, AActor* Instigator);

	UFUNCTION(Server, Reliable)
	void ServerAddAbility(TSubclassOf<UASAbility> AbilityClass, AActor* Instigator);

	UFUNCTION(Server, Reliable)
	void ServerRemoveAbility(FGameplayTag AbilityTag);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	TArray<TSubclassOf<UASAbility>> DefaultAbilities;
	
};
