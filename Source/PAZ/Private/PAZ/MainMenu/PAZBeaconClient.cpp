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

void APAZBeaconClient::SendChatMessage(const FText& ChatMessage)
{
	Server_SendChatMessage(ChatMessage);
}

bool APAZBeaconClient::Server_SendChatMessage_Validate(const FText& ChatMessage)
{
	return true;
}

void APAZBeaconClient::Server_SendChatMessage_Implementation(const FText& ChatMessage)
{
	FString Message = PlayerName + ": " + ChatMessage.ToString();
	UE_LOG(LogTemp, Warning, TEXT("Chat: %s"), *Message); // Print message "Server"

	if (APAZBeaconHostObject* Host = Cast<APAZBeaconHostObject>(BeaconOwner))
	{
		Host->SendChatToLobby(FText::FromString(Message));
	}
}

void APAZBeaconClient::Client_OnChatMessageReceived_Implementation(const FText& ChatMessage)
{
	FOnChatReceived.Broadcast(ChatMessage);
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

void APAZBeaconClient::SetPlayerName(const FString& NewPlayerName)
{
	PlayerName = NewPlayerName;
}

FString APAZBeaconClient::GetPlayerName()
{
	return PlayerName;
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

