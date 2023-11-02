#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class AWeapon;
class UPhysicsHandleComponent;
class UCameraComponent;
class UArrowComponent;
class UInventoryComponent;
class UItemObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponEquip, AWeapon*, Weapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponUnEquip);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CYBERLIFE_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionComponent();

	FOnWeaponEquip OnWeaponEquip;
	FOnWeaponUnEquip OnWeaponUnEquip;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interact", meta=(AllowPrivateAccess))
	float InteractDistance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Grabing", meta=(AllowPrivateAccess))
	float ForceThrow;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grabing", meta=(AllowPrivateAccess))
	UArrowComponent* DefaultGrabObjectLocation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grabing", meta=(AllowPrivateAccess))
	UPrimitiveComponent* HoldingObject;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grabing", meta=(AllowPrivateAccess))
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grabing", meta=(AllowPrivateAccess))
	UPhysicsHandleComponent* PhysicsHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta=(AllowPrivateAccess))
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta=(AllowPrivateAccess))
	AWeapon* EquipedWeapon;

public:
	void Init(UPhysicsHandleComponent* PhysicsHandleComponent, UArrowComponent* DefaultLocation, UCameraComponent* CameraComponentParam);
	void Interact();
	UFUNCTION(BlueprintCallable)
	void SetInventoryBP(UInventoryComponent* InventoryComponentBP);

	void AttackWeapon();

	bool IsHoldingObject() const;

	void ThrowObject();

	FORCEINLINE UInventoryComponent* GetInventory() const { return InventoryComponent; }

	FORCEINLINE AWeapon* GetWaepon() const { return EquipedWeapon; }
	
private:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;
	
	void TraceForObject();
	void GrabObject(const FHitResult HitResult);
	void DropObject();
	
	UFUNCTION()
	void EquipWeapon(UItemObject* WeaponItemObject);
	UFUNCTION()
	void UnEquipWeapon();

	template<typename T>
	T* CreateBlueprintDefferd(UWorld* World, const FString& Name, const FTransform& Transform = FTransform::Identity)
	{
		const UBlueprint* Blueprint = LoadObject<UBlueprint>(nullptr, *Name);
		return (World && Blueprint) ? World->SpawnActorDeferred<T>(Blueprint->GeneratedClass, Transform) : nullptr;
	}
		
};
