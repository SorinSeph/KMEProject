// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "KMEProjectCharacter.h"
#include "KMEProjectProjectile.h"
#include "KMEProjectPlayerController.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"
#include "MotionControllerComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);



//////////////////////////////////////////////////////////////////////////
// AKMEProjectCharacter

AKMEProjectCharacter::AKMEProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	FPSHands = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPSHands"));
	FPSHands->SetupAttachment(FirstPersonCameraComponent);

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	// Create VR Controllers.
	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->Hand = EControllerHand::Right;
	R_MotionController->SetupAttachment(RootComponent);
	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->SetupAttachment(RootComponent);

	// Create a gun and attach it to the right-hand VR controller.
	// Create a gun mesh component
	VR_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VR_Gun"));
	VR_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	VR_Gun->bCastDynamicShadow = false;
	VR_Gun->CastShadow = false;
	VR_Gun->SetupAttachment(R_MotionController);
	VR_Gun->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	VR_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("VR_MuzzleLocation"));
	VR_MuzzleLocation->SetupAttachment(VR_Gun);
	VR_MuzzleLocation->SetRelativeLocation(FVector(0.000004, 53.999992, 10.000000));
	VR_MuzzleLocation->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));		// Counteract the rotation of the VR gun model.

	// Uncomment the following line to turn motion controllers on by default:
	//bUsingMotionControllers = true;

	GetCharacterMovement()->MaxWalkSpeed = 350;

	LevelUpPoints = 0;

	bIsTargeting = false;
	CharLockpickID = 0;
	TimeDelay = 0;
	bIsRunning = false;
}

void AKMEProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();


	//AKMEProjectPlayerController* MyPC = Cast<AKMEProjectPlayerController>(GetWorld()->GetFirstPlayerController());

	InitDelay();
	GiveDefaultWeapon();
	MyPC = Cast<AKMEProjectPlayerController>(GetWorld()->GetFirstPlayerController());



	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	if (bUsingMotionControllers)
	{
		VR_Gun->SetHiddenInGame(false, true);
		Mesh1P->SetHiddenInGame(true, true);
	}
	else
	{
		VR_Gun->SetHiddenInGame(true, true);
		Mesh1P->SetHiddenInGame(false, true);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AKMEProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AKMEProjectCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AKMEProjectCharacter::SprintStop);
	PlayerInputComponent->BindAction("EnterLockpick", IE_Pressed, this, &AKMEProjectCharacter::EnterLockpick);
	PlayerInputComponent->BindAxis("MoveForward", this, &AKMEProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AKMEProjectCharacter::MoveRight);
	PlayerInputComponent->BindAction("Use", IE_Pressed, this, &AKMEProjectCharacter::OnUse);
	PlayerInputComponent->BindAction("Use", IE_Released, this, &AKMEProjectCharacter::OnUseFinished);

	InputComponent->BindAction("Fire", IE_Pressed, this, &AKMEProjectCharacter::OnFire);
	InputComponent->BindAction("Fire", IE_Released, this, &AKMEProjectCharacter::StopFire);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AKMEProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AKMEProjectCharacter::LookUpAtRate);
}

void AKMEProjectCharacter::OnUse()
{
	bWantsToUse = true;
}

void AKMEProjectCharacter::OnUseFinished()
{
	bWantsToUse = false;
}

void AKMEProjectCharacter::InitDelay()
{
	float TimeDelay = GetWorld()->GetTimeSeconds() + 5;
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::SanitizeFloat(TimeDelay));
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::SanitizeFloat(GetWorld()->GetTimeSeconds()));
}

void AKMEProjectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, bTEST ? TEXT("TRUE") : TEXT("FALSE"));
	
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::FromInt(CharLockpickID));
	if ( FMath::IsNearlyEqual(GetWorld()->GetTimeSeconds(), 5, 0.01f) )
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Time achieved!"));
	}

	GetCurrentClip();
}

void AKMEProjectCharacter::OnFire()
{
	if (CurrentWeapon != NULL)
	{
		CurrentWeapon->Fire();
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Fire from Character.cpp!"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Current weapon null!"));
	}
}

void AKMEProjectCharacter::StopFire()
{
	if (CurrentWeapon != NULL)
	{
		CurrentWeapon->Stop();
	}
}

void AKMEProjectCharacter::Reload()
{
	if (CurrentWeapon != NULL)
	{
		CurrentWeapon->Reload();
	}
}

