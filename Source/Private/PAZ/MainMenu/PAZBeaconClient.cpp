// Project made by ElectriZ


#include "PAZ/Public/PAZ/MainMenu/PAZBeaconClient.h"


APAZBeaconClient::APAZBeaconClient()
{
	PlayerIndex = 0;
}

void APAZBeaconClient::OnFailure()
{
	UE_LOG(LogTemp, Warning, TEXT("Client failed to connect to host beacon"));
	FOnConnected.Broadcast(false);
}

void APAZBeaconClient::OnConnected()
{
	UE_LOG(LogTemp, Warning, TEXT("Client connected to host beacon"));
	FOnConnected.Broadcast(true);
}

void APAZBeaconClient::Client_OnDisconnected_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Disconnected"));
	FOnDisconnected.Broadcast();
}

void APAZBeaconClient::Client_OnLobbyUpdated_Implementation(FPAZLobbyInfo LobbyInfo)
{
	FOnLobbyUpdated.Broadcast(LobbyInfo);
}

void APAZBeaconClient::SetPlayerIndex(uint8 Index)
{
	PlayerIndex = Index;
}

uint8 APAZBeaconClient::GetPlayerIndex()
{
	return PlayerIndex;
}

bool APAZBeaconClient::ConnectToServer(const FString& Address)
{
	FURL Destination = FURL(nullptr, *Address, ETravelType::TRAVEL_Absolute);
	Destination.Port = 7787;
	return InitClient(Destination);
}

void APAZBeaconClient::LeaveLobby()
{
	DestroyBeacon();
}

