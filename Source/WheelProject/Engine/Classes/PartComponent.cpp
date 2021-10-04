// Fill out your copyright notice in the Description page of Project Settings.

#include "PartComponent.h"
#include "Engine/DataTable.h"

DEFINE_LOG_CATEGORY(LogPart);

// Sets default values for this component's properties
UPartComponent::UPartComponent() : bSkeletalMesh(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UPartComponent::InitPartComponent()
{
	if (bSkeletalMesh)
		UE_LOG(LogPart, Error, TEXT("Initialing with static meshes while declared using skeletal mesh."));

	ChildStaticMeshes.Empty();
	PartIndices.Empty();
	SkeletalMesh = nullptr;
	TArray<USceneComponent*> ChildComponents;
	GetChildrenComponents(false, ChildComponents);
	for (USceneComponent* compIter : ChildComponents)
	{
		if (UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(compIter))
		{
			ChildStaticMeshes.Add(StaticMesh);
			StaticMesh->SetReceivesDecals(CustomizePart.bAcceptDecals);
			StaticMesh->SetRenderCustomDepth(true);
		}
	}
}

void UPartComponent::InitPartComponent(USkeletalMeshComponent* SkeletalMeshComponent)
{
	if (!bSkeletalMesh)
		UE_LOG(LogPart, Error, TEXT("Initialing with skeletal mesh while declared using static meshes."));

	ChildStaticMeshes.Empty();
	SkeletalMesh = SkeletalMeshComponent;
	if (SkeletalMesh)
	{
		SkeletalMesh->SetRenderCustomDepth(true);
		if (CustomizePart.DefaultMaterial)
		{
			for (int indexIter : PartIndices)
				SkeletalMesh->SetMaterial(indexIter, CustomizePart.DefaultMaterial);
		}
	}
}

void UPartComponent::DefaultPartMaterial()
{
	if (!CustomizePart.DefaultMaterial || IsEmpty())
	{
		UE_LOG(LogPart, Warning, TEXT("Early exit while changing materials."));
		return;
	}
		
	PartMaterial = UMaterialInstanceDynamic::Create(CustomizePart.DefaultMaterial, this);
	
	if (bSkeletalMesh)
	{
		for (int indexIter : PartIndices)
			SkeletalMesh->SetMaterial(indexIter, PartMaterial);
	}
	else
	{
		for (UStaticMeshComponent* meshIter : ChildStaticMeshes)
		{
			if (meshIter)
				meshIter->SetMaterial(0, PartMaterial);
		}
	}
}

void UPartComponent::ChangePartMaterial(UMaterialInterface* Mat)
{
	if (!Mat || IsEmpty())
	{
		UE_LOG(LogPart, Warning, TEXT("Early exit while changing materials."));
		return;
	}

	if (Cast<UMaterialInstanceDynamic>(Mat))
	{
		PartMaterial = Cast<UMaterialInstanceDynamic>(Mat);
	}
	else
	{
		PartMaterial = UMaterialInstanceDynamic::Create(Mat, this);
	}

	if (bSkeletalMesh)
	{
		for (int indexIter : PartIndices)
			SkeletalMesh->SetMaterial(indexIter, PartMaterial);
	}
	else
	{
		for (UStaticMeshComponent* meshIter : ChildStaticMeshes)
		{
			if (meshIter)
				meshIter->SetMaterial(0, PartMaterial);
		}
	}
}

FString UPartComponent::ToReadablePartName(const FString& str)
{
	FString ReadableStr = "";
	const int32 StringLength = str.Len();
	const TCHAR* RawData = str.GetCharArray().GetData();
	bool SpaceFlag = false;
	bool NumFlag = false;
	for (int32 i = 0; i < StringLength; ++i)
	{
		if (i == 0)
		{
			ReadableStr = ReadableStr.AppendChar(FChar::ToUpper(RawData[i]));
		}
		else
		{
			if (FChar::IsAlpha(RawData[i]))
			{
				if (NumFlag)
				{
					if (SpaceFlag)
						SpaceFlag = false;
					else
						ReadableStr = ReadableStr.AppendChar(' ');

					ReadableStr = ReadableStr.AppendChar(FChar::ToUpper(RawData[i]));
					NumFlag = false;
				}
				else if (SpaceFlag)
				{
					SpaceFlag = false;
					ReadableStr = ReadableStr.AppendChar(FChar::ToUpper(RawData[i]));
				}
				else
				{
					if (FChar::IsUpper(RawData[i]))
					{
						if (SpaceFlag)
							SpaceFlag = false;
						else
							ReadableStr = ReadableStr.AppendChar(' ');
					}
					ReadableStr = ReadableStr.AppendChar(RawData[i]);
				}
			}
			else if (FChar::IsDigit(RawData[i]))
			{
				if (!NumFlag)
				{
					if (SpaceFlag)
						SpaceFlag = false;
					else
						ReadableStr = ReadableStr.AppendChar(' ');

					NumFlag = true;
				}
				ReadableStr = ReadableStr.AppendChar(RawData[i]);
			}
			else
			{
				NumFlag = false;
				SpaceFlag = false;
				if (FChar::IsWhitespace(RawData[i]))
				{
					SpaceFlag = true;
				}
				ReadableStr = ReadableStr.AppendChar(RawData[i]);
			}
		}
	}
	return ReadableStr;
}

#if WITH_EDITOR
void UPartComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCustomizePart, DefaultMaterial))
	{
		if (!CustomizePart.DefaultMaterial)
			return;

		if (bSkeletalMesh)
		{
			if (SkeletalMesh)
			{
				/*for (int indexIter : PartIndices)
				{
					// Doesn't do anything.
					SkeletalMesh->SetMaterial(indexIter, CustomizePart.DefaultMaterial);
				}*/
			}
		}
		else
		{
			TArray<USceneComponent*> ChildComponents;
			GetChildrenComponents(false, ChildComponents);
			for (USceneComponent* compIter : ChildComponents)
			{
				if (UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(compIter))
				{
					StaticMesh->SetMaterial(0, CustomizePart.DefaultMaterial);
				}
			}
		}
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

