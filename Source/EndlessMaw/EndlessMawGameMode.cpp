// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessMawGameMode.h"
#include "EndlessMawCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEndlessMawGameMode::AEndlessMawGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
