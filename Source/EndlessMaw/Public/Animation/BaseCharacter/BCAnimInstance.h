// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BCAnimInstance.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnimation);

UCLASS()
class ENDLESSMAW_API UBCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	// broadcasts OnDeathEnded delegate to signal end of selected dearth animation
	void DeathEnded();

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

	// sequence bases
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimSequenceBase* DeathSequence;

	// preview window debugging
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DebugDeath = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DebugHurt = false;

public:
	// animation for taking damage
	UFUNCTION(BluePrintNativeEvent, BlueprintCallable)
	void HurtAnimation();
	virtual void HurtAnimation_Implementation();

	// death animation
	UFUNCTION(BluePrintNativeEvent, BlueprintCallable)
	void DeathAnimation();
	virtual void DeathAnimation_Implementation();
	// on death ended delegate
	UPROPERTY(BlueprintAssignable)
	FOnAnimation OnDeathEnded;
};
