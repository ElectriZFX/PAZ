// Project made by ElectriZ

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PAZGameState.generated.h"

/**
 * 
 */
UCLASS()
class PAZ_API APAZGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	APAZGameState();

protected:
	uint16 RoundNumber;
	uint8 ZombiesOnMap;

public:
	uint16 GetRoundNumber();
	void IncrementRoundNumber();
};
