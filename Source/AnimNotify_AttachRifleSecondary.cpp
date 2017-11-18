// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotify_AttachRifleSecondary.h"
#include "KMEProjectCharacter.h"

UAnimNotify_AttachRifleSecondary::UAnimNotify_AttachRifleSecondary()
	: Super() {}

void UAnimNotify_AttachRifleSecondary::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	KMEProjectCharacter* MyChar = Cast<KMEProjectCharacter>(MeshComp->GetOwner());

	if (MyChar)
	{
		MyChar->CurrentWeapon->AttachToPlayerSecondarySocket();
	}
}






