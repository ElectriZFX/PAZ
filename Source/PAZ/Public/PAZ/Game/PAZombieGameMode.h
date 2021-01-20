// Project made by ElectriZ

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PAZombieGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PAZ_API APAZombieGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	APAZombieGameMode();

protected:
	class APAZGameState* ZombieGameState;

	bool bHasLoadedSpawnPoints;
	TArray<class APAZPlayerSpawnPoint*> PlayerSpawnPoints;
	TArray<class APAZZombieSpawnPoint*> ZombieSpawnPoints;

	UPROPERTY(EditAnywhere, Category = "PAZSettings")
		TSubclassOf<class AZombieBase> ZombieClass;

	FTimerHandle TZombieSpawnHandle;

	uint16 ZombiesRemaining;

protected:
	void CalculateZombieCount();
	void SpawnZombie();

protected:
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	void SetSpawnPoints();
};
