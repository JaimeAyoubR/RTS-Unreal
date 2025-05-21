#pragma once

#include "CoreMinimal.h"
#include "NavegateInterface.h"
#include "SelectableInterface.h"
#include "SelectableInterface.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h" //Todos los includes van antes que este


class UCapsuleComponent;

class UFloatingPawnMovement;

class USkeletalMeshComponent;

class UStaticMeshComponent;

UCLASS()

class TOPDOWN_UTILIDADES_API ABasePawn : public APawn, public ISelectableInterface, public INavegateInterface
{
	GENERATED_BODY()

private:
	//Capsule Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> Capsule;
	//Skeleton Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> SkeletMesh;
	//Floating PawnMovement Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;
	//Indicador si esta seleccionado
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> IndicatorSelect;

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move();

	FVector MoveTargetLocation = FVector::ZeroVector;
	bool bIsMoving = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	float DistanceOffset = 50.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	float RotationSpeed = 5.0f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void SelectActorLocal(const bool isSelected);

	UFUNCTION()
	void DeselectActor(const bool isSelected);

	void SelectActor_Implementation(const bool select) override;

	void MoveToLocation_Implementation(const FVector location) override;
};
