// Fill out your copyright notice in the Description page of Project Settings.


#include "PAZ/Public/PAZ/Game/PAZGameInstanceBase.h"

#include "Engine/World.h"

UPAZGameInstanceBase::UPAZGameInstanceBase()
{

}

void UPAZGameInstanceBase::GoToMap(FString MAPURL)
{
	GetWorld()->ServerTravel(MAPURL);
}
