// Fill out your copyright notice in the Description page of Project Settings.

#include "KMEProjectWeapon.h"


AKMEProjectWeapon::AKMEProjectWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PhysicalMesh"));
	RootComponent = WeaponMesh;
	//WeaponMesh->RelativeLocation = FVector(0, 0, 0);

	WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	WeaponBox->SetupAttachment(WeaponMesh);

	LastFireTime = 0.0f;
	bCanAim = false;
	bCanAttach = false;
	TEST = 0;
}

void AKMEProjectWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

//	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::SanitizeFloat(TEST));
}

void AKMEProjectWeapon::SetOwningPawn(AKMEProjectCharacter * NewOwner)
{
	if (MyPawn != NewOwner)
	{
		Instigator = NewOwner;
		MyPawn = NewOwner;
	}
}

// Called when the game starts or when spawned
void AKMEProjectWeapon::BeginPlay()
{
	Super::BeginPlay();

	//AttachToPlayer();
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, SocketToAttach.ToString());
}

void AKMEProjectWeapon::AttachToPlayer()
{
	if (MyPawn)
	{

		//	UCameraComponent *Character = MyPawn->GetFirstPersonCameraComponent();
		WeaponMesh->SetHiddenInGame(false);
		WeaponMesh->AttachToComponent(MyPawn->FPSHands, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), PrimarySocket);
	}
}

void AKMEProjectWeapon::DettachFromPlayer()
{
	if (MyPawn)
	{
		WeaponMesh->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
		//WeaponMesh->SetHiddenInGame(true);
	}
}

void AKMEProjectWeapon::AttachToPlayerSecondarySocket()
{
	WeaponMesh->SetHiddenInGame(false);
	WeaponMesh->AttachToComponent(MyPawn->FPSHands, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), SecondarySocket);
}

void AKMEProjectWeapon::DettachFromPlayerAndHide()
{
	WeaponMesh->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	WeaponMesh->SetHiddenInGame(true);
}

void AKMEProjectWeapon::PlayReloadAnim()
{

}

void AKMEProjectWeapon::PlayUnequipAnim()
{
	if (UnequipAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = WeaponMesh->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(UnequipAnimation);
		}
	}
}

void AKMEProjectWeapon::Fire()
{
	bWantsToFire = true;

	WeaponMesh->GetSocketLocation(MuzzleAttachPoint);
	if (MuzzleFX)
	{
		if (MuzzlePSC == NULL)
		{
			MuzzlePSC = UGameplayStatics::SpawnEmitterAttached(MuzzleFX, WeaponMesh, MuzzleAttachPoint);
			MuzzlePSC->ActivateSystem(true);
		}
	}

	if (ProjectileType == EWeaponProjectile::EBullet)
	{
		if ((CurrentAmmo > 0) && (bWantsToFire))
		{
			InstantFire();
		}
	}

	if (ProjectileType == EWeaponProjectile::ESpread)
	{
		if ((CurrentAmmo > 0) && (!bDelay))
		{
			for (int32 i = 0; i < WeaponConfig.WeaponShots; i++)
			{
				InstantFire();
				bDelay = true;
				StartDelayFire();
			}
		}
	}

	if (ProjectileType == EWeaponProjectile::ESpray)
	{
		if ((CurrentAmmo > 0) && (bWantsToFire))// && MyPawn && MyPawn->IsLocallyControlled())
		{
			InstantFire();
			GetWorldTimerManager().SetTimer(Handle_Fire, this, &AKMEProjectWeapon::Fire, WeaponConfig.TimeBetweenShots, false);
		}
	}
}

void AKMEProjectWeapon::Stop()
{
	GetWorldTimerManager().ClearTimer(Handle_Fire);
	if (MuzzlePSC != NULL)
	{
		MuzzlePSC->DeactivateSystem();
		MuzzlePSC = NULL;
	}
}

void AKMEProjectWeapon::CheckDelay()
{
bDelay = false;
GetWorldTimerManager().ClearTimer(Handle_DelayFire);
}

void AKMEProjectWeapon::StartDelayFire()
{
	if (bDelay)
	{
		GetWorldTimerManager().SetTimer(Handle_DelayFire, this, &AKMEProjectWeapon::StopDelayFire, WeaponConfig.TimeBetweenShots, false);
	}
}

void AKMEProjectWeapon::StopDelayFire()
{
	bDelay = false;
	GetWorldTimerManager().ClearTimer(Handle_DelayFire);
}

