// Project made by ElectriZ

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableBase.generated.h"

UCLASS()
class PAZ_API AInteractableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableBase();

protected:
	UPROPERTY(EditAnywhere, Category = "PAZ Zombie Settings")
		FString UIMessage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FString GetUIMessage();
	virtual void Use(class ACharacterBase* Player);
};
