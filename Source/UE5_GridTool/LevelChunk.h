#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelGridSlot.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SpawnableElement.h"
#include "LevelChunk.generated.h"

UCLASS()
class UE5_GRIDTOOL_API ALevelChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	ALevelChunk();

	// --- Variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Setup")
	int32 SizeX = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Setup")
	int32 SizeY = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Setup")
	int32 SizeZ = 4;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<ULevelGridSlot*> Slots;

	UPROPERTY()
	TArray<UStaticMeshComponent*> PreviewMeshes;

	// --- Functions

	// Remove preview elements
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Actor Methods")
	void HidePreview();

	// Temporarily spawn each element in this chunk
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Actor Methods")
	void PreviewElements();

private:
	void BeginPlay() override;

	UFUNCTION()
	void SetupGrid();

	UFUNCTION()
	void CleanupComponents();

};
