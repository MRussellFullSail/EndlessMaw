// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MeleePlayer.h"
#include "Animation/BaseCharacter/BCAnimInstance.h"


void AMeleePlayer::LightAttack(const FInputActionValue& value)
{
	if (IsValid(LightAttackMontage)) {
		if (CanQueueNextAttack()) {
			if (!AnimInstance->Montage_IsPlaying(LightAttackMontage)) {
				UE_LOG(LogTemp, Warning, TEXT("set to opener"));
				AnimInstance->Montage_JumpToSection(FName("Opener"), LightAttackMontage);
			}
			UE_LOG(LogTemp, Warning, TEXT("meleeplayer queued next attack"))
			AnimInstance->Montage_JumpToSection(GetMontageSection(), LightAttackMontage);
			bCanQueueNextAttack = false;
			PlayAnimMontage(LightAttackMontage, 1.f, MontageSection);
		}
		else if (!AnimInstance->Montage_IsPlaying(LightAttackMontage)) {
			UE_LOG(LogTemp, Warning, TEXT("restting to opener"));
			AnimInstance->Montage_JumpToSection(FName("Opener"), LightAttackMontage);
		}
		//if (!AnimInstance->Montage_IsPlaying(LightAttackMontage)) {
		//	bCanQueueNextAttack = false;
		//	PlayAnimMontage(LightAttackMontage, 1.f, MontageSection);
		//	UE_LOG(LogTemp, Warning, TEXT("meleeplayer light attack montage"));
		//}
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
	UE_LOG(LogTemp, Warning, TEXT("melee ctor"));
}

void AMeleePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UE_LOG(LogTemp, Warning, TEXT("melee player input component"));
}

void AMeleePlayer::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("melee beginplay"));
	if (!AnimInstance) {
		UE_LOG(LogTemp, Warning, TEXT("melee has no animinstance"));
	}
}

