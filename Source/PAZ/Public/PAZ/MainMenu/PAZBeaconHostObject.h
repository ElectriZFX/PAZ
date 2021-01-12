// Project made by ElectriZ

#pragma once

#include "CoreMinimal.h"
#include "OnlineBeaconHostObject.h"
#include "PAZBeaconHostObject.generated.h"

USTRUCT(BlueprintType)
struct FPAZLobbyInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		class UTexture2D* MapImage;
	UPROPERTY(BlueprintReadOnly)
		TArray<FString> PlayerList;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHostLobbyUpdated, FPAZLobbyInfo, FOnHostLobbyUpdated);

UCLASS()
class PAZ_API APAZBeaconHostObject : public AOnlineBeaconHostObject
{
	GENERATED_BODY()
public:
	APAZBeaconHostObject();

protected:
	FPAZLobbyInfo LobbyInfo;

	UPROPERTY(BlueprintAssignable)
		FHostLobbyUpdated FOnHostLobbyUpdated;

	UFUNCTION(BlueprintCallable)
		void UpdateLobbyInfo(FPAZLobbyInfo NewLobbyInfo);

	void UpdateClientLobbyInfo();

protected:
	virtual void BeginPlay() override;

	virtual void OnClientConnected(AOnlineBeaconClient* NewClientActor, UNetConnection* ClientConnection) override;
	virtual void NotifyClientDisconnected(AOnlineBeaconClient* LeavingClientActor) override;

	UFUNCTION(BlueprintCallable)
		void ShutdownServer();
		void DisconnectAllClients();

		virtual void DisconnectClient(AOnlineBeaconClient* ClientActor) override;
};