void AKMEProjectWeapon::AltFire()
{/*
 if (AimAnimation != NULL)
 {
 // Get the animation object for the arms mesh
 UAnimInstance* AnimInstance = WeaponMesh->GetAnimInstance();
 if (AnimInstance != NULL)
 {
 AnimInstance->Montage_Play(AimAnimation);
 }
 /*GetWorldTimerManager().SetTimer(Handle_AltFire, this, &AKMEProjectWeapon::AltFirePause, 0.5, false);
 if (bCanAim)
 {
 AnimInstance->Montage_Pause(AimAnimation);
 }
 }
 }
 */
}

void AKMEProjectWeapon::AltFirePause()
{
	bCanAim = false;
}

void AKMEProjectWeapon::AltFireResume()
{

}

void AKMEProjectWeapon::StopAltFire()
{
	if (AimAnimation != NULL)
	{
		UAnimInstance* AnimInstance = WeaponMesh->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Stop(0.2f, AimAnimation);
			GetWorldTimerManager().ClearTimer(Handle_AltFire);
		}

	}
}

void AKMEProjectWeapon::Reload()
{

}

void AKMEProjectWeapon::InstantFire()
{
	class APlayerController *PlC = MyPawn ? Cast<APlayerController>(MyPawn->GetController()) : NULL;

	if (PlC && PlC->IsLocalPlayerController())
	{
		FVector CamLoc;
		FRotator CamRot;


		PlC->GetPlayerViewPoint(CamLoc, CamRot);
		const FVector StartTrace = CamLoc; // trace start is the camera location
		const FVector AimDir = CamRot.Vector();
		const int32 RandomSeed = FMath::Rand();
		FRandomStream WeaponRandomStream(RandomSeed);
		//const float CurrentSpread = WeaponConfig.WeaponSpread;
		const float CurrentSpread = DetermineSpread();
		//const float SpreadCone = FMath::DegreesToRadians(WeaponConfig.WeaponSpread * 0.5);
		const float SpreadCone = FMath::DegreesToRadians(CurrentSpread * 0.5);
		//const FVector AimDir = WeaponMesh->GetSocketRotation("MF").Vector(); 
		//const FVector StartTrace = WeaponMesh->GetSocketLocation("MF");
		const FVector ShootDir = WeaponRandomStream.VRandCone(AimDir, SpreadCone, SpreadCone);
		const FVector EndTrace = StartTrace + ShootDir * WeaponConfig.WeaponRange;
		const FHitResult Impact = WeaponTrace(StartTrace, EndTrace);
		ProcessInstantHit(Impact, StartTrace, ShootDir, RandomSeed, CurrentSpread);
	}
}

int AKMEProjectWeapon::DetermineSpread()
{
	if (MyPawn && MyPawn->IsTargeting())
	{
		return WeaponConfig.WeaponAimingSpread;
	}

	else
	{
		return WeaponConfig.WeaponSpread;
	}
}

void AKMEProjectWeapon::ProcessInstantHit(const FHitResult &Impact, const FVector &Origin, const FVector &ShootDir, int32 RandomSeed, float ReticleSpread)
{
	const FVector EndTrace = Origin + ShootDir * WeaponConfig.WeaponRange;
	const FVector EndPoint = Impact.GetActor() ? Impact.ImpactPoint : EndTrace;
	DrawDebugLine(this->GetWorld(), Origin, Impact.TraceEnd, FColor(255, 0, 0), false, 5, 10.f, 2);
}

FHitResult AKMEProjectWeapon::WeaponTrace(const FVector &TraceFrom, const FVector &TraceTo) const
{
	static FName WeaponFireTag = FName(TEXT("WeaponTrace"));

	FCollisionQueryParams TraceParams(WeaponFireTag, true, Instigator);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;
	TraceParams.AddIgnoredActor(this);

	FHitResult Hit(ForceInit);

	GetWorld()->LineTraceSingleByChannel(Hit, TraceFrom, TraceTo, TRACE_WEAPON, TraceParams);
	//DrawDebugLine(GetWorld(), TraceFrom, TraceTo, FColor(255, 0, 0), false, 4, 0, 2);

	return Hit;
}

void AKMEProjectWeapon::DealDamage()
{
	//class AEnemy *Enemy = Cast<AEnemy>(Impact.GetActor());
}

AKMEProjectWeapon* AKMEProjectWeapon::GetWeapon() const

{
	return Weapon;
}