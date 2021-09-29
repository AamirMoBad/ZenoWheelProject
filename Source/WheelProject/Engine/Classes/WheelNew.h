// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WheelNew.generated.h"

#ifndef RIM_RADIUS_MIN
#define RIM_RADIUS_MIN 14
#endif // !RIM_RADIUS_MIN
#ifndef RIM_RADIUS_MAX
#define RIM_RADIUS_MAX 24
#endif // !RIM_RADIUS_MAX
#ifndef TIRE_RADIUS_MIN
#define TIRE_RADIUS_MIN 18.0f
#endif // !TIRE_RADIUS_MIN
#ifndef TIRE_RADIUS_MAX
#define TIRE_RADIUS_MAX 28.0f
#endif // !TIRE_RADIUS_MAX
#ifndef TIRE_WIDTH_MIN
#define TIRE_WIDTH_MIN 188.0f
#endif // !TIRE_WIDTH_MIN
#ifndef TIRE_WIDTH_MAX
#define TIRE_WIDTH_MAX 338.0f
#endif // !TIRE_WIDTH_MAX

class UChildActorComponent;
class USkeletalMeshComponent;
class ARimBase;

/**
 * Car class.
 */
UCLASS()
class WHEELPROJECT_API AWheelNew : public AActor
{
	GENERATED_BODY()

public:	
#pragma region Construction
	/* Constructor*/
	AWheelNew();
	/* Post actor created*/
	virtual void PostActorCreated() override;
	/* Post load for actor placed in level*/
	virtual void PostLoad() override;
#pragma endregion

	/**
	 * Change to new rim.
	 *
	 * @param NewRim : New rim actor.
	 * @param bResetSize : Rim size will reset if true, otherwise rim size will remain the same.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Wheel")
		void ChangeRim(TSubclassOf<ARimBase> NewRim, bool bResetSize = false);

	/**
	 * Change mesh of tire mesh component.
	 *
	 * @param NewTireMesh : New tire mesh.
	 * @param NewWidth : New tire depth.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Wheel")
		void ChangeTire(USkeletalMesh* NewTireMesh, const float NewWidth);

	/**
	 * Change mesh of brake disc mesh component.
	 *
	 * @param NewBrakeDiscMesh : New brake disc mesh.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Wheel")
		void ChangeBrakeDisc(USkeletalMesh* NewBrakeDiscMesh);

	/**
	 * Change mesh of caliper mesh component.
	 *
	 * @param NewCaliperMesh : New caliper mesh.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Wheel")
		void ChangeCaliper(USkeletalMesh* NewCaliperMesh);

	/**
	 * Change rim radius, overall wheel radius is constant.
	 * 
	 * @param NewRadius : New rim radius. [14, 24]
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Wheel")
		void SetRimRadius(const float NewRadius);

	/**
	 * Set wheel aspect ratio.
	 *
	 * @param NewAspectRatio : New wheel aspect ratio.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Wheel")
		void SetWheelAspectRatio(const float NewAspectRatio);

	/**
	 * Set wheel width.
	 *
	 * @param NewWidth : New wheel width.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Wheel")
		void SetWheelWidth(const float NewWidth);
	 
	/**
	 * Get rim.
	 * 
	 * @return Rim actor.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Wheel")
		ARimBase* GetRim() const;

#pragma region Helper Function
public:
	/**
	 * Helper function to convert rim radius to morph target value.
	 *
	 * @param Radius : Rim radius to convert.
	 * @return Morph target value to use.
	 */
	FORCEINLINE float NormalizeRimRadius(const int Radius) { return FMath::GetMappedRangeValueUnclamped(FVector2D(RIM_RADIUS_MIN, RIM_RADIUS_MAX), FVector2D(0.0f, 1.0f), (float)Radius); }

	/**
	 * Helper function to convert tire radius to morph target value.
	 *
	 * @param Radius : Tire radius to convert.
	 * @return Morph target value to use.
	 */
	FORCEINLINE float NormalizeTireRadius(const float Radius) { return FMath::GetMappedRangeValueUnclamped(FVector2D(TIRE_RADIUS_MIN, TIRE_RADIUS_MAX), FVector2D(1.0f, 0.0f), Radius); }

	/**
	 * Helper function to convert tire width to morph target value.
	 *
	 * @param Width : Tire width to convert.
	 * @return Morph target value to use.
	 */
	FORCEINLINE float NormalizeTireWidth(const float Width) { return FMath::GetMappedRangeValueUnclamped(FVector2D(TIRE_WIDTH_MIN, TIRE_WIDTH_MAX), FVector2D(0.0f, 1.0f), Width); }
#pragma endregion

protected:
	/* Rim actor*/
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Wheel")
		UChildActorComponent* RimActor;
	/* Tire skeletal mesh*/
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Wheel")
		USkeletalMeshComponent* TireMesh;
	/* Brake disc skeletal mesh*/
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Wheel")
		USkeletalMeshComponent* BrakeDiscMesh;
	/* Caliper skeletal mesh*/
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Wheel")
		USkeletalMeshComponent* CaliperMesh;

	/* Wheel aspect ratio*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Wheel", meta = (DisplayPriority = 2))
		float AspectRatio;
	/* Total radius of wheel*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wheel", meta = (DisplayPriority = 2))
		float TireRadius;
	/* Total width of wheel*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Wheel", meta = (DisplayPriority = 2))
		float TireWidth;
	/* Rim radius*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Wheel", meta = (DisplayPriority = 2))
		float RimRadius;
	/* Brake disc offset from rim*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wheel", meta = (DisplayPriority = 2))
		float BrakeDiscDepth;

#if WITH_EDITOR
public:
	/**
	 * Virtual PostEditChangeProperty in USceneComponent class.
	 */
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
