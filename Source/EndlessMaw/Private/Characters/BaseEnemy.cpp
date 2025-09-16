// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Animation/BaseCharacter/BCAnimInstance.h"
#include "AI/AIC_Enemy.h"

ABaseEnemy::ABaseEnemy()
	:HealthKey("Health")
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ABaseEnemy::BeginPlay()
{
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
		AnimInstance->OnDeathEnded.AddDynamic(this, &ABaseEnemy::HandleDeath);
	}
	UpdateBlackboardHealth(1.f);
}

void ABaseEnemy::HandlePerception(AActor* actor, FAIStimulus stimulus)
{
	// check our blackboard is there
	if (UBlackboardComponent* BB = AIC_Enemy->GetBlackboardComponent()) {
		if (stimulus.WasSuccessfullySensed()) {
			// if we sensed it: broadcast that and set our playerkey to the actor
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
	Destroy();
}

void ABaseEnemy::DetermineAttack()
{
}

void ABaseEnemy::EnemyLightAttack()
{
}

void ABaseEnemy::EnemyHeavyAttack()
{
}
