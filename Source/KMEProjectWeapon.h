// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KMEProjectInventoryItem.h"
#include "KMEProjectCharacter.h"
#include "KMEProjectPlayerController.h"
#include "KMEProjectWeapon.generated.h"

/**
 * 
 */

class AKMEProjectCharacter;

#define TRACE_WEAPON ECC_GameTraceChannel1

namespace EWeaponState
{
	enum State
	{
		Idle,
		Walking,
		Sprinting,
		Aiming,
		Reloading
	};
}

UENUM(BlueprintType)
namespace EWeaponProjectile
{
	enum ProjectileType
	{
		EBullet			UMETA(DisplayName = "Bullet"),
		ESpread			UMETA(DisplayName = "Spread"),
		ESpray			UMETA(DisplayName = "Spray"),
	};
}

/*(UENUM(BlueprintType)
enum WeaponType
{
	Knife, 
	Gun1,
	Gun2,
	Shotgun1,
	Shotgun2,
	Rifle1

};*/


USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	int32 MaxClip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	float TimeBetweenShots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	int32 ShotCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	float WeaponRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	float WeaponSpread;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	float WeaponAimingSpread;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	float WeaponShots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	UTexture2D* SplashArt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	int32 Priority;
};

UCLASS()
class KMEPROJECT_API AKMEProjectWeapon : public AKMEProjectInventoryItem
{
	GENERATED_BODY()

	UFUNCTION()
	void AltFire();

	UFUNCTION()
	void StopAltFire();

	UFUNCTION()
	void InstantFire();

	UFUNCTION()
	void StartDelayFire();

	UFUNCTION()
	void CheckDelay();

	UFUNCTION()
	void StopDelayFire();

	UFUNCTION()
	AKMEProjectWeapon* GetWeapon() const;

	bool bWantsToFire;

	UPROPERTY()
	AKMEProjectWeapon* Weapon;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	class USoundBase* FireSound;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	int32 Damage;

	UPROPERTY(EditDefaultsOnly, Category = Attachment)
	FName SecondarySocket;

public:
	// Sets default values for this actor's properties
	AKMEProjectWeapon();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	class USkeletalMeshComponent *WeaponMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	class UBoxComponent *WeaponBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	FWeaponData WeaponConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Config)
	TEnumAsByte<EWeaponProjectile::ProjectileType> ProjectileType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	class UAnimMontage* AimAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	class UAnimMontage* UnequipAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	class UAnimMontage* ReloadAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	int32 CurrentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	int32 CurrentClip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Reference)
	class AKMEProjectCharacter *MyPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Reference)
	class AKMEProjectCharacter *MyPawn2;

	UPROPERTY(EditDefaultsOnly, Category = Effects)
	UParticleSystem* MuzzleFX;

	UPROPERTY()
	UParticleSystemComponent* MuzzlePSC;

	UPROPERTY(EditDefaultsOnly, Category = Effects)
	FName MuzzleAttachPoint;

	UFUNCTION()
	void Fire();

	UFUNCTION()
	void Stop();

	void Reload();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetOwningPawn(AKMEProjectCharacter* NewOwner);

	void AttachToPlayer();

	void DettachFromPlayer();

	void AttachToPlayerSecondarySocket();

	void DettachFromPlayerAndHide();

	void PlayUnequipAnim();

	bool bCanAttach;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	float TEST;
protected:

	UFUNCTION()
	void PlayReloadAnim();

	virtual void Tick(float DeltaTime) override;

	float LastFireTime;

	uint32 bRefiring;

	EWeaponState::State CurrentState;

	FTimerHandle Handle_Fire;

	FTimerHandle Handle_AltFire;

	FTimerHandle Handle_DelayFire;

	void AltFirePause();

	void AltFireResume();

	int DetermineSpread();

	bool bDelay = false;

	bool bCanAim;

	class AKMEProjectPlayerController *Controller;

	void DealDamage();

	FHitResult WeaponTrace(const FVector &TraceFrom, const FVector &TraceTo) const;

	void ProcessInstantHit(const FHitResult &Impact, const FVector &Origin, const FVector &ShootDir, int32 RandomSeed, float ReticleSpread); 
};