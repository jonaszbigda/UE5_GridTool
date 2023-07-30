#include "LevelChunk.h"

ALevelChunk::ALevelChunk()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetupGrid();
}

// Called when the game starts or when spawned
void ALevelChunk::BeginPlay()
{
	Super::BeginPlay();
	CleanupComponents();
}

void ALevelChunk::SetupGrid() {
	// Set XYZ base points. Next we will offset each next slot from these points
	float ZBase = -(100.f * (SizeZ - 1) / 2);
	float XBase = -(100.f * (SizeX - 1) / 2);
	float YBase = -(100.f * (SizeY - 1) / 2);
	int32 Count = 0;

	// Z axis loop
	for (int32 z = 0; z < SizeZ; ++z) {
		float ZOffset = ZBase + (100.f * z);

		// X axis loop
		for (int32 x = 0; x < SizeX; ++x) {
			float XOffset = XBase + (100.f * x);

			// Y axis loop
			for (int32 y = 0; y < SizeY; ++y) {
				float YOffset = YBase + (100.f * y);
				ULevelGridSlot* ThisSlot = CreateDefaultSubobject<ULevelGridSlot>(*FString::Printf(TEXT("GridSlot %i"), Count));
				UStaticMeshComponent* PreviewMesh = CreateDefaultSubobject<UStaticMeshComponent>(*FString::Printf(TEXT("PreviewMesh %i"), Count));
				ThisSlot->Index = Count;
				ThisSlot->SetupAttachment(RootComponent);
				ThisSlot->EditorScale = 0.25f;
				ThisSlot->SetRelativeLocation(FVector(XOffset, YOffset, ZOffset));
				PreviewMesh->SetRelativeLocation(FVector(XOffset, YOffset, ZOffset));
				Slots.Add(ThisSlot);
				PreviewMeshes.Add(PreviewMesh);
				Count++;
			}
		}
	}
}

// Preview elements --- Go through all of the slots and if given slot has any class chosen, and that class has any static mesh, set corresponding PreviewMesh to display that mesh.
void ALevelChunk::PreviewElements() {
	for (ULevelGridSlot* Slot : Slots) {
		if (IsValid(Slot)) {

			UClass* Class = Slot->ResolveClass();
			if (IsValid(Class)) {

				ASpawnableElement* DefaultObject = Cast<ASpawnableElement>(Class->GetDefaultObject());
				if (IsValid(DefaultObject->StaticMesh)) {
					PreviewMeshes[Slot->Index]->SetStaticMesh(DefaultObject->StaticMesh->GetStaticMesh());
				}
			}
		}
	}
}

// Set all PreviewMeshes to nullptr
void ALevelChunk::HidePreview() {
	int32 Count = 0;
	for (UStaticMeshComponent* PreviewMesh : PreviewMeshes) {
		if (IsValid(PreviewMesh)) {

			PreviewMesh->SetStaticMesh(nullptr);
		}
		Count++;
	}
}

void ALevelChunk::CleanupComponents() {
	for (UStaticMeshComponent* PreviewMesh : PreviewMeshes) {
		PreviewMesh->UnregisterComponent();
	}
	PreviewMeshes.Empty();
}