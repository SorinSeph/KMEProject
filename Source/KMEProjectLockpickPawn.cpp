// Fill out your copyright notice in the Description page of Project Settings.

#include "KMEProjectLockpickPawn.h"
#include "Engine.h"


// Sets default values
AKMEProjectLockpickPawn::AKMEProjectLockpickPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(false);

	LockpickCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("LockpickingCam"));

	Tumbler1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TumblerOne"));
	Tumbler1->SetupAttachment(LockpickCamera);

	Lockpick = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActualLockpick"));
	Lockpick->SetupAttachment(Tumbler1);
	Lockpick->RelativeLocation = FVector(30,0,0);

	Lock = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LockMesh"));
	Lock->SetupAttachment(LockpickCamera);

	TumblerSpawnLoc = CreateDefaultSubobject<UBillboardComponent>(TEXT("TumblerSpawnLocation"));
	TumblerSpawnLoc->SetupAttachment(Lock);

	Spring = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SpringTest"));
	Spring->SetupAttachment(LockpickCamera);
	Spring->RelativeLocation = FVector(0, 0, 0);

	LockpickID = 0;

	CurrentMousePosX = 0;
	CurrentMousePosY = 0;

	OriginalMousePosX = 0;
	OriginalMousePosY = 0;

	NumberOfTumblers = 0;

	LockpickIndex = 0;
	MorphSpeed = 0;
	TargetTime = 0;
	LockpickPosition = 0;
	CurrentTime = 0;

	bDelay = false;
	bWantsToLockpick = false;
}

// Called when the game starts or when spawned
void AKMEProjectLockpickPawn::BeginPlay()
{
	Super::BeginPlay();

	Lockpick->AttachToComponent(Tumbler1, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true), TEXT("TumblerSocket2"));
	
	MyPC = Cast<AKMEProjectPlayerController>(GetWorld()->GetFirstPlayerController());
	//MyPC->bShowMouseCursor = true;
	SpawnTumblers();

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Recovered!"));
}

void AKMEProjectLockpickPawn::StartLockpick()
{
	bWantsToLockpick = true;
	CurrentTime = GetWorld()->GetTimeSeconds();
	MorphSpeed = 1;
	TumblerRef[LockpickIndex]->TargetTime2 = GetWorld()->GetTimeSeconds() + TumblerRef[LockpickIndex]->RandomNumber;
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::SanitizeFloat(TumblerRef->TargetTime2));
}

void AKMEProjectLockpickPawn::EndLockpick()
{
	bWantsToLockpick = false;
	TumblerRef[LockpickIndex]->bCanSeed = false;
	bDelay = false;
}

// Called every frame
void AKMEProjectLockpickPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Lockpick ticking..."));

	MyPC->GetMousePosition(CurrentMousePosX, CurrentMousePosY);

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::SanitizeFloat(Lockpick->GetComponentLocation().Z));
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::SanitizeFloat(Lockpick->GetComponentLocation().Y));
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::SanitizeFloat(Lockpick->GetComponentLocation().X));

	if (CurrentMousePosX > OriginalMousePosX + 100 && LockpickIndex < NumberOfTumblers - 1)
	{
		OriginalMousePosX = CurrentMousePosX;
		//Lockpick->MoveComponent(Lockpick->SetRelativeLocation + FVector(1,0,0), Lockpick->GetComponentRotation(), false);
	//	Lockpick->SetRelativeLocation(Lockpick->Location + FVector(1,0,0));
		Lockpick->SetWorldLocation(Lockpick->GetComponentLocation() + FVector(0,10.65,0));
		LockpickIndex++;
	}

	if (CurrentMousePosX < OriginalMousePosX - 100 && LockpickIndex > 0)
	{
		OriginalMousePosX = CurrentMousePosX;
		Lockpick->SetWorldLocation(Lockpick->GetComponentLocation() + FVector(0, -10.65, 0));
		LockpickIndex--;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::FromInt(LockpickIndex));

	if (bWantsToLockpick)
	{
		//Spring->SetMorphTarget(TEXT("001"), FMath::FInterpConstantTo(MorphSpeed, 100, GetWorld()->GetDeltaSeconds(), 10));
		//Spring->SetMorphTarget(TEXT("001"), 25);
		//MorphSpeed = FMath::FInterpConstantTo(MorphSpeed, 10, GetWorld()->GetDeltaSeconds(), 1);

		if (FMath::IsNearlyEqual( GetWorld()->GetTimeSeconds(), TargetTime, 0.1f) )
		{
			bDelay = true;
			//MorphSpeed = FMath::FInterpConstantTo(MorphSpeed, FMath::FRandRange(-2, 1), GetWorld()->GetDeltaSeconds(), 1);
			//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::SanitizeFloat(MorphSpeed));
		}

		if (bDelay)
		{
			//MorphSpeed = FMath::FInterpConstantTo(0, FMath::FRandRange(-3, 1), GetWorld()->GetDeltaSeconds(), 1);
			MorphSpeed = FMath::FRandRange(-0.5f, 0.5f);
		}

		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::SanitizeFloat(MorphSpeed));

	}

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::SanitizeFloat(GetWorld()->GetTimeSeconds()));
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::SanitizeFloat(CurrentMousePosX));
    //GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::SanitizeFloat(OriginalMousePosX));
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, bWantsToLockpick ? "true" : "false");
}

void AKMEProjectLockpickPawn::SpawnTumblers()
{
	class AKMEProjectLockpickTumbler* NewTumbler = GetWorld()->SpawnActor<class AKMEProjectLockpickTumbler>(TumblerRef2[0]);
}

// Called to bind functionality to input
void AKMEProjectLockpickPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Lockpick", IE_Pressed, this, &AKMEProjectLockpickPawn::StartLockpick);
	PlayerInputComponent->BindAction("Lockpick", IE_Released, this, &AKMEProjectLockpickPawn::EndLockpick);

}

