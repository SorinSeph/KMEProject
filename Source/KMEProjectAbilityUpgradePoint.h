// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InterfaceUse.h"
#include "KMEProjectAbilityUpgradePoint.generated.h"

UENUM(BlueprintType)
enum EAbilityUpgrade
{
	Damage,
	Movementspeed,
	Healing
};



UCLASS()
class KMEProject_API AKMEProjectAbilityUpgradePoint : public AActor, public IInterfaceUse
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKMEProjectAbilityUpgradePoint();

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* ActorMesh;

	UPROPERTY(EditDefaultsOnly, Category = Collision)
	class UBoxComponent* ActorCollision;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MyCategory")
	bool Use();
	virtual bool Use_Implementation() override;

protected:

	class AKMEProjectCharacter* MyPawn;

	class AKMEProjectPlayerController* MyPC;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void StartOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
