// Copyright Epic Games, Inc. All Rights Reserved.

#include "PAZGameMode.h"
#include "PAZHUD.h"
#include "PAZ/Public/Player/CharacterBase.h"
#include "UObject/ConstructorHelpers.h"

APAZGameMode::APAZGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/BlueprintClasses/Player/BP_CharacterBase.BP_CharacterBase_C"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = APAZHUD::StaticClass();
}
