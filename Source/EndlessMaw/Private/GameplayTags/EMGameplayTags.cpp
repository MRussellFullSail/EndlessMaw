// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayTags/EMGameplayTags.h"
#include "Engine/EngineTypes.h"
#include "GameplayTagsManager.h"

namespace EMTag {
	UE_DEFINE_GAMEPLAY_TAG(PawnState_Dead, "PawnState.Dead");
	UE_DEFINE_GAMEPLAY_TAG(PawnState_Attacking, "PawnState.Attacking");
	UE_DEFINE_GAMEPLAY_TAG(PawnState_CanQueueAttack, "PawnState.CanQueueAttack");
	UE_DEFINE_GAMEPLAY_TAG(PawnState_Moveable, "PawnState.Moveable");


	FGameplayTag FindTag(const FString& TagToFind, bool PartialMatch)
	{
		const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
		FGameplayTag Tag = Manager.RequestGameplayTag(FName(*TagToFind), false);

		return Tag;
	}
};
