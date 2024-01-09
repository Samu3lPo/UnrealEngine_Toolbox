// Fill out your copyright notice in the Description page of Project Settings.


#include "ASAbilityEffect.h"
#include "ASAbilityComponent.h"
#include "TimerManager.h"

UASAbilityEffect::UASAbilityEffect()
{
	bAutoStart = true;
}

bool UASAbilityEffect::Start_Implementation(AActor* Instigator)
{
	bool ret = Super::Start_Implementation(Instigator);

	if(Duration > 0.0f)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this,"Stop", Instigator);
		GetWorld()->GetTimerManager().SetTimer(DurationHandle,Delegate,Duration,false);
	}

	if(Period > 0.0f)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this,"ExecutePeriodicEffect", Instigator);
		GetWorld()->GetTimerManager().SetTimer(PeriodHandle,Delegate,Period,true);
	}
	
	return ret;
}

bool UASAbilityEffect::Stop_Implementation(AActor* Instigator)
{
	if(GetWorld()->GetTimerManager().GetTimerRemaining(PeriodHandle) < KINDA_SMALL_NUMBER)
	{
		ExecutePeriodicEffect(Instigator);
	}
	
	bool ret = Super::Stop_Implementation(Instigator);

	GetWorld()->GetTimerManager().ClearTimer(PeriodHandle);
	GetWorld()->GetTimerManager().ClearTimer(DurationHandle);

	auto* Comp = GetOwningComponent();
	if(!ensure(Comp)) return false;

	Comp->RemoveAbility(AbilityTag);

	return ret;
}

void UASAbilityEffect::ExecutePeriodicEffect_Implementation(AActor* Instigator)
{
	
}
