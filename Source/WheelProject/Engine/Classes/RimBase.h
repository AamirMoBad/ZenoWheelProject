// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Structs/RimStruct.h"
#include "RimBase.generated.h"

class USkeletalMeshComponent;
class UPartComponent;

#ifndef RIM_RADIUS_MIN
#define RIM_RADIUS_MIN 14.0f
#endif // !RIM_RADIUS_MIN
#ifndef RIM_RADIUS_MAX
#define RIM_RADIUS_MAX 24.0f
#endif // !RIM_RADIUS_MAX
#ifndef RIM_WIDTH_MIN
#define RIM_WIDTH_MIN 188.0f
#endif // !RIM_WIDTH_MIN
#ifndef RIM_WIDTH_MAX
#define RIM_WIDTH_MAX 338.0f
#endif // !RIM_WIDTH_MAX

/**
 * Car class.
 */
UCLASS()
class WHEELPROJECT_API ARimBase : public AActor
{
	GENERATED_BODY()

public:	
#pragma region Construction
	/* Constructor*/
	ARimBase();
	/* Post actor created*/
	virtual void PostActorCreated() override;
	/* Post load for actor placed in level*/
	virtual void PostLoad() override;
	/* Post components initialized*/
	virtual void PostInitializeComponents() override;
#pragma endregion

	/**
	 * Initialize rim.
	 * 
	 * @param InitInfo : Info used to initialize rim.
	 */
	UFUNCTION(BlueprintCallable, Category = "Rim")
		void Initialize(const FRimTableRow& InitInfo);

	/**
	 * Change rim radius.
	 *
	 * @param NewRadius : New rim radius. [14.0, 24.0]
	 * @param MorphTargetName : Skeleton mesh morph target name.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Rim")
		void SetRadius(const float NewRadius, FName MorphTargetName = FName(TEXT("Rim_Radius")));

	/**
	 * Change rim width.
	 *
	 * @param NewDepth : New rim width. [188.0, 338.0]
	 * @param MorphTargetName : Skeleton mesh morph target name.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Rim")
		void SetWidth(const float NewWidth, FName MorphTargetName = FName(TEXT("Depth")));

	/**
	 * Get all info related to this rim.
	 *
	 * @return Rim info.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Rim")
		FRimTableRow GetRimInfo() const { return RimInfo; }

	/**
	 * Get current rim radius.
	 *
	 * @return Rim radius.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Rim")
		float GetCurrentRadius() const { return RimRadius; }

	UFUNCTION(BlueprintCallable)
		void ChangeMaterial(const FString& PartName, UMaterialInterface* Mat);

#pragma region Helper Function
protected:
	/**
	 * Helper function to convert rim radius to morph target value.
	 * 
	 * @param Radius : Rim radius to convert.
	 * @return Morph target value to use.
	 */
	FORCEINLINE float NormalizeRadius(const int Radius) { return FMath::GetMappedRangeValueUnclamped(FVector2D(RIM_RADIUS_MIN, RIM_RADIUS_MAX), FVector2D(1.0f, 0.0f), Radius); }

	/**
	 * Helper function to convert rim width to morph target value.
	 *
	 * @param Width : Rim width to convert.
	 * @return Morph target value to use.
	 */
	FORCEINLINE float NormalizeWidth(const float Width) { return FMath::GetMappedRangeValueUnclamped(FVector2D(RIM_WIDTH_MIN, RIM_WIDTH_MAX), FVector2D(0.0f, 1.0f), Width); }
#pragma endregion

protected:
	/* Rim skeletal mesh*/
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Rim")
		USkeletalMeshComponent* RimMesh;

	/* Rim info*/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Rim")
		FRimTableRow RimInfo;

	/* Current rim radius*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Rim", meta = (ClampMin = 14.0f, ClampMax = 24.0f, DisplayPriority=2))
		float RimRadius;
	/* Current rim width*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Rim", meta = (ClampMin = 188.0f, ClampMax = 338.0f, DisplayPriority = 2))
		float RimWidth;

#if WITH_EDITOR
public:
	/**
	 * Virtual PostEditChangeProperty in USceneComponent class.
	 */
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
