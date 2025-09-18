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
	AAIC_Enemy* controller = Cast<AAIC_Enemy>(OwnerComp.GetAIOwner());
	if (!controller) {
		UE_LOG(LogTemp, Error, TEXT("BTT_EnemyAttack, No Controller"));
		return EBTNodeResult::Failed;
	}
	APawn* pawn = controller->GetPawn();
	if (!pawn) {
		UE_LOG(LogTemp, Error, TEXT("BTT_EnemyAttack, No Pawn"));
		return EBTNodeResult::Failed;
	}
	IEnemyInterface* EnemyInterface = Cast<IEnemyInterface>(OwnerComp.GetAIOwner()->GetPawn());
	if (EnemyInterface) {
		EnemyInterface->DetermineAttack();
		WaitForMessage(OwnerComp, FinishMessage);
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}
