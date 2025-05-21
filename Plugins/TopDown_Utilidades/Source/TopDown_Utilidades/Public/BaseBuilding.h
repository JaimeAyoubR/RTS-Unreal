// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SelectableInterface.h"
#include "BaseBuilding.generated.h"

class UBoxComponent;
UCLASS()
class TOPDOWN_UTILIDADES_API ABaseBuilding : public AActor,public ISelectableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBuilding();
	private:
	//Box Collider
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Building,meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoxComponent;
	//Mesh
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Building,meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	//Select Indicator
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Building,meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> SelectIndicator;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SelectActor_Implementation(const bool select) override;

};
