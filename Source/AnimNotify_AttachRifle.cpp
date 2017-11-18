// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotify_AttachRifle.h"
#include "KMEProjectWeapon.h"
#include "Engine.h"

UAnimNotify_AttachRifle::UAnimNotify_AttachRifle()
	: Super() {}

void UAnimNotify_AttachRifle::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	KMEProjectCharacter* MyChar = Cast<AKMEProjectCharacter>(MeshComp->GetOwner());

	KMEProjectWeapon* WeaponRef = Cast<AKMEProjectWeapon>(MyWeapon.GetDefaultObject());

	if (MyChar)
	{
		MyChar->CurrentWeapon->AttachToPlayer();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Char in AnimNotify NOT valid"));
	}


	/*MyWeapon.GetDefaultObject()->Destroy();
	MyWeapon.GetDefaultObject()->AttachToComponent(MeshComp, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("RifleSocket"));
	MyWeapon.GetDefaultObject()->bCanAttach = true;
	MyWeapon.GetDefaultObject()->TEST = 5;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("AnimNotify valid"));*/

}