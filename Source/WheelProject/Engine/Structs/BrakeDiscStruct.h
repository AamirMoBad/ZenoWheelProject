#pragma once

#include "Engine/DataTable.h"
#include "Engine/SkeletalMesh.h"
#include "BrakeDiscStruct.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "Brake Disc Struct"))
struct FBrakeDiscTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Brake Disc")
		TSoftObjectPtr<USkeletalMesh> Mesh;

	FBrakeDiscTableRow() : Mesh(nullptr)
	{

	}
};