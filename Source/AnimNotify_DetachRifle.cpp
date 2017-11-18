// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotify_DetachRifle.h"
#include "KMEProjectCharacter.h"

UAnimNotify_DetachRifle::UAnimNotify_DetachRifle()
	: Super() {}


void UAnimNotify_DetachRifle::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	KMEProjectCharacter* MyChar = Cast<AKMEProjectCharacter>(MeshComp->GetOwner());

	if (MyChar)
	{
		MyChar->CurrentWeapon->DettachFromPlayer();
	}
}