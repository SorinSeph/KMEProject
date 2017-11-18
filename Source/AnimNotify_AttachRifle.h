// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "KMEProjectCharacter.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_AttachRifle.generated.h"

class UAnimSequenceBase;
class USkeletalMeshComponent;
/**
 * 
 */
UCLASS()
class KMEPROJECT_API UAnimNotify_AttachRifle : public UAnimNotify
{
	GENERATED_BODY()

	UAnimNotify_AttachRifle();
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Classes)
	TSubclassOf<class AKMEProjectCharacter> MyPawn;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Classes)
	//class AKMEProject* MyChar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<class AKMEProjectWeapon> MyWeapon;

	UPROPERTY(EditAnywhere, Category = Parameters)
	UClass* TestClassParameter;
};
