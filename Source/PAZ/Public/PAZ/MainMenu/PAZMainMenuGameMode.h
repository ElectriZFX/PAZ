// Project made by ElectriZ

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PAZMainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PAZ_API APAZMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	APAZMainMenuGameMode();

protected:
	UFUNCTION(BlueprintCallable)
		bool CreateHostBeacon();

	class APAZBeaconHostObject* HostObject;

	class AOnlineBeaconHost* Host;

	UFUNCTION(BlueprintCallable)
		class APAZBeaconHostObject* GetBeaconHost();

};
