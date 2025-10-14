// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/QueueAttackNotifyState.h"
#include "Characters/BaseCharacter.h"
#include "Animation/BaseCharacter/BCAnimInstance.h"
#include "GameplayTags/EMGameplayTags.h"


void UQueueAttackNotifyState::NotifyBegin(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, float totalDuration)
{

	ABaseCharacter* character = Cast<ABaseCharacter>(meshComp->GetOwner());
	if (character) {
		UBCAnimInstance* animinst = Cast<UBCAnimInstance>(meshComp->GetAnimInstance());
		if (animinst) {
			UAnimMontage* montage = Cast<UAnimMontage>(animation);
			if (montage) {
				// we can queue the next attack
				//character->SetQueueNextAttack(true);
				character->PawnTags.AddTag(EMTag::PawnState_CanQueueAttack);
				FName currentSection = animinst->Montage_GetCurrentSection(montage);
				if (montage->IsValidSectionName(currentSection)) {
					// where are we in our current combo
					int currentindex = montage->GetSectionIndex(currentSection);
					if (montage->IsValidSectionIndex(currentindex + 1)) { // is the next section valid?
						NextSection = montage->GetSectionName(currentindex + 1);
						// end of combo back to beginning
						if (NextSection == NAME_None) {
							character->SetMontageSection(FName("Opener"));
						}
						else {
							// continue our combo
							character->SetMontageSection(NextSection);
						}
					}
					else { // its not valid back to beginning
						character->SetMontageSection(FName("Opener"));
					}
				}
			}
		}
	}
}

void UQueueAttackNotifyState::NotifyEnd(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation)
{
	ABaseCharacter* character = Cast<ABaseCharacter>(meshComp->GetOwner());
	if (character) {
		if (character->PawnTags.HasTag(EMTag::PawnState_CanQueueAttack)) { // player never queued an attack, return to opener
			character->SetMontageSection(FName("Opener"));
			UBCAnimInstance* animinst = Cast<UBCAnimInstance>(meshComp->GetAnimInstance());
			if (animinst) {
				animinst->SetMoveable(true);
				//character->isAttacking = false;
				character->PawnTags.RemoveTag(EMTag::PawnState_Attacking);
			}
		}
	}
}
