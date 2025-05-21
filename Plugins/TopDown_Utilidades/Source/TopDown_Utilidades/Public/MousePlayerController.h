#pragma once

#include "CoreMinimal.h"
#include "RTSHUD.h"
#include "GameFramework/PlayerController.h"
#include "MousePlayerController.generated.h"

/**
 * 
 */
class UInputMappingContext;
class UInputAction;
class ABasePawn;
class ARTSHUD;
struct FInputActionValue;

UCLASS()

class TOPDOWN_UTILIDADES_API AMousePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMousePlayerController();

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = true))
	UInputMappingContext* InputMappingContext;

protected:

	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

	//Funcion para seleccionar un personaje o edificio
	void Select(const FInputActionValue& value);
	//Funcion para poder manejar a los personajes
	void CommandSelectedActor(const FInputActionValue& value);
	//Funciones para hacer una seleccion grande
	void StartSelect(const FInputActionValue& value);
	void OnGoingSelect(const FInputActionValue& value);
	void EndSelect(const FInputActionValue& value);
	void SelectActors();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess=true))
	TObjectPtr<UInputAction> SelectAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess=true))
	TObjectPtr<UInputAction> CommandAction;


	UPROPERTY()
	TObjectPtr<AActor> HitActor;
	UPROPERTY()
	TObjectPtr<ARTSHUD> HUD;
	
	FVector2D SelectStartPosition;
	FVector2D RectangleSize;
	float mousePosX, mousePosY;
	TArray<AActor*> SelectedActors;
	FTimerHandle TimerHandle;
};
