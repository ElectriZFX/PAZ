// Project made by ElectriZ


#include "PAZ/Public/PAZ/Game/PAZPlayerSpawnPoint.h"

APAZPlayerSpawnPoint::APAZPlayerSpawnPoint()
{
	bIsUsed = false;
}

bool APAZPlayerSpawnPoint::IsUsed()
{
	return bIsUsed;
}

void APAZPlayerSpawnPoint::SetUsed(bool Used)
{
	bIsUsed = Used;
}
