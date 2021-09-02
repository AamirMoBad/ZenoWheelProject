// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WheelBase.generated.h"

class UChildActorComponent;
class USkeletalMeshComponent;
class ARimBase;

/**
 * Car class.
 */
UCLASS()
class WHEELPROJECT_API AWheelBase : public AActor
{
	GENERATED_BODY()

public:	
	/* Constructor*/
	AWheelBase();

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
	 * @param NewDepth : New tire depth.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Wheel")
		void ChangeTire(USkeletalMesh* NewTireMesh, const float NewDepth);

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
	 * Change wheel radius.
	 * 
	 * @param NewRadius : New wheel radius.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Wheel")
		void ChangeRadius(const float NewRadius);
	 
	/**
	 * Get rim.
	 * 
	 * @return Rim actor.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Wheel")
		ARimBase* GetRim() const;

protected:
	/* Rim actor*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wheel")
		UChildActorComponent* RimActor;
	/* Tire skeletal mesh*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wheel")
		USkeletalMeshComponent* TireMesh;
	/* Brake disc skeletal mesh*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wheel")
		USkeletalMeshComponent* BrakeDiscMesh;
	/* Caliper skeletal mesh*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wheel")
		USkeletalMeshComponent* CaliperMesh;

	/* Total depth of wheel*/
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Wheel")
		float TireDepth;
	/* Brake disc offset from rim*/
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Wheel")
		float BrakeDiscDepth;
};
