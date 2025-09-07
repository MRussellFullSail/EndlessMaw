// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/QueueAttackNotifyState.h"
#include "Characters/BasePlayer.h"
#include "Animation/BaseCharacter/BCAnimInstance.h"


void UQueueAttackNotifyState::NotifyBegin(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, float totalDuration)
{
	//UAnimMontage* montage = Cast<UAnimMontage>(animation);
	//ABasePlayer* player = Cast<ABasePlayer>(meshComp->GetOwner());
	//int index = montage->GetSectionIndex(player->GetMontageSection());
	//
	//if (player) {
	//	if (montage->IsValidSectionIndex(++index))
	//	{
	//		player->SetQueueNextAttack(true);
	//		player->SetMontageSection(montage->GetSectionName(index));
	//	}
	//	else {
	//		player->SetMontageSection(FName("None"));
	//	}
	//}
	UE_LOG(LogTemp, Warning, TEXT("queue attack notify begin"));
	ABasePlayer* player = Cast<ABasePlayer>(meshComp->GetOwner());
	if (player) {


		UBCAnimInstance* animinst = Cast<UBCAnimInstance>(meshComp->GetAnimInstance());
		if (animinst) {
			UAnimMontage* montage = Cast<UAnimMontage>(animation);
			if (montage) {
				player->SetQueueNextAttack(true);
				FName currentSection = animinst->Montage_GetCurrentSection(montage);
				if (montage->IsValidSectionName(currentSection)) {
					int currentindex = montage->GetSectionIndex(currentSection);
					UE_LOG(LogTemp, Warning, TEXT("current index is: %d"), currentindex);
					if (montage->IsValidSectionIndex(currentindex + 1)) {
						NextSection = montage->GetSectionName(currentindex + 1);
						// end of combo back to beginning
						if (NextSection == NAME_None) {
							UE_LOG(LogTemp, Warning, TEXT("end of combo setting next section to none"));
							player->SetMontageSection(NAME_None);
						}
						else {
							// continue our combo
							UE_LOG(LogTemp, Warning, TEXT("setting next attack of the combo"));
							player->SetMontageSection(NextSection);
						}
					}
					else {
						UE_LOG(LogTemp, Error, TEXT("current section is valid section index"));
						player->SetMontageSection(FName("Opener"));
					}
				}
				else {
					UE_LOG(LogTemp, Error, TEXT("current section is invalid section name"));
				}
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("no montage for notify state"));
			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("no anim inst for notify state"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("no player for notify state"));
	}
}

void UQueueAttackNotifyState::NotifyEnd(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation)
{
	ABasePlayer* player = Cast<ABasePlayer>(meshComp->GetOwner());
	if (player) {
		UE_LOG(LogTemp, Warning, TEXT("end of queueattackstate"));
		if (player->CanQueueNextAttack()) {
			UE_LOG(LogTemp, Warning, TEXT("player did not queue an attack, resetting montage to opener"));
			player->SetMontageSection(FName("Opener"));
		}
	}
}
