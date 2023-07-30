#include "SpawnableElement.h"

ASpawnableElement::ASpawnableElement()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
}