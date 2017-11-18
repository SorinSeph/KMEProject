// Fill out your copyright notice in the Description page of Project Settings.

#include "KMEProjectLockpickObject.h"


// Sets default values
AKMEProjectLockpickObject::AKMEProjectLockpickObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LPMesh"));

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(Mesh);

	LockpickID = 0;
}

// Called when the game starts or when spawned
void AKMEProjectLockpickObject::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AKMEProjectLockpickObject::StartOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AKMEProjectLockpickObject::EndOverlap);
	
}

// Called every frame
void AKMEProjectLockpickObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKMEProjectLockpickObject::StartOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetActorTickEnabled(true);
	//bIsOverlapping = true;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Collision started"));
	AKMEProjectCharacter* MyPawn = Cast<AKMEProjectCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	MyPawn->CharLockpickID = LockpickID;
}

void AKMEProjectLockpickObject::EndOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SetActorTickEnabled(false);
	//bIsOverlapping = false;
	//MyPawn->VerticalImpactPoint = 0;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Collision ended"));
}
