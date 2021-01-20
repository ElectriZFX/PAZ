// Project made by ElectriZ

#pragma once

#include "CoreMinimal.h"
#include "OnlineBeaconClient.h"
#include "PAZ/Public/PAZ/MainMenu/PAZBeaconHostObject.h"
#include "PAZBeaconClient.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FConnectSuccess, bool, OnConnected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDisconnected);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLobbyUpdated, FPAZLobbyInfo, FOnLobbyUpdated);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChatReceived, const FText&, FOnChatReceived);

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

	UPROPERTY(BlueprintAssignable)
		FChatReceived FOnChatReceived;

	uint8 PlayerIndex;
	FString PlayerName;

protected:
	UFUNCTION(BlueprintCallable)
		bool ConnectToServer(const FString& Address);

	UFUNCTION(BlueprintCallable)
		void LeaveLobby();

	virtual void OnFailure() override;
	virtual void OnConnected() override;

protected:
	UFUNCTION(BlueprintCallable)
		void SendChatMessage(const FText& ChatMessage);

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_SendChatMessage(const FText& ChatMessage);
	bool Server_SendChatMessage_Validate(const FText& ChatMessage);
	void Server_SendChatMessage_Implementation(const FText& ChatMessage);

public:
	UFUNCTION(Client, Reliable)
		void Client_OnDisconnected();
	virtual void Client_OnDisconnected_Implementation();

	UFUNCTION(Client, Reliable)
		void Client_OnLobbyUpdated(FPAZLobbyInfo LobbyInfo);
	void Client_OnLobbyUpdated_Implementation(FPAZLobbyInfo LobbyInfo);

	UFUNCTION(Client, Reliable)
		void Client_OnChatMessageReceived(const FText& ChatMessage);
	void Client_OnChatMessageReceived_Implementation(const FText& ChatMessage);

	void SetPlayerIndex(uint8 Index);
	uint8 GetPlayerIndex();

	void SetPlayerName(const FString& NewPlayerName);
	FString GetPlayerName();
};
