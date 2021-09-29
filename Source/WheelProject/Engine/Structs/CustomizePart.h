#pragma once

#include "CustomizePart.generated.h"

UENUM(BlueprintType, meta = (DisplayName = "Left Right Position"))
enum class EPosiLR : uint8
{
	None,
	Left,
	Right
};

UENUM(BlueprintType, meta = (DisplayName = "Front Back Position"))
enum class EPosiFB : uint8
{
	None,
	Front,
	Back
};

USTRUCT(BlueprintType, meta = (DisplayName = "Part Position"))
struct FPartPosition
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Part Position")
		EPosiLR LeftRightPosition;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Part Position")
		EPosiFB FrontBackPosition;

	FPartPosition() : LeftRightPosition(EPosiLR::None), FrontBackPosition(EPosiFB::None)
	{

	}

	FPartPosition(EPosiLR lr, EPosiFB fb) : LeftRightPosition(lr), FrontBackPosition(fb)
	{

	}

	bool IsFront() const { return FrontBackPosition == EPosiFB::Front; }
	bool IsBack() const { return FrontBackPosition == EPosiFB::Back; }
	bool IsLeft() const { return LeftRightPosition == EPosiLR::Left; }
	bool IsRight() const { return LeftRightPosition == EPosiLR::Right; }
};

USTRUCT(BlueprintType, meta = (DisplayName = "Customize Part"))
struct FCustomizePart
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Customize Part")
		FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Customize Part")
		TSoftObjectPtr<UTexture2D> PartThumbnail;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Customize Part")
		UMaterialInterface* DefaultMaterial;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Customize Part")
		bool bIsMainBody;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Customize Part")
		bool bChromeDeleteOption;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Customize Part")
		bool bVisibleOption;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Customize Part")
		bool bAcceptDecals;

	FCustomizePart() : Name("Part"),  DefaultMaterial(nullptr), bIsMainBody(false), bChromeDeleteOption(false), bVisibleOption(true), bAcceptDecals(true)
	{

	}
};