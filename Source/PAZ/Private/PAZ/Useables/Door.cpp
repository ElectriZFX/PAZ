// Project made by ElectriZ


#include "PAZ/Public/PAZ/Useables/Door.h"

#include "Components/StaticMeshComponent.h"

ADoor::ADoor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");

	RootComponent = MeshComp;
	Cost = 500;
}