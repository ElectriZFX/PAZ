// Project made by ElectriZ


#include "PAZ/Public/PAZ/Game/PAZombieGameMode.h"
#include "PAZ/Public/PAZ/Game/PAZGameState.h"
#include "PAZ/Public/PAZ/Game/PAZPlayerSpawnPoint.h"
#include "PAZ/Public/PAZ/Game/PAZZombieSpawnPoint.h"
#include "PAZ/Public/Player/CharacterBase.h"
#include "PAZ/Public/PAZ/Zombie/ZombieBase.h"

#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

APAZombieGameMode::APAZombieGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/BlueprintClasses/Player/BP_PAZCharacter.BP_PAZCharacter_C"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	bHasLoadedSpawnPoints = false;

	ZombiesRemaining = 0;

}

void APAZombieGameMode::BeginPlay()
{
	Super::BeginPlay();

	ZombieGameState = GetGameState<APAZGameState>();
	CalculateZombieCount();

	TArray<AActor*> TempActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APAZZombieSpawnPoint::StaticClass(), TempActors);
	for (AActor* Actor : TempActors)
	{
		if (APAZZombieSpawnPoint* SpawnPoint = Cast<APAZZombieSpawnPoint>(Actor))
		{
			ZombieSpawnPoints.Add(SpawnPoint);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Zombie spawn count: %d"), ZombieSpawnPoints.Num()); //Nbr zombie spawn point

	GetWorld()->GetTimerManager().SetTimer(TZombieSpawnHandle, this, &APAZombieGameMode::SpawnZombie, 2.0f, true);
}

void APAZombieGameMode::CalculateZombieCount()
{
	if (ZombieGameState)
	{
		uint16 RoundNumber = ZombieGameState->GetRoundNumber();
		ZombiesRemaining = 5;
	}
}

void APAZombieGameMode::SetSpawnPoints() // Set spawn point in landscape
{
	TArray<AActor*> TempActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APAZPlayerSpawnPoint::StaticClass(), TempActors);
	for (AActor* Actor : TempActors)
	{
		if (APAZPlayerSpawnPoint* SpawnPoint = Cast<APAZPlayerSpawnPoint>(Actor))
		{
			PlayerSpawnPoints.Add(SpawnPoint);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Spawn point count: %d"), PlayerSpawnPoints.Num()); //Nbr spawn point
	bHasLoadedSpawnPoints = true;
}

void APAZombieGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (bHasLoadedSpawnPoints == false)
		SetSpawnPoints();

	for (APAZPlayerSpawnPoint* SpawnPoint : PlayerSpawnPoints)
	{
		if (!SpawnPoint->IsUsed())
		{
			FVector SpawnLocation = SpawnPoint->GetActorLocation();
			if (APawn* Pawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, SpawnLocation, FRotator::ZeroRotator))
			{
				UE_LOG(LogTemp, Warning, TEXT("Spawned pawn to possess"));
				NewPlayer->Possess(Pawn);
				SpawnPoint->SetUsed(true);
				return;
			}
		}
	}
}

void APAZombieGameMode::SpawnZombie()
{
	if (ZombiesRemaining > 0)
	{
		int RandomIndex = FMath::RandRange(0, ZombieSpawnPoints.Num() - 1);

		if (APAZZombieSpawnPoint* SpawnPoint = ZombieSpawnPoints[RandomIndex])
		{
			FVector Loc = SpawnPoint->GetActorLocation();
			FRotator Rot = SpawnPoint->GetActorRotation();

			if (AZombieBase* Zombie = GetWorld()->SpawnActor<AZombieBase>(ZombieClass, Loc, Rot))
			{
				UE_LOG(LogTemp, Warning, TEXT("Spawning zombie"));
				--ZombiesRemaining;
			}
		}
	}
	else
	{
		GetWorld()->GetTimerManager().PauseTimer(TZombieSpawnHandle);
	}
}