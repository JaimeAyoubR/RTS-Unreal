// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuilding.h"

#include "Components/BoxComponent.h"
#include "Components/Button.h"
#include "Misc/MapErrors.h"

// Sets default values
ABaseBuilding::ABaseBuilding()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	StaticMesh->SetupAttachment(BoxComponent);
	//Create Box
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	//
	// BoxComponent->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	//
	// BoxComponent->SetupAttachment(RootComponent);
	

	//Crete Indicator
	SelectIndicator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SelectIndicator"));
	SelectIndicator->SetupAttachment(RootComponent);
	SelectIndicator->SetHiddenInGame(true);
	SelectIndicator->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ABaseBuilding::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Display, TEXT("AAAAAAAAAAAAAAH"));
}

void ABaseBuilding::SelectActor_Implementation(const bool select)
{
	SelectIndicator->SetHiddenInGame(!select);
}
