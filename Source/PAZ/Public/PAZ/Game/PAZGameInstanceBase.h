// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PAZGameInstanceBase.generated.h"


USTRUCT(BlueprintType)
struct FMapInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MapURL;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MapName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MapDescription;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UTexture2D* MapImage;
};

UCLASS()
class PAZ_API UPAZGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()
public:
	UPAZGameInstanceBase();

protected:
	UFUNCTION(BlueprintCallable)
		void GoToMap(FString MAPURL);
};
