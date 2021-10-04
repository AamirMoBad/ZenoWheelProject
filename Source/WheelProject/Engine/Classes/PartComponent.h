// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "../Structs/CustomizePart.h"
#include "PartComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPart, Log, All);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WHEELPROJECT_API UPartComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPartComponent();

	/**
	 * Get customize part info struct.
	 *
	 * @return Customize part struct.
	 */
	UFUNCTION(BlueprintCallable)
		const FCustomizePart& GetPartInfo() const { return CustomizePart; }

	/**
	 * Set customize part name.
	 */
	UFUNCTION(BlueprintCallable)
		void SetPartName(const FString& name) { CustomizePart.Name = name; }

	/**
	 * Get customize part name.
	 *
	 * @return Customize part name.
	 */
	UFUNCTION(BlueprintCallable)
		FString GetPartName() const { return CustomizePart.Name; }

	/**
	 * Get raw customize part name. No spaces.
	 *
	 * @return Customize part name.
	 */
	UFUNCTION(BlueprintCallable)
		FString GetRawPartName() const { return CustomizePart.Name.Replace(TEXT(" "), TEXT(""), ESearchCase::IgnoreCase); }

	/**
	 * Initialize part component using child static meshes.
	 */
	void InitPartComponent();

	/**
	 * Initialize part component using skeletal mesh.
	 * 
	 * @param SkeletalMeshComponent : Mesh whose material slots are group in this part.
	 */
	void InitPartComponent(USkeletalMeshComponent* SkeletalMeshComponent);

	/**
	 * Change customize part material to default material.
	 */
	UFUNCTION(BlueprintCallable)
		void DefaultPartMaterial();

	/**
	 * Change customize part material.
	 *
	 * @param Mat : Material to apply.
	 */
	UFUNCTION(BlueprintCallable)
		void ChangePartMaterial(UMaterialInterface* Mat);

	/**
	 * Get children static mesh components.
	 *
	 * @return Array of child static mesh components.
	 */
	UFUNCTION(BlueprintCallable)
		const TArray<UStaticMeshComponent*>& GetChildrenMeshes() const { return ChildStaticMeshes; }

	/**
	 * Get skeletal mesh component.
	 *
	 * @return Skeletal mesh component.
	 */
	UFUNCTION(BlueprintCallable)
		USkeletalMeshComponent* GetSkeletalMesh() const { return SkeletalMesh; }

	/**
	 * Get skeletal mesh components material indices.
	 *
	 * @return Array of material indices.
	 */
	UFUNCTION(BlueprintCallable)
		const TArray<int>& GetPartIndices() const { return PartIndices; }

	/**
	 * Get whether there are any children components (static mesh and body kit).
	 *
	 * @return True if part has no children components, false otherwise.
	 */
	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsEmpty() const { return bSkeletalMesh ? (SkeletalMesh ? PartIndices.Num() == 0 : true) : ChildStaticMeshes.Num() == 0; }

	UFUNCTION(BlueprintCallable)
		static FString ToReadablePartName(const FString& str);

	/**
	 * Get part material.
	 *
	 * @return Part material.
	 */
	UFUNCTION(BlueprintCallable)
		UMaterialInstanceDynamic* GetPartMaterial() { return PartMaterial; }

protected:
	/* Information of cutomizable part*/
	UPROPERTY(EditAnywhere)
		FCustomizePart CustomizePart;

	/* Whether this part uses static or skeletal meshes*/
	UPROPERTY(EditAnywhere)
		bool bSkeletalMesh;

	/* List of child static meshes affected by this part*/
	UPROPERTY(BlueprintReadOnly, Transient)
		TArray<UStaticMeshComponent*> ChildStaticMeshes;

	/* Skeletal mesh affected by this part*/
	UPROPERTY(BlueprintReadOnly, Transient)
		USkeletalMeshComponent* SkeletalMesh;

	/* Skeletal mesh material indices affected by this part*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (EditCondition = bSkeletalMesh))
		TArray<int> PartIndices;

	/* Current material applied to this part*/
	UPROPERTY(BlueprintReadOnly, Transient)
		UMaterialInstanceDynamic* PartMaterial;

#if WITH_EDITOR
public:
	/**
	 * Virtual PostEditChangeProperty in USceneComponent class.
	 */
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	/**
	 * Get editable customize part info struct.
	 *
	 * @return Customize part struct.
	 */
	FCustomizePart& GetEditablePartInfo() { return CustomizePart; }
#endif
};
