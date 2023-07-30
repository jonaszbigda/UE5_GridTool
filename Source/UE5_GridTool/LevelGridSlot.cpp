#include "LevelGridSlot.h"

// Sets default values for this component's properties
ULevelGridSlot::ULevelGridSlot()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void ULevelGridSlot::BeginPlay()
{
	Super::BeginPlay();
	Spawn();
}

UClass* ULevelGridSlot::ResolveClass() {
	UClass* Class = nullptr;
	if (!Object.IsNull()) {
		if (!Object.IsValid()) {
			Class = Object.LoadSynchronous();
		}
		else {
			Class = Object.Get();
		}
	} 
	return Class;
}

void ULevelGridSlot::Spawn() {
	UClass* Class = ResolveClass();

	if (IsValid(Class)) {
		FActorSpawnParameters SpawnParams;
		GetWorld()->SpawnActor<ASpawnableElement>(Class, this->GetComponentLocation(), this->GetComponentRotation(), SpawnParams);
	}
	this->DestroyComponent();
}