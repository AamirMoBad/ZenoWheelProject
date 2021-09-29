// Fill out your copyright notice in the Description page of Project Settings.

#include "PartComponent.h"
#include "Engine/DataTable.h"

// Sets default values for this component's properties
UPartComponent::UPartComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UPartComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPartComponent::InitPartComponent()
{
	DefaultMeshes.Empty();
	TArray<USceneComponent*> ChildComponents;
	GetChildrenComponents(false, ChildComponents);
	for (USceneComponent* compIter : ChildComponents)
	{
		UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(compIter);
		if (StaticMesh)
		{
			DefaultMeshes.Add(StaticMesh);
			StaticMesh->SetReceivesDecals(CustomizePart.bAcceptDecals);
			StaticMesh->SetRenderCustomDepth(true);
		}
	}
}

void UPartComponent::DefaultPartMaterial()
{
	if (!CustomizePart.DefaultMaterial || DefaultMeshes.Num() <= 0)
		return;

	PartMaterial = UMaterialInstanceDynamic::Create(CustomizePart.DefaultMaterial, this);
		
	for (UStaticMeshComponent* mesh : DefaultMeshes)
	{
		if (mesh)
			mesh->SetMaterial(0, PartMaterial);
	}
}

void UPartComponent::ChangePartMaterial(UMaterialInterface* mat)
{
	if (!mat || DefaultMeshes.Num() <= 0)
		return;

	if (Cast<UMaterialInstanceDynamic>(mat))
	{
		PartMaterial = Cast<UMaterialInstanceDynamic>(mat);
	}
	else
	{
		PartMaterial = UMaterialInstanceDynamic::Create(mat, this);
	}

	for (UStaticMeshComponent* mesh : DefaultMeshes)
	{
		if (mesh)
			mesh->SetMaterial(0, PartMaterial);
	}
}

void UPartComponent::OnChildAttached(USceneComponent* ChildComponent)
{

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

	UE_LOG(LogBlueprint, Display, TEXT("BP property changed: %s."), *PropertyName.ToString());

	if (PropertyName.ToString() == "DefaultMaterial") // Only create new dynamic material if material is null or material changed.
	{
		if (!CustomizePart.DefaultMaterial)
			return;
		TArray<USceneComponent*> ChildComponents;
		GetChildrenComponents(false, ChildComponents);
		for (USceneComponent* compIter : ChildComponents)
		{
			UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(compIter);
			if (StaticMesh)
			{
				StaticMesh->SetMaterial(0, CustomizePart.DefaultMaterial);
			}
		}
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

