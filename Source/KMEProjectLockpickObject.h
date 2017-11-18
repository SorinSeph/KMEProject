// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "KMEProjectCharacter.h"
#include "GameFramework/Actor.h"
#include "KMEProjectLockpickObject.generated.h"

UCLASS()
class KMEPROJECT_API AKMEProjectLockpickObject : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
	class UBoxComponent* BoxCollision;

	UFUNCTION()
	void StartOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
public:	
	// Sets default values for this actor's properties
	AKMEProjectLockpickObject();

	UPROPERTY(EditAnywhere, Category = Gameplay)
	int32 LockpickID;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
