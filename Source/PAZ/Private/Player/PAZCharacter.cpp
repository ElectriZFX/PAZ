// Project made by ElectriZ


#include "PAZ/Public/Player/PAZCharacter.h"

#include "TimerManager.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"

APAZCharacter::APAZCharacter()
{

}

void APAZCharacter::BeginPlay()
{
	Super::BeginPlay();

	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	GetWorld()->GetTimerManager().SetTimer(TInteractTimerHandle, this, &APAZCharacter::Interact, 1.0f, true);
}

void APAZCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APAZCharacter::OnFire);

	PlayerInputComponent->BindAxis("MoveForward", this, &APAZCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APAZCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APAZCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APAZCharacter::LookUpAtRate);

}

void APAZCharacter::Interact()
{
	FVector Start = GetFirstPersonCameraComponent()->GetComponentLocation();
	FVector Rot = GetFirstPersonCameraComponent()->GetComponentRotation().Vector();
	FVector End = Start + Rot * 500.0f;

	FHitResult HitResult;
	FCollisionObjectQueryParams CollisionQuery;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByObjectType(OUT HitResult, Start, End, CollisionQuery, CollisionParams);

	if (HitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("HIT ACTOR %s"), *HitResult.GetActor()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("did not hit anything important"));
	}
}