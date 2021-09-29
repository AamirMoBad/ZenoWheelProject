// Fill out your copyright notice in the Description page of Project Settings.

#include "WheelNew.h"
#include "Components/SphereComponent.h"
#include "Components/ChildActorComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "RimBase.h"

#define INCH_TO_CM 2.54f

#pragma region Construction
AWheelNew::AWheelNew() : AspectRatio(40.0f), TireWidth(220.0f), RimRadius(20.0f)
{
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	
	RimActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("RimActor"));
	RimActor->SetupAttachment(RootComponent);
	
	TireMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TireMesh"));
	TireMesh->SetupAttachment(RootComponent);
	TireMesh->SetCollisionProfileName(FName("NoCollision"));
	TireMesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	TireMesh->SetGenerateOverlapEvents(false);

	BrakeDiscMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BrakeDiscMesh"));
	BrakeDiscMesh->SetupAttachment(RootComponent);
	BrakeDiscMesh->SetCollisionProfileName(FName("NoCollision"));
	BrakeDiscMesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	BrakeDiscMesh->SetGenerateOverlapEvents(false);

	CaliperMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CaliperMesh"));
	CaliperMesh->SetupAttachment(RootComponent);
	CaliperMesh->SetCollisionProfileName(FName("NoCollision"));
	CaliperMesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	CaliperMesh->SetGenerateOverlapEvents(false);
}

void AWheelNew::PostActorCreated()
{
	Super::PostActorCreated();

	TireRadius = AspectRatio * TireWidth / 500.0f / INCH_TO_CM + RimRadius;
	TireMesh->SetMorphTarget(FName(TEXT("Rim_Radius")), NormalizeRimRadius(RimRadius));
	TireMesh->SetMorphTarget(FName(TEXT("Tire_Radius")), NormalizeTireRadius(TireRadius));
	TireMesh->SetMorphTarget(FName(TEXT("Depth")), NormalizeTireWidth(TireWidth));

	ARimBase* Rim = GetRim();
	if (Rim)
	{
		BrakeDiscDepth = Rim->GetRimInfo().BrakeDiscDepth;
		BrakeDiscMesh->SetMorphTarget(FName(TEXT("BD_Depth")), BrakeDiscDepth);
		CaliperMesh->SetMorphTarget(FName(TEXT("BD_Depth")), BrakeDiscDepth);
	}
}

void AWheelNew::PostLoad()
{
	Super::PostLoad();

	TireRadius = AspectRatio * TireWidth / 500.0f / INCH_TO_CM + RimRadius;
	TireMesh->SetMorphTarget(FName(TEXT("Rim_Radius")), NormalizeRimRadius(RimRadius));
	TireMesh->SetMorphTarget(FName(TEXT("Tire_Radius")), NormalizeTireRadius(TireRadius));
	TireMesh->SetMorphTarget(FName(TEXT("Depth")), NormalizeTireWidth(TireWidth));

	ARimBase* Rim = GetRim();
	if (Rim)
	{
		BrakeDiscDepth = Rim->GetRimInfo().BrakeDiscDepth;
		BrakeDiscMesh->SetMorphTarget(FName(TEXT("BD_Depth")), BrakeDiscDepth);
		CaliperMesh->SetMorphTarget(FName(TEXT("BD_Depth")), BrakeDiscDepth);
	}
}
#pragma endregion

void AWheelNew::ChangeRim_Implementation(TSubclassOf<ARimBase> NewRim, bool bResetSize)
{
	ARimBase* Rim = GetRim();
	if (!NewRim || !Rim)
		return;

	const float OldRadius = Rim->GetCurrentRadius();
	RimActor->SetChildActorClass(NewRim);
	Rim = GetRim();
	if (bResetSize)
		TireMesh->SetMorphTarget(FName(TEXT("Rim_Radius")), NormalizeRimRadius(Rim->GetCurrentRadius()));
	else
		SetRimRadius(OldRadius);
	Rim->SetWidth(TireWidth);
	BrakeDiscDepth = Rim->GetRimInfo().BrakeDiscDepth;
	BrakeDiscMesh->SetMorphTarget(FName(TEXT("BD_Depth")), BrakeDiscDepth);
	CaliperMesh->SetMorphTarget(FName(TEXT("BD_Depth")), BrakeDiscDepth);
}

