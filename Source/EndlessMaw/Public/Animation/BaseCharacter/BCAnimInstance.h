// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BCAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSMAW_API UBCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PreviewWindowUpdate();
	virtual void PreviewWindowUpdate_Implementation();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defaults")
	float Velocity = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defaults")
	float Direction = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName SlotName = "Action";
};
