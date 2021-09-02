#pragma once

#include "Engine/DataTable.h"
#include "Engine/SkeletalMesh.h"
#include "RimStruct.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "Rim Struct"))
struct FRimTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rim")
		TSoftObjectPtr<USkeletalMesh> Mesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tire")
		float BrakeDiscDepth;

	FRimTableRow() : Mesh(nullptr), BrakeDiscDepth(0.0f)
	{

	}
};