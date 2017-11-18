// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_DetachRifle.generated.h"

/**
 * 
 */
UCLASS()
class KMEPROJECT_API UAnimNotify_DetachRifle : public UAnimNotify
{
	GENERATED_BODY()
	
	UAnimNotify_DetachRifle();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Classes)
	TSubclassOf<class AKMEProjectCharacter> MyPawn;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Classes)
	//class KMEProjectCharacter* MyChar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<class KMEProjectWeapon> MyWeapon;
	
};
