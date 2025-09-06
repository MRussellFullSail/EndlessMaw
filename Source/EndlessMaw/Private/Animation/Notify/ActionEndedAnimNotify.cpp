// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/ActionEndedAnimNotify.h"
#include "Animation/BaseCharacter/BCAnimInstance.h"

void UActionEndedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (UBCAnimInstance* animInst = Cast<UBCAnimInstance>(MeshComp->GetAnimInstance())) {
		animInst->OnActionEnded.Broadcast();
	}
}
