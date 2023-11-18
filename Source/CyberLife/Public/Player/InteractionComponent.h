#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "Narrative/NoteData.h"
#include "InteractionComponent.generated.h"

class AItem;
class AWeapon;
class UPhysicsHandleComponent;
class UCameraComponent;
class UArrowComponent;
class UItemObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponEquip, AWeapon*, Weapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponUnEquip);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFlashlightPickUp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNoteLogPickUp, FNoteData, NoteData);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CYBERLIFE_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionComponent();

	FOnWeaponEquip OnWeaponEquip;
	FOnWeaponUnEquip OnWeaponUnEquip;
	FOnFlashlightPickUp OnFlashlightPickUp;
	FOnNoteLogPickUp OnNoteLogPickUp;

	void Init(UPhysicsHandleComponent* PhysicsHandleComponent, UArrowComponent* DefaultLocation, UCameraComponent* CameraComponentParam);
	void Interact();
	
	void PickUpNote(const FNoteData& NoteData);
	bool IsHoldingObject() const;

	void ThrowObject();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interact", meta=(AllowPrivateAccess))
	float InteractDistance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Grabing", meta=(AllowPrivateAccess))
	float ForceThrow;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grabing", meta=(AllowPrivateAccess))
	TObjectPtr<UArrowComponent> DefaultGrabObjectLocation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grabing", meta=(AllowPrivateAccess))
	TObjectPtr<UPrimitiveComponent> HoldingObject;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grabing", meta=(AllowPrivateAccess))
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grabing", meta=(AllowPrivateAccess))
	UPhysicsHandleComponent* PhysicsHandle;

private:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;
	
	void TraceForObject();
	void GrabObject(const FHitResult HitResult);
	void DropObject();
	
};
