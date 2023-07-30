// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnableElement.h"
#include "Components/BillboardComponent.h"
#include "LevelGridSlot.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_GRIDTOOL_API ULevelGridSlot : public UBillboardComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULevelGridSlot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Setup")
	TSoftClassPtr<ASpawnableElement> Object;

	UPROPERTY()
	int32 Index;

	UFUNCTION()
	UClass* ResolveClass();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void Spawn();
};
