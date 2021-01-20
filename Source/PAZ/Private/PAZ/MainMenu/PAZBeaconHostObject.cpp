// Project made by ElectriZ


#include "PAZ/Public/PAZ/MainMenu/PAZBeaconHostObject.h"
#include "PAZ/Public/PAZ/MainMenu/PAZBeaconClient.h"
#include "PAZ/Public/PAZ/MainMenu/PAZMainMenuGameMode.h"

#include "OnlineBeaconHost.h"
#include "TimerManager.h"

APAZBeaconHostObject::APAZBeaconHostObject()
{
	ClientBeaconActorClass = APAZBeaconClient::StaticClass();
	BeaconTypeName = ClientBeaconActorClass->GetName();
}

void APAZBeaconHostObject::BeginPlay()
{
	LobbyInfo.PlayerList.Add(FString("Host"));
	GetWorld()->GetTimerManager().SetTimer(TInitialLobbyHandle, this, &APAZBeaconHostObject::InitialLobbyHandling, 0.2f, false);
}

void APAZBeaconHostObject::InitialLobbyHandling()
{
	UpdateLobbyInfo(LobbyInfo);
}

void APAZBeaconHostObject::UpdateLobbyInfo(FPAZLobbyInfo NewLobbyInfo)
{
	LobbyInfo.MapImage = NewLobbyInfo.MapImage;
	UpdateClientLobbyInfo();
	FOnHostLobbyUpdated.Broadcast(LobbyInfo);
}

void APAZBeaconHostObject::UpdateClientLobbyInfo()
{
	for (AOnlineBeaconClient* ClientBeacon : ClientActors)
	{
		if (APAZBeaconClient* Client = Cast<APAZBeaconClient>(ClientBeacon))
		{
			Client->Client_OnLobbyUpdated(LobbyInfo);
		}
	}
}

void APAZBeaconHostObject::OnClientConnected(AOnlineBeaconClient* NewClientActor, UNetConnection* ClientConnection)
{
	Super::OnClientConnected(NewClientActor, ClientConnection);

	if (NewClientActor)
	{
		FString PlayerName = FString("Player ");
		uint8 Index = LobbyInfo.PlayerList.Num();
		PlayerName.Append(FString::FromInt(Index));
		LobbyInfo.PlayerList.Add(PlayerName);

		if (APAZBeaconClient* Client = Cast<APAZBeaconClient>(NewClientActor))
		{
			Client->SetPlayerIndex(Index);
			Client->SetPlayerName(PlayerName);
		}

		UE_LOG(LogTemp, Warning, TEXT("Connected Client Valid"));
		FOnHostLobbyUpdated.Broadcast(LobbyInfo);
		UpdateClientLobbyInfo();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Connected Client Invalid"));
	}
}

void APAZBeaconHostObject::NotifyClientDisconnected(AOnlineBeaconClient* LeavingClientActor)
{
	Super::NotifyClientDisconnected(LeavingClientActor);

	UE_LOG(LogTemp, Warning, TEXT("Client has Disconnected")); //Notif client disconnect
	if (APAZBeaconClient* Client = Cast<APAZBeaconClient>(LeavingClientActor))
	{
		uint8 Index = Client->GetPlayerIndex();
		LobbyInfo.PlayerList.RemoveAt(Index);
	}

	FOnHostLobbyUpdated.Broadcast(LobbyInfo);
	UpdateClientLobbyInfo();
}

void APAZBeaconHostObject::ShutdownServer()
{
	DisconnectAllClients();
	if (AOnlineBeaconHost* Host = Cast<AOnlineBeaconHost>(GetOwner()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Destroying host beacon"));
		Host->UnregisterHost(BeaconTypeName);
		Host->DestroyBeacon();
	}
}

void APAZBeaconHostObject::DisconnectAllClients()
{
	UE_LOG(LogTemp, Warning, TEXT("Disconnecting all clients"));
	for (AOnlineBeaconClient* Client : ClientActors)
	{
		if (Client)
			DisconnectClient(Client);
	}
}

void APAZBeaconHostObject::DisconnectClient(AOnlineBeaconClient* ClientActor)
{
	AOnlineBeaconHost* BeaconHost = Cast<AOnlineBeaconHost>(GetOwner());
	if (BeaconHost)
	{
		if (APAZBeaconClient* Client = Cast<APAZBeaconClient>(ClientActor))
		{
			UE_LOG(LogTemp, Warning, TEXT("Disconnecting clients %s"), *ClientActor->GetName());
			Client->Client_OnDisconnected();
		}
		BeaconHost->DisconnectClient(ClientActor);
	}
}

void APAZBeaconHostObject::SendChatToLobby(const FText& ChatMessage)
{
	FOnHostChatReceived.Broadcast(ChatMessage);

	for (AOnlineBeaconClient* ClientBeacon : ClientActors)
	{
		if (APAZBeaconClient* Client = Cast<APAZBeaconClient>(ClientBeacon))
		{
			Client->Client_OnChatMessageReceived(ChatMessage);
		}
	}
}
