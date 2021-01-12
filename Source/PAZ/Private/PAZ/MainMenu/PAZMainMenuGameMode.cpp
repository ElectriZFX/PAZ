// Project made by ElectriZ


#include "PAZ/Public/PAZ/MainMenu/PAZMainMenuGameMode.h"
#include "PAZ/Public/PAZ/MainMenu/PAZBeaconHostObject.h"

#include "OnlineBeaconHost.h"

APAZMainMenuGameMode::APAZMainMenuGameMode()
{
	HostObject = nullptr;
	Host = nullptr;
}

bool APAZMainMenuGameMode::CreateHostBeacon()
{
	Host = GetWorld()->SpawnActor<AOnlineBeaconHost>(AOnlineBeaconHost::StaticClass());
	if (Host)
	{
		UE_LOG(LogTemp, Warning, TEXT("SPAWNED AOnlineBeaconHost"));//Check if AOnlineBeaconHost spawned
		if (Host->InitHost())
		{
			Host->PauseBeaconRequests(false);
			UE_LOG(LogTemp, Warning, TEXT("Init HOST"));  // Check if Init Host ?
			HostObject = GetWorld()->SpawnActor<APAZBeaconHostObject>(APAZBeaconHostObject::StaticClass());
			if (HostObject)
			{
				UE_LOG(LogTemp, Warning, TEXT("SPAWN HOST OBJECT")); // Check if hostobject spawn
				Host->RegisterHost(HostObject);
				return true;
			}
		}
	}
	return false;
}

APAZBeaconHostObject* APAZMainMenuGameMode::GetBeaconHost()
{
	return HostObject;
}