void AKMEProjectCharacter::GiveDefaultWeapon()
{
	AKMEProjectWeapon *Spawner = GetWorld()->SpawnActor<AKMEProjectWeapon>(WeaponSpawn);

	if (Spawner)
		{

			Inventory[Spawner->WeaponConfig.Priority] = Spawner;
			CurrentWeapon = Inventory[Spawner->WeaponConfig.Priority];
			CurrentWeapon->SetOwningPawn(this);
			CurrentWeapon->AttachToPlayer();
		}
}


void AKMEProjectCharacter::UpgradeAbility()
{

}

void AKMEProjectCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AKMEProjectCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AKMEProjectCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = false;
}

int32 AKMEProjectCharacter::GetCurrentClip()
{
	if (Inventory[0])
	{
		return Inventory[0]->CurrentClip;
	}
	return 1;
}

//Commenting this section out to be consistent with FPS BP template.
//This allows the user to turn without using the right virtual joystick

//void AKMEProjectCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
//	{
//		if (TouchItem.bIsPressed)
//		{
//			if (GetWorld() != nullptr)
//			{
//				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
//				if (ViewportClient != nullptr)
//				{
//					FVector MoveDelta = Location - TouchItem.Location;
//					FVector2D ScreenSize;
//					ViewportClient->GetViewportSize(ScreenSize);
//					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
//					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.X * BaseTurnRate;
//						AddControllerYawInput(Value);
//					}
//					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.Y * BaseTurnRate;
//						AddControllerPitchInput(Value);
//					}
//					TouchItem.Location = Location;
//				}
//				TouchItem.Location = Location;
//			}
//		}
//	}
//}

void AKMEProjectCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
		if (bIsRunning)
		{
			MyPC->ClientStopCameraShake(WalkingCameraShake, false);
			MyPC->ClientPlayCameraShake(SprintingCameraShake, 1, ECameraAnimPlaySpace::CameraLocal, FRotator(0, 0, 0));
		}
		else
		{
			MyPC->ClientStopCameraShake(SprintingCameraShake, false);
			MyPC->ClientPlayCameraShake(WalkingCameraShake, 1, ECameraAnimPlaySpace::CameraLocal, FRotator(0, 0, 0));
		}
	}
}

void AKMEProjectCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AKMEProjectCharacter::SprintStart()
{
	bIsRunning = true;
	//MyPC->ClientStopCameraShake(WalkingCameraShake, false);
	GetCharacterMovement()->MaxWalkSpeed = 750;
	if (!GetCharacterMovement()->IsWalking())
	{
		MyPC->ClientStopCameraShake(SprintingCameraShake, false);
	}
	//MyPC->ClientPlayCameraShake(SprintingCameraShake, 1, ECameraAnimPlaySpace::CameraLocal, FRotator(0, 0, 0));
}

void AKMEProjectCharacter::SprintStop()
{
	bIsRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = 350;
	//MyPC->ClientStopCameraShake(SprintingCameraShake, false);
}

void AKMEProjectCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AKMEProjectCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AKMEProjectCharacter::EnterLockpick()
{
	//AKMEProjectPlayerController* MyPC = Cast<AKMEProjectPlayerController>(Controller);
	MyPC->Possess(LockpickPawnRef[CharLockpickID]);
	LockpickPawnRef[CharLockpickID]->SetActorTickEnabled(true);

	const ULocalPlayer* LocalPlayer = MyPC->GetLocalPlayer();
	if (LocalPlayer && LocalPlayer->ViewportClient)
	{
		FViewport* Viewport = LocalPlayer->ViewportClient->Viewport;
		if (Viewport)
		{
			FVector2D ViewportSize;
			LocalPlayer->ViewportClient->GetViewportSize(ViewportSize);
			const int32 X = static_cast<int32>(ViewportSize.X * 0.5f);
			const int32 Y = static_cast<int32>(ViewportSize.Y * 0.5f);

			Viewport->SetMouse(X, Y);
			LockpickPawnRef[CharLockpickID]->OriginalMousePosX = X;
			LockpickPawnRef[CharLockpickID]->CurrentMousePosY = Y;
			//MyPC->bShowMouseCursor = true;
		}
	}
}

bool AKMEProjectCharacter::IsTargeting() const
{
	return bIsTargeting;
}

bool AKMEProjectCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	bool bResult = false;
	if (FPlatformMisc::GetUseVirtualJoysticks() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		bResult = true;
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AKMEProjectCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AKMEProjectCharacter::EndTouch);

		//Commenting this out to be more consistent with FPS BP template.
		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AKMEProjectCharacter::TouchUpdate);
	}
	return bResult;
}
