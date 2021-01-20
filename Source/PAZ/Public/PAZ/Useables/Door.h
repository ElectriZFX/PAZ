// Project made by ElectriZ

#pragma once

#include "CoreMinimal.h"
#include "PAZ/Useables/InteractableBase.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class PAZ_API ADoor : public AInteractableBase
{
	GENERATED_BODY()
public:
	ADoor();

protected:
	UPROPERTY(EditAnywhere, Category = "PAZ Zombie Settings")
		class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, Category = "PAZ Zombie Settings")
		uint16 Cost;
};
