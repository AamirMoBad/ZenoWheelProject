// Fill out your copyright notice in the Description page of Project Settings.

#include "WheelBase.h"
#include "Components/SphereComponent.h"
#include "Components/ChildActorComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "RimBase.h"

AWheelBase::AWheelBase()
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

void AWheelBase::ChangeRim_Implementation(TSubclassOf<ARimBase> NewRim, bool bResetSize)
{
	ARimBase* Rim = GetRim();
	if (!NewRim || !Rim)
		return;

	const float OldRadius = Rim->GetCurrentRadius();
	RimActor->SetChildActorClass(NewRim);
	Rim = GetRim();
	if (bResetSize)
		TireMesh->SetMorphTarget(FName(TEXT("Radius")), Rim->GetCurrentRadius());
	else
		ChangeRadius(OldRadius);
	Rim->ChangeDepth(TireDepth);
	BrakeDiscDepth = Rim->GetRimInfo().BrakeDiscDepth;
	BrakeDiscMesh->SetMorphTarget(FName(TEXT("BD_Depth")), BrakeDiscDepth);
}

void AWheelBase::ChangeTire_Implementation(USkeletalMesh* NewTireMesh, const float NewDepth)
{
	ARimBase* Rim = GetRim();
	if (!NewTireMesh || !Rim)
		return;

	TireDepth = NewDepth;
	TireMesh->SetSkeletalMesh(NewTireMesh);
	TireMesh->SetMorphTarget(FName(TEXT("Radius")), Rim->GetCurrentRadius());
	Rim->ChangeDepth(TireDepth);
	BrakeDiscMesh->SetMorphTarget(FName(TEXT("BD_Depth")), BrakeDiscDepth);
}

void AWheelBase::ChangeBrakeDisc_Implementation(USkeletalMesh* NewBrakeDiscMesh)
{
	if (!NewBrakeDiscMesh)
		return;

	BrakeDiscMesh->SetSkeletalMesh(NewBrakeDiscMesh);
	BrakeDiscMesh->SetMorphTarget(FName(TEXT("BD_Depth")), BrakeDiscDepth);
}

void AWheelBase::ChangeCaliper_Implementation(USkeletalMesh* NewCaliperMesh)
{
	if (!NewCaliperMesh)
		return;

	CaliperMesh->SetSkeletalMesh(NewCaliperMesh);
	CaliperMesh->SetMorphTarget(FName(TEXT("BD_Depth")), BrakeDiscDepth);
}

void AWheelBase::ChangeRadius_Implementation(const float NewRadius)
{
	ARimBase* Rim = GetRim();
	if (!Rim)
		return;

	TireMesh->SetMorphTarget(FName(TEXT("Radius")), NewRadius);
	Rim->ChangeRadius(NewRadius);
}

ARimBase* AWheelBase::GetRim() const
{ 
	return Cast<ARimBase>(RimActor->GetChildActor()); 
}
