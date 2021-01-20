// Project made by ElectriZ

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "PAZPlayerSpawnPoint.generated.h"

/**
 * 
 */
UCLASS()
class PAZ_API APAZPlayerSpawnPoint : public ATargetPoint
{
	GENERATED_BODY()
public:
	APAZPlayerSpawnPoint();

protected:
	bool bIsUsed;

public:
	bool IsUsed();
	void SetUsed(bool Used);
};
