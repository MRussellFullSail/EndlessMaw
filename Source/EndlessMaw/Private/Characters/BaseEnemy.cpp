// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Animation/AnimMontage.h"
#include "Animation/BaseCharacter/BCAnimInstance.h"
#include "AI/AIC_Enemy.h"
#include "BrainComponent.h"
#include "Components/AC_Health.h"


ABaseEnemy::ABaseEnemy()
	:HealthKey("Health"), ActionFinished("ActionFinished")
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	AIC_Enemy = Cast<AAIC_Enemy>(GetController());
	if (AIC_Enemy) {
		AIC_Enemy->OnPerception.AddDynamic(this, &ABaseEnemy::HandlePerception);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("BaseEnemy, !AIController"));
		Destroy();
		return;
	}
	if (AnimInstance) {
		AnimInstance->SetMoveable(true);
		AnimInstance->OnMontageEnded.AddDynamic(this, &ABaseEnemy::HandleMontageFinished);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("BaseEnemy, !AnimInstance"));
		Destroy();
		return;
	}
	UpdateBlackboardHealth(1.f);
}

void ABaseEnemy::HandlePerception(AActor* actor, FAIStimulus stimulus)
{
	//UE_LOG(LogTemp, Warning, TEXT("BaseEnemy HandlePerception"));
	// check our blackboard is there
	if (UBlackboardComponent* BB = AIC_Enemy->GetBlackboardComponent()) {
		if (stimulus.WasSuccessfullySensed()) {
			// if we sensed it: set our playerkey to the actor
			BB->SetValueAsObject(AIC_Enemy->PlayerKey, actor);
		}
		else {
			// if no stimuli clear out playerkey
			BB->ClearValue(AIC_Enemy->PlayerKey);
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("BaseEnemy failed AIC->GetBlackboardComponent()"));
	}
}

void ABaseEnemy::UpdateBlackboardHealth(float health)
{
	if (UBlackboardComponent* BB = AIC_Enemy->GetBlackboardComponent()) {
		BB->SetValueAsFloat(HealthKey, health);
	}
}

void ABaseEnemy::HandleHurt(float health)
{
	Super::HandleHurt(health);
	UpdateBlackboardHealth(health);
}

void ABaseEnemy::HandleDeath()
{
	if (AIC_Enemy) {
		AIC_Enemy->StopMovement();
		AIC_Enemy->ClearFocus(EAIFocusPriority::Gameplay);
		DetachFromControllerPendingDestroy();
	}
	Super::HandleDeath();
}

void ABaseEnemy::HandleMontageFinished(UAnimMontage* montage, bool bInterrupted)
{
	APawn* pawn = Cast<APawn>(this);
	FAIMessage::Send(pawn, FAIMessage(ActionFinished, this, true));
	isAttacking = false;
	bCanQueueNextAttack = true;
}

void ABaseEnemy::DetermineAttack()
{
	EnemyLightAttack();
}

void ABaseEnemy::EnemyLightAttack()
{
	if (IsValid(LightAttackMontage)) {
		isAttacking = true;
		bCanQueueNextAttack = false;
		PlayAnimMontage(LightAttackMontage, 1.f, FName("Default"));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("BaseEnemy !LightAttackMontage"));
	}
}

void ABaseEnemy::EnemyHeavyAttack()
{
}
