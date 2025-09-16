// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTT_EnemyAttack.h"
#include "AI/AIC_Enemy.h"
#include "Interfaces/EnemyInterface.h"

UBTT_EnemyAttack::UBTT_EnemyAttack()
	:FinishMessage("ActionFinished")
{
	NodeName = "BTT_EnemyAttack";
}

EBTNodeResult::Type UBTT_EnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	IEnemyInterface* EnemyInterface = Cast<IEnemyInterface>(OwnerComp.GetAIOwner()->GetPawn());
	if (EnemyInterface) {
		EnemyInterface->DetermineAttack();
		WaitForMessage(OwnerComp, FinishMessage);
		return EBTNodeResult::InProgress;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No EnemyInterface for BTT_EnemyAttack"));
	}
	return EBTNodeResult::Failed;
}
