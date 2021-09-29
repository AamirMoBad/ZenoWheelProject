// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "../Structs/CustomizePart.h"
#include "PartComponent.generated.h"


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
	 * Initialize part component.
	 */
	UFUNCTION(BlueprintCallable)
		void InitPartComponent();

	/**
	 * Change customize part material to default material.
	 */
	UFUNCTION(BlueprintCallable)
		void DefaultPartMaterial();

	/**
	 * Change customize part material.
	 *
	 * @param mat : Material to apply.
	 */
	UFUNCTION(BlueprintCallable)
		void ChangePartMaterial(UMaterialInterface* mat);

	/**
	 * Get children static mesh components.
	 *
	 * @return Array of child static mesh components.
	 */
	UFUNCTION(BlueprintCallable)
		const TArray<UStaticMeshComponent*>& GetChildrenMeshes() const { return DefaultMeshes; }

	/**
	 * Get whether there are any children components (static mesh and body kit).
	 *
	 * @return True if part has no children components, false otherwise.
	 */
	UFUNCTION(BlueprintCallable)
		bool IsEmpty() const { return DefaultMeshes.Num() == 0; }

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
	/**
	 * Virtual BeginPlay in USceneComponent class.
	 */
	virtual void BeginPlay() override;

	/**
	 * Virtual OnChildAttached in USceneComponent class.
	 *
	 * @param ChildComponent : Child component to added.
	 */
	virtual void OnChildAttached(USceneComponent* ChildComponent) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Part Component")
		FCustomizePart CustomizePart;

	UPROPERTY(BlueprintReadOnly)
		TArray<UStaticMeshComponent*> DefaultMeshes;

	UPROPERTY(BlueprintReadOnly)
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
