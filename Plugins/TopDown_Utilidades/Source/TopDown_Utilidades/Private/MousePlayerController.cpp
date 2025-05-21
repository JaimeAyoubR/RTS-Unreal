// Fill out your copyright notice in the Description page of Project Settings.


#include "MousePlayerController.h"

#include "BasePawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


AMousePlayerController::AMousePlayerController()
{
	bShowMouseCursor = true;
}

void AMousePlayerController::BeginPlay()
{
	Super::BeginPlay();
	HUD = Cast<ARTSHUD>(GetHUD());
}

void AMousePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputMappingContext == nullptr)
	{
		return;
	}
	UEnhancedInputLocalPlayerSubsystem* Subsystem;
	Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem != nullptr)
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
		UE_LOG(LogTemp, Display, TEXT("InputMapping Agregado"));
	}
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		//Agregar la funcion de mover
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Completed, this,
		                                   &AMousePlayerController::Select);

		//Secuencia para hacer la seleccion grande y que aparezca un rectangulo
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Started, this,
		                                   &AMousePlayerController::StartSelect);
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Triggered, this,
		                                   &AMousePlayerController::OnGoingSelect);
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Completed, this,
		                                   &AMousePlayerController::EndSelect);


		//Agregar la funcion de command
		EnhancedInputComponent->BindAction(CommandAction, ETriggerEvent::Completed, this,
		                                   &AMousePlayerController::CommandSelectedActor);
	}
}

void AMousePlayerController::Select(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Display, TEXT("SelectAction"));

	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Camera, false, HitResult);

	//Deseleccionar el personaje anterior
	if (HitActor)
	{
		if (HitActor->GetClass()->ImplementsInterface(USelectableInterface::StaticClass()))
		{
			ISelectableInterface::Execute_SelectActor(HitActor, false);
		}
	}
	HitActor = HitResult.GetActor();

	if (HitActor)
	{
		UE_LOG(LogTemp, Display, TEXT("Click Personaje: %s"), *HitActor->GetName());

		//Vemos si lo que clickeamos contiene SelectableInterface, o sea,
		//Si es algo que podemos seleccionar en primer lugar
		if (HitActor->GetClass()->ImplementsInterface(USelectableInterface::StaticClass()))

		{
			ISelectableInterface::Execute_SelectActor(HitActor, true);
		}
	}
}

void AMousePlayerController::CommandSelectedActor(const FInputActionValue& value)
{
	if (HitActor)
	{
		UE_LOG(LogTemp, Display, TEXT("Commanding %s"), *HitActor->GetName());

		if (HitActor->GetClass()->ImplementsInterface(UNavegateInterface::StaticClass()))
		//Vemos si lo que clickeamos tiene la clase de navegar, si no, no tendria porque moverse
		{
			FHitResult HitResult;
			GetHitResultUnderCursor(ECC_Camera, false, HitResult);
			if (HitResult.bBlockingHit)
			{
				INavegateInterface::Execute_MoveToLocation(HitActor, HitResult.Location);
			}
		}
	}
}

void AMousePlayerController::StartSelect(const FInputActionValue& value)
{
	GetMousePosition(mousePosX, mousePosY);
	SelectStartPosition = FVector2D(mousePosX, mousePosY);
}

void AMousePlayerController::OnGoingSelect(const FInputActionValue& value)
{
	GetMousePosition(mousePosX, mousePosY);
	RectangleSize = FVector2D(mousePosX - SelectStartPosition.X, mousePosY - SelectStartPosition.Y);
	if (HUD != nullptr)
	{
		HUD->TurnOnSelectionRect(SelectStartPosition, RectangleSize);
	}
}

void AMousePlayerController::EndSelect(const FInputActionValue& value)
{
	if (HUD != nullptr)
	{
		HUD->TurnOffSelectionRect();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,
		                                       &AMousePlayerController::SelectActors, 0.02f, false);
	}
}

void AMousePlayerController::SelectActors()
{
	if (HUD != nullptr)
	{
		for (AActor* Actor : SelectedActors)
		{
			UE_LOG(LogTemp, Display, TEXT("SelectActors: %s"), *Actor->GetName());
			if (Actor != nullptr)
			{
				if (Actor->GetClass()->ImplementsInterface(USelectableInterface::StaticClass()))
				{
					ISelectableInterface::Execute_SelectActor(Actor, false); //Para desactivar los anteriores
				}
			}
		}
		SelectedActors = HUD->GetSelectedActors();
		for (AActor* Actor : SelectedActors)
		{
			if (Actor != nullptr)
			{
				if (Actor->GetClass()->ImplementsInterface(USelectableInterface::StaticClass()))
				{
					ISelectableInterface::Execute_SelectActor(Actor, true);
				}
			}
		}
	}
}
