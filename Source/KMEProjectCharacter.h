// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KMEProjectLockpickPawn.h"
#include "KMEProjectWeapon.h"
#include "InterfaceUse.h"
#include "KMEProjectCharacter.generated.h"

class UInputComponent;


UCLASS(config=Game)
class AKMEProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	/** Gun mesh: VR view (attached to the VR controller directly, no arm, just the actual gun) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* VR_Gun;

	/** Location on VR gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* VR_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	/** Motion controller (right hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* R_MotionController;

	/** Motion controller (left hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* L_MotionController;

public:
	AKMEProjectCharacter();

protected:
	virtual void BeginPlay();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Reference)
	//class AKMEProjectLockpickPawn* LockpickPawn;
	UPROPERTY(EditDefaultsOnly, Category = Camera)
	TSubclassOf<UCameraShake> WalkingCameraShake;

	UPROPERTY(EditDefaultsOnly, Category = Camera)
	TSubclassOf<UCameraShake> SprintingCameraShake;

	UPROPERTY(EditAnywhere, Category = Reference)
	TArray<class AKMEProjectLockpickPawn*> LockpickPawnRef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
	TArray<class AKMEProjectWeapon*> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
	TSubclassOf<class AKMEProjectWeapon> WeaponSpawn;

	//UPROPERTY(VisibleAnywhere, Category = Reference)
	//;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Upgrade)
	int32 BonusDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Upgrade)
	int32 BonusMS;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Upgrade)
	int32 BonusJumpTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Upgrade)
	int32 BonusHealing;

	UPROPERTY()
	uint8 bIsTargeting : 1;

public:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	class USkeletalMeshComponent* FPSHands;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
	AKMEProjectWeapon *CurrentWeapon;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AKMEProjectProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint32 bUsingMotionControllers : 1;

	UFUNCTION(BlueprintCallable, Category = "Game|Weapon")
	bool IsTargeting() const;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	int32 GetCurrentClip();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 CharCurrentClip;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gameplay)
	int32 LevelUpPoints;

	void OnUse();

	void OnUseFinished();

	bool bWantsToUse;

	virtual void Tick(float DeltaTime) override;

	int32 CharLockpickID;

protected:

	class AKMEProjectPlayerController* MyPC;

	void InitDelay();

	float TimeDelay;
	/** Fires a projectile. */
	void OnFire();

	void StopFire();

	void Reload();

	void GiveDefaultWeapon();

	void UpgradeAbility();

	void SprintStart();

	void SprintStop();

	bool bIsRunning;

	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	void EnterLockpick();

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

