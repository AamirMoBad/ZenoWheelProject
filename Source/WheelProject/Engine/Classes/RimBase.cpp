// Fill out your copyright notice in the Description page of Project Settings.

#include "RimBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "PartComponent.h"

#pragma region Construction
ARimBase::ARimBase() : RimRadius(20.0f), RimWidth(220.0f)
{
	RimMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RimMesh"));
	RootComponent = RimMesh;
}

void ARimBase::PostActorCreated()
{
	Super::PostActorCreated();

	if (IsTemplate())
		return;

	RimMesh->SetMorphTarget(FName(TEXT("Rim_Radius")), NormalizeRadius(RimRadius));
	RimMesh->SetMorphTarget(FName(TEXT("Depth")), NormalizeWidth(RimWidth));
}

void ARimBase::PostLoad()
{
	Super::PostLoad();

	if (IsTemplate())
		return;

	RimMesh->SetMorphTarget(FName(TEXT("Rim_Radius")), NormalizeRadius(RimRadius));
	RimMesh->SetMorphTarget(FName(TEXT("Depth")), NormalizeWidth(RimWidth));
}

void ARimBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (IsTemplate())
		return;

	TArray<UActorComponent*> Components = GetComponentsByClass(UPartComponent::StaticClass());
	for (UActorComponent* compIter : Components)
	{
		if (UPartComponent* PartComponent = Cast<UPartComponent>(compIter))
		{
			PartComponent->InitPartComponent(RimMesh);
		}
	}
}
#pragma endregion

void ARimBase::Initialize(const FRimTableRow& InitInfo)
{
	RimInfo = InitInfo;
	USkeletalMesh* SkeletalMesh = RimInfo.Mesh.LoadSynchronous();
	if (SkeletalMesh)
	{
		RimMesh->SetSkeletalMesh(SkeletalMesh);
	}
}

void ARimBase::SetRadius_Implementation(const float NewRadius, FName MorphTargetName)
{
	RimRadius = NewRadius;
	RimMesh->SetMorphTarget(MorphTargetName, NormalizeRadius(RimRadius));
}

void ARimBase::SetWidth_Implementation(const float NewWidth, FName MorphTargetName)
{
	RimWidth = NewWidth;
	RimMesh->SetMorphTarget(MorphTargetName, NormalizeWidth(RimWidth));
}

void ARimBase::ChangeMaterial(const FString& PartName, UMaterialInterface* Mat)
{
	TArray<UActorComponent*> Components = GetComponentsByClass(UPartComponent::StaticClass());
	for (UActorComponent* compIter : Components)
	{
		if (UPartComponent* PartComponent = Cast<UPartComponent>(compIter))
		{
			if (PartComponent->GetPartName() == PartName)
				PartComponent->ChangePartMaterial(Mat);
		}
	}
}

#if WITH_EDITOR
void ARimBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName.ToString() == "RimRadius")
	{
		RimMesh->SetMorphTarget(FName(TEXT("Rim_Radius")), NormalizeRadius(RimRadius));
	}
	if (PropertyName.ToString() == "RimWidth")
	{
		RimMesh->SetMorphTarget(FName(TEXT("Depth")), NormalizeWidth(RimWidth));
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif