// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSHUD.h"

void ARTSHUD::ActorsSelectedInRect()
{
	ActorsSelected.Empty(); //Esto para que que no se selecciones tambien los pasados
	FVector2D StartPos = RectStartPos;
	FVector2D EndPos = RectStartPos + RectSize;
	GetActorsInSelectionRectangle<AActor>(StartPos,EndPos,ActorsSelected,false);
	SelectedActors = false;
	for (AActor* Actor : ActorsSelected)
	{
		if (Actor != nullptr)
		{
			
		}
	}
}

TArray<AActor*> ARTSHUD::GetSelectedActors()
{
	return  ActorsSelected;
}

void ARTSHUD::TurnOnSelectionRect(const FVector2D InRectStartPos, const FVector2D InRectSize)
{
	RectStartPos = InRectStartPos;
	RectSize = InRectSize;
	isSelecting = true;
	
}

void ARTSHUD::TurnOffSelectionRect()
{
	isSelecting = false;
	SelectedActors = true;
}

void ARTSHUD::DrawHUD()
{
	Super::DrawHUD();
	if (isSelecting)
	{
		DrawRect(ColorRelleno,RectStartPos.X,RectStartPos.Y,RectSize.X,RectSize.Y);
	}
	if (SelectedActors)
	{
		ActorsSelectedInRect();
	}
}
