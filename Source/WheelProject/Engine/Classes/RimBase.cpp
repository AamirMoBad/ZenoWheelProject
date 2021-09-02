// Fill out your copyright notice in the Description page of Project Settings.

#include "RimBase.h"
#include "Components/SkeletalMeshComponent.h"

ARimBase::ARimBase()
{
	RimMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RimMesh"));
	RootComponent = RimMesh;
}

void ARimBase::Initialize(const FRimTableRow& InitInfo)
{
	RimInfo = InitInfo;
	USkeletalMesh* SkeletalMesh = RimInfo.Mesh.LoadSynchronous();
	if (SkeletalMesh)
	{
		RimMesh->SetSkeletalMesh(SkeletalMesh);
	}
}

void ARimBase::ChangeRadius_Implementation(const float NewRadius, FName MorphTargetName)
{
	RimRadius = NewRadius;
	RimMesh->SetMorphTarget(MorphTargetName, RimRadius);
}

void ARimBase::ChangeDepth_Implementation(const float NewDepth, FName MorphTargetName)
{
	RimMesh->SetMorphTarget(MorphTargetName, NewDepth);
}