// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_AttachRifleSecondary.generated.h"

/**
 * 
 */
UCLASS()
class KMEPROJECT_API UAnimNotify_AttachRifleSecondary : public UAnimNotify
{
	GENERATED_BODY()
	
	UAnimNotify_AttachRifleSecondary();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
