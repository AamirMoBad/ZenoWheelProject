// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Structs/RimStruct.h"
#include "RimBase.generated.h"

class USkeletalMeshComponent;

/**
 * Car class.
 */
UCLASS()
class WHEELPROJECT_API ARimBase : public AActor
{
	GENERATED_BODY()

public:	
	/* Constructor*/
	ARimBase();

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
	 * @param NewRadius : New rim radius.
	 * @param MorphTargetName : Skeleton mesh morph target name.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Rim")
		void ChangeRadius(const float NewRadius, FName MorphTargetName = FName(TEXT("Radius")));

	/**
	 * Change rim depth.
	 *
	 * @param NewDepth : New rim depth.
	 * @param MorphTargetName : Skeleton mesh morph target name.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Rim")
		void ChangeDepth(const float NewDepth, FName MorphTargetName = FName(TEXT("Depth")));

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

protected:
	/* Rim skeletal mesh*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Rim")
		USkeletalMeshComponent* RimMesh;

	/* Rim info*/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Rim")
		FRimTableRow RimInfo;

	/* Current rim radius*/
	UPROPERTY(BlueprintReadOnly, Category = "Rim")
		float RimRadius;
};
