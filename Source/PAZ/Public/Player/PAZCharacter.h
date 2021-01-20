// Project made by ElectriZ

#pragma once

#include "CoreMinimal.h"
#include "Player/CharacterBase.h"
#include "PAZCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PAZ_API APAZCharacter : public ACharacterBase
{
	GENERATED_BODY()
public:
	APAZCharacter();

protected:
	FTimerHandle TInteractTimerHandle;

protected:
	void Interact();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
