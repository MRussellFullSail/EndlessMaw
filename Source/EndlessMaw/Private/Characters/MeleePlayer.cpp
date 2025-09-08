// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MeleePlayer.h"
#include "Animation/BaseCharacter/BCAnimInstance.h"


void AMeleePlayer::LightAttack(const FInputActionValue& value)
{
	if (IsValid(LightAttackMontage)) {
		if (CanQueueNextAttack()) { // can we attack?
			if (!AnimInstance->Montage_IsPlaying(LightAttackMontage)) { // no montage is playing, goto the opener
				AnimInstance->Montage_JumpToSection(FName("Opener"), LightAttackMontage);
			}
			// jump to the section to plau
			AnimInstance->Montage_JumpToSection(GetMontageSection(), LightAttackMontage);
			// mark that we are unable to attack
			bCanQueueNextAttack = false;
			AnimInstance->SetMoveable(false);
			isAttacking = true;
			// play the attack
			PlayAnimMontage(LightAttackMontage, 1.f, MontageSection);
		}
		else if (!AnimInstance->Montage_IsPlaying(LightAttackMontage)) { 
			// we cant attack but no montage is playing reset, to the opener
			AnimInstance->Montage_JumpToSection(FName("Opener"), LightAttackMontage);
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Melee Player, !LightAttackMontage"));
	}
}

void AMeleePlayer::HeavyAttack(const FInputActionValue& value)
{
}

void AMeleePlayer::AlternateAttack(const FInputActionValue& value)
{
}

AMeleePlayer::AMeleePlayer()
{
}

void AMeleePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMeleePlayer::BeginPlay()
{
	Super::BeginPlay();
	if (!AnimInstance) {
		UE_LOG(LogTemp, Warning, TEXT("melee has no animinstance"));
	}
}