void AWheelNew::ChangeTire_Implementation(USkeletalMesh* NewTireMesh, const float NewWidth)
{
	if (!NewTireMesh)
		return;

	TireWidth = NewWidth;
	TireMesh->SetSkeletalMesh(NewTireMesh);
	TireMesh->SetMorphTarget(FName(TEXT("Rim_Radius")), NormalizeRimRadius(RimRadius));
	if (ARimBase* Rim = GetRim())
	{
		Rim->SetWidth(TireWidth);
		BrakeDiscMesh->SetMorphTarget(FName(TEXT("BD_Depth")), BrakeDiscDepth);
		CaliperMesh->SetMorphTarget(FName(TEXT("BD_Depth")), BrakeDiscDepth);
	}
}

void AWheelNew::ChangeBrakeDisc_Implementation(USkeletalMesh* NewBrakeDiscMesh)
{
	if (!NewBrakeDiscMesh)
		return;

	BrakeDiscMesh->SetSkeletalMesh(NewBrakeDiscMesh);
	BrakeDiscMesh->SetMorphTarget(FName(TEXT("BD_Depth")), BrakeDiscDepth);
}

void AWheelNew::ChangeCaliper_Implementation(USkeletalMesh* NewCaliperMesh)
{
	if (!NewCaliperMesh)
		return;

	CaliperMesh->SetSkeletalMesh(NewCaliperMesh);
	CaliperMesh->SetMorphTarget(FName(TEXT("BD_Depth")), BrakeDiscDepth);
}

void AWheelNew::SetRimRadius_Implementation(const float NewRadius)
{
	RimRadius = NewRadius;
	TireMesh->SetMorphTarget(FName(TEXT("Rim_Radius")), NormalizeRimRadius(RimRadius));
	if (ARimBase* Rim = GetRim())
		Rim->SetRadius(NewRadius);
}

void AWheelNew::SetWheelAspectRatio_Implementation(const float NewAspectRatio)
{
	AspectRatio = NewAspectRatio;
	TireRadius = AspectRatio * TireWidth / 500.0f / INCH_TO_CM + RimRadius;
	TireMesh->SetMorphTarget(FName(TEXT("Tire_Radius")), NormalizeTireRadius(TireRadius));
}

void AWheelNew::SetWheelWidth_Implementation(const float NewWidth)
{
	TireWidth = NewWidth;
	TireMesh->SetMorphTarget(FName(TEXT("Depth")), NormalizeTireWidth(TireWidth));
	TireRadius = AspectRatio * TireWidth / 500.0f / INCH_TO_CM + RimRadius;
	TireMesh->SetMorphTarget(FName(TEXT("Tire_Radius")), NormalizeTireRadius(TireRadius));
	if (ARimBase* Rim = GetRim())
		Rim->SetWidth(TireWidth);
}

ARimBase* AWheelNew::GetRim() const
{ 
	return Cast<ARimBase>(RimActor->GetChildActor()); 
}

#if WITH_EDITOR
void AWheelNew::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName.ToString() == "AspectRatio" || PropertyName.ToString() == "TireWidth")
	{
		TireMesh->SetMorphTarget(FName(TEXT("Depth")), NormalizeTireWidth(TireWidth));
		TireRadius = AspectRatio * TireWidth / 500.0f / INCH_TO_CM + RimRadius;
		TireMesh->SetMorphTarget(FName(TEXT("Tire_Radius")), NormalizeTireRadius(TireRadius));

		if (ARimBase* Rim = GetRim())
			Rim->SetWidth(TireWidth);
	}
	else if (PropertyName.ToString() == "RimRadius")
	{
		TireMesh->SetMorphTarget(FName(TEXT("Rim_Radius")), NormalizeRimRadius(RimRadius));

		if (ARimBase* Rim = Cast<ARimBase>(RimActor->GetChildActorTemplate()))
			Rim->SetRadius(RimRadius);
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
