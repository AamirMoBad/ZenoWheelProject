#pragma once

#include "Engine/DataTable.h"
#include "Engine/SkeletalMesh.h"
#include "TireStruct.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "Tire Struct"))
struct FTireTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tire")
		TSoftObjectPtr<USkeletalMesh> Mesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tire")
		float Depth;

	FTireTableRow() : Mesh(nullptr), Depth(0.0f)
	{

	}
};