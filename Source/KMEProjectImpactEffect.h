// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KMEProjectImpactEffect.generated.h"

#define IMPACT_SURFACE_Default		SurfaceType_Default
#define IMPACT_SURFACE_Concrete		SurfaceType1
#define IMPACT_SURFACE_Dirt			SurfaceType2
#define IMPACT_SURFACE_Water		SurfaceType3
#define IMPACT_SURFACE_Metal		SurfaceType4
#define IMPACT_SURFACE_Wood			SurfaceType5
#define IMPACT_SURFACE_Grass		SurfaceType6
#define IMPACT_SURFACE_Glass		SurfaceType7
#define IMPACT_SURFACE_Flesh		SurfaceType8

UENUM()
namespace EImpactMaterial
{
	enum Type
	{
		Default,
		Concrete,
		Dirt,
		Water,
		Metal,
		Wood,
		Grass,
		Glass,
		Flesh,
	};
}

UCLASS()
class KMEPROJECT_API AKMEProjectImpactEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKMEProjectImpactEffect();

protected:
	
	virtual void PostInitializeComponents() override;
};
