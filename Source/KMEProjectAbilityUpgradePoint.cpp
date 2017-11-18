// Fill out your copyright notice in the Description page of Project Settings.

#include "KMEProjectAbilityUpgradePoint.h"
#include "KMEProjectCharacter.h"
#include "KMEProjectPlayerController.h"
#include "Engine.h"
#include "Components/BoxComponent.h"


// Sets default values
AKMEProjectAbilityUpgradePoint::AKMEProjectAbilityUpgradePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshActor"));
	RootComponent = ActorMesh;

	ActorCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	ActorCollision->SetupAttachment(ActorMesh);
}

// Called when the game starts or when spawned
void AKMEProjectAbilityUpgradePoint::BeginPlay()
{
	Super::BeginPlay();
	ActorCollision->OnComponentBeginOverlap.AddDynamic(this, &AKMEProjectAbilityUpgradePoint::StartOverlap);
	ActorCollision->OnComponentEndOverlap.AddDynamic(this, &AKMEProjectAbilityUpgradePoint::EndOverlap);
}

bool AKMEProjectAbilityUpgradePoint::Use_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Interface called from Ability Upgrade Point"));
	return true;
}

void AKMEProjectAbilityUpgradePoint::StartOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetActorTickEnabled(true);
	MyPawn = Cast<AKMEProjectCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	MyPC = Cast<AKMEProjectPlayerController>(GetWorld()->GetFirstPlayerController());
}

void AKMEProjectAbilityUpgradePoint::EndOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SetActorTickEnabled(false);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("End overlap"));
}

// Called every frame
void AKMEProjectAbilityUpgradePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (MyPawn && MyPC)
	{
		if (MyPawn->bWantsToUse)
		{
			MyPC->ToggleUpgradeMenu();
			MyPawn->OnUseFinished();
		}
	}

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Tick"));
}

