// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Animation/AnimMontage.h"
#include "Animation/BaseCharacter/BCAnimInstance.h"
#include "AI/AIC_Enemy.h"
#include "BrainComponent.h"


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
	//AnimInstance = Cast<UBCAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance) {
		AnimInstance->SetMoveable(true);
		AnimInstance->OnDeathEnded.AddDynamic(this, &ABaseEnemy::HandleDeath);
		AnimInstance->OnActionEnded.AddDynamic(this, &ABaseEnemy::HandleActionFinished);
		//EndMontage.BindUFunction(this, FName("HandleMontageFinished"));
		//AnimInstance->Montage_SetEndDelegate(EndMontage, LightAttackMontage);
		//AnimInstance->OnMontageEnded.AddDynamic(this, &ABaseEnemy::HandleMontageFinished);
		//EndMontage.BindLambda([&](UAnimMontage* montage, bool bInter) {
		//	UE_LOG(LogTemp, Warning, TEXT("bound lambda playing"));
		//	});
		//EndMontage.BindUObject(this, &ABaseEnemy::HandleMontageFinished);
		//AnimInstance->Montage_SetEndDelegate(EndMontage, LightAttackMontage);
		AnimInstance->OnEndOfMontage.AddDynamic(this, &ABaseEnemy::HandleMontageFinished);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("BaseEnemy, !AnimInstance"));
		Destroy();
		return;
	}
	if (EndMontage.IsBound())
		UE_LOG(LogTemp, Warning, TEXT("end is bound"));
	if (AnimInstance->OnMontageEnded.IsBound())
		UE_LOG(LogTemp, Warning, TEXT("montage ended is bound"));
	UpdateBlackboardHealth(1.f);
}

void ABaseEnemy::HandlePerception(AActor* actor, FAIStimulus stimulus)
{
	UE_LOG(LogTemp, Warning, TEXT("BaseEnemy HandlePerception"));
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

void ABaseEnemy::HandleActionFinished()
{
	UE_LOG(LogTemp, Warning, TEXT("Action Finished"));
	APawn* pawn = Cast<APawn>(this);
	
	FAIMessage::Send(pawn, FAIMessage(ActionFinished, this, true));
	isAttacking = false;
	bCanQueueNextAttack = true;
}

void ABaseEnemy::HandleMontageFinished()
{
	//UAnimMontage* montage, bool bInterrupted
	UE_LOG(LogTemp, Warning, TEXT("Montage Finished"));
	APawn* pawn = Cast<APawn>(this);
	
	FAIMessage::Send(pawn, FAIMessage(ActionFinished, this, true));
	isAttacking = false;
	bCanQueueNextAttack = true;
}

void ABaseEnemy::DetermineAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("BaseEnemy Determining Attack"));
	EnemyLightAttack();
}

void ABaseEnemy::EnemyLightAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy Light Attack"));
	if (IsValid(LightAttackMontage)) {
		PlayAnimMontage(LightAttackMontage, 1.f, FName("Default"));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("BaseEnemy !LightAttackMontage"));
	}
	if (AnimInstance->Montage_IsPlaying(LightAttackMontage)) {
		UE_LOG(LogTemp, Warning, TEXT("montage playing"));
	}
}

void ABaseEnemy::EnemyHeavyAttack()
{
}
