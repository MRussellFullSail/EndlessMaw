// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "ComboEnum.generated.h"

UENUM()
enum class EComboType : uint8 {
	None	UMETA(DisplayName = "None"),
	Light	UMETA(DisplayName = "Light"),
	Heavy	UMETA(DisplayName = "Heavy")
};

UCLASS()
class ENDLESSMAW_API UComboEnum : public UUserDefinedEnum
{
	GENERATED_BODY()
	
};
