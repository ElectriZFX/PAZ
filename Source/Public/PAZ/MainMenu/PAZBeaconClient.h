// Project made by ElectriZ

#pragma once

#include "CoreMinimal.h"
#include "OnlineBeaconClient.h"
#include "PAZ/Public/PAZ/MainMenu/PAZBeaconHostObject.h"
#include "PAZBeaconClient.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FConnectSuccess, bool, OnConnected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDisconnected);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLobbyUpdated, FPAZLobbyInfo, FOnLobbyUpdated);

UCLASS()
class PAZ_API APAZBeaconClient : public AOnlineBeaconClient
{
	GENERATED_BODY()
public:
	APAZBeaconClient();

protected:
	UPROPERTY(BlueprintAssignable)
		FConnectSuccess FOnConnected;
	UPROPERTY(BlueprintAssignable)
		FDisconnected FOnDisconnected;

	UPROPERTY(BlueprintAssignable)
		FLobbyUpdated FOnLobbyUpdated;

	uint8 PlayerIndex;

protected:
	UFUNCTION(BlueprintCallable)
		bool ConnectToServer(const FString& Address);

	UFUNCTION(BlueprintCallable)
		void LeaveLobby();

	virtual void OnFailure() override;
	virtual void OnConnected() override;

public:
	UFUNCTION(Client, Reliable)
		void Client_OnDisconnected();
	virtual void Client_OnDisconnected_Implementation();

	UFUNCTION(Client, Reliable)
		void Client_OnLobbyUpdated(FPAZLobbyInfo LobbyInfo);
	void Client_OnLobbyUpdated_Implementation(FPAZLobbyInfo LobbyInfo);

	void SetPlayerIndex(uint8 Index);

	uint8 GetPlayerIndex();
};
