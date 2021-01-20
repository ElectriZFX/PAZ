// Project made by ElectriZ


#include "PAZ/Public/PAZ/Game/PAZGameState.h"

APAZGameState::APAZGameState()
{
	RoundNumber = 1;
	ZombiesOnMap = 0;
}

uint16 APAZGameState::GetRoundNumber()
{
	return RoundNumber;
}

void APAZGameState::IncrementRoundNumber()
{
	++RoundNumber;
}
