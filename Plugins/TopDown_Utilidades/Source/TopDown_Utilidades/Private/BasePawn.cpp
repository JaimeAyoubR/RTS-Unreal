// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
//#include "KismetMathLibrary.generated.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIController.h"



// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Creamos la capsula
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	//FVector ScalaNueva = FVector(1.0f, 1.0f, 90.0f);

	//Capsule->SetWorldScale3D(ScalaNueva);
	RootComponent = Capsule;
	Capsule->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	//Creamos el Esqueleto
	SkeletMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletMesh"));
	SkeletMesh->SetupAttachment(RootComponent);

	//Creamos el movimiento
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	//Creamos el Indicador
	IndicatorSelect = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IndicatorSelect"));
	IndicatorSelect->SetupAttachment(RootComponent);
	IndicatorSelect->SetHiddenInGame(true);
	IndicatorSelect->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

}

void ABasePawn::Move()
{
	if (!bIsMoving)
	{
		return;
	}

	FVector MoveDirection = (MoveTargetLocation - GetActorLocation());
	if (MoveDirection.Length() < DistanceOffset)
	{
		UE_LOG(LogTemp, Display, TEXT("Moving"));
		bIsMoving = false;
		return;
	}
	MoveDirection.Normalize(1);
	

	FRotator RotateDirection = UKismetMathLibrary::MakeRotFromX(MoveDirection);
	RotateDirection.Pitch = 0;
	RotateDirection.Roll = 0;

	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), RotateDirection, GetWorld()->GetDeltaSeconds(),
	                                        RotationSpeed);
	SetActorRotation(NewRotation);
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("Actor Location: %s"), *GetActorLocation().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Mesh Relative Location: %s"), *SkeletMesh->GetRelativeLocation().ToString());
	Move();
}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABasePawn::SelectActorLocal(const bool isSelected)
{
	IndicatorSelect->SetHiddenInGame(!isSelected);
}

void ABasePawn::DeselectActor(const bool isSelected)
{
}

void ABasePawn::SelectActor_Implementation(const bool select)
{
	IndicatorSelect->SetHiddenInGame(!select);
}

void ABasePawn::MoveToLocation_Implementation(const FVector location)
{
	UE_LOG(LogTemp, Display, TEXT("Naveg"));
	MoveTargetLocation = location + FVector(0, 0, GetDefaultHalfHeight());
	bIsMoving = true;

	AAIController* AIController = Cast<AAIController>(GetController());
	AIController->MoveToLocation(location,DistanceOffset);
}
