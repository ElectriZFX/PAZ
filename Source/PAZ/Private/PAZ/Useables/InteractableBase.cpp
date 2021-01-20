// Project made by ElectriZ


#include "PAZ/Public/PAZ/Useables/InteractableBase.h"
#include "PAZ/Public/Player/CharacterBase.h"

// Sets default values
AInteractableBase::AInteractableBase()
{
	UIMessage = "Press and hold F to purchase";
}

// Called when the game starts or when spawned
void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();
	
}

FString AInteractableBase::GetUIMessage()
{
	return UIMessage;
}

void AInteractableBase::Use(class ACharacterBase* Player)
{

}