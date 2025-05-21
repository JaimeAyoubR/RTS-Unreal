// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllerPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AControllerPawn::AControllerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Crar la capusla (el player por asi decirlo)
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;

	//Crear el Spring Arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));


	//Crear camara
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	//Unir camara/SpringArm/Capsula
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
	//Modificar el como se ve la camara y la distancia entre camara - jugador
	SpringArm->TargetArmLength = 1000;
	//Se pone Orthographic para darle ese efecto tipico de RTS
	Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

// Called when the game starts or when spawned
void AControllerPawn::BeginPlay()
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	Super::BeginPlay();
}

void AControllerPawn::Move(const FInputActionValue& Value)
{
	const FVector2D InputMovement = Value.Get<FVector2D>();
	if (Controller)
	{
		
		const FRotator Rotator = Controller->GetControlRotation();
		const FRotator YRotation(0, Rotator.Yaw, 0);

		const FVector Forward = FRotationMatrix(YRotation).GetUnitAxis(EAxis::X);
		const FVector Right = FRotationMatrix(YRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Forward, InputMovement.Y);
		AddMovementInput(Right, InputMovement.X);
	}
}

void AControllerPawn::Zoom(const FInputActionValue& Value)
{
	const float ZoomDirection = Value.Get<float>();
	if (Controller)
	{
		float DirectionZoom = Camera->OrthoWidth + ZoomDirection * -ZoomSpeed;
		DirectionZoom = FMath::Clamp(DirectionZoom, 200.0f, 2000.0f); //Esto para que no puedas hacer zoom infinito

		Camera->OrthoWidth = DirectionZoom;
	}
}

// Called every frame
void AControllerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AControllerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Agregar la funcion de mover
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AControllerPawn::Move);

		//Agregar la funcion de hacer zoom
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &AControllerPawn::Zoom);
	}
}
