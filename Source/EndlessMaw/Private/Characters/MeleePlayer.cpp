// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MeleePlayer.h"
#include "Animation/BaseCharacter/BCAnimInstance.h"

#include "Weapons/OneHandWeapon.h"
#include "GameplayTags/EMGameplayTags.h"


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
			//bCanQueueNextAttack = false;
			PawnTags.RemoveTag(EMTag::PawnState_CanQueueAttack);
			AnimInstance->SetMoveable(false);
			//isAttacking = true;
			PawnTags.AddTag(EMTag::PawnState_Attacking);
			// play the attack
			SetComboType(EComboType::Light);
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
	if (!MovementInstance) {
		UE_LOG(LogTemp, Warning, TEXT("melee has no movement"));
	}
	GetMesh()->LinkAnimClassLayers(MovementInstance);

	FActorSpawnParameters spawn;
	sword = GetWorld()->SpawnActor<AOneHandWeapon>(WeaponToSpawn);
	if (sword != nullptr) {
		sword->SetOwner(this);
		sword->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale,
			MainWeaponSocket);
		AnimInstance->OnDamageWindowStart.AddDynamic(sword, &ABaseWeapon::DamageWindowOn);
		AnimInstance->OnDamageWindowEnd.AddDynamic(sword, &ABaseWeapon::DamageWindowOff);
		sword->SetActorRelativeRotation(FRotator(0, -70, 110));
		sword->SetActorScale3D(FVector(.7, .3, .6));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("MeleePlayer, !sword"));
	}

}

