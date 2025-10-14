// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace EMTag {
	FGameplayTag FindTag(const FString& Tag, bool PartialMatch = false);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PawnState_Dead);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PawnState_CanQueueAttack);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PawnState_Attacking);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(PawnState_Moveable);
};


/**
 * 
 */
//class ENDLESSMAW_API EMGameplayTags
//{
//public:
//	EMGameplayTags();
//	~EMGameplayTags();
//};
