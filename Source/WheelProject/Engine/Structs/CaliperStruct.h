#pragma once

#include "Engine/DataTable.h"
#include "Engine/SkeletalMesh.h"
#include "CaliperStruct.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "Caliper Struct"))
struct FCaliperTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Caliper")
		TSoftObjectPtr<USkeletalMesh> Mesh;

	FCaliperTableRow() : Mesh(nullptr)
	{

	}
};