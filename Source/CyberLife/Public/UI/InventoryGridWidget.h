// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "UI/GridElements.h"
#include "InventoryGridWidget.generated.h"

class UInventoryComponentInterface;
class UItemData;
class UInventoryComponent;
UCLASS()
class CYBERLIFE_API UInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	TScriptInterface<UInventoryComponentInterface> InventoryInterface;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UInventoryComponent* InventoryComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	float TileSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	TArray<FLine> Lines;
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	FIntPoint DragenItemTopLeftTIle;
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool bDragDropLocation;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UBorder* GridBorder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UCanvasPanel* GridCanvasPanel;

public:
	void Init(UInventoryComponent* Inventory, const float SizeTile);

private:
	void CreateLineSegemnts();
	void CreateSlotGrid() const;
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnInit();

	UFUNCTION(BlueprintCallable)
	UItemData* GetPayload(UDragDropOperation* DragDropOperation) const;

	UFUNCTION(BlueprintPure)
	bool IsSpaceForPayload(UItemData* InItem) const;

	UFUNCTION(BlueprintCallable)
	void OnDropItem(UDragDropOperation* InOperation);

	UFUNCTION(BlueprintCallable)
	void GetMousePositionInTile(FVector2D InMousePosition, bool& bRight, bool& bDown) const;

	void OnRemoveItem(UItemData* InItemObject);

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
};