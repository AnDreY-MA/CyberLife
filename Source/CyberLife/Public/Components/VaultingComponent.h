#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VaultingComponent.generated.h"

class UCapsuleComponent;

UENUM(BlueprintType)
enum class EVaultState : uint8
{
	EVS_NotVault UMETA(DisplayName = "NotVaulting"),
	EVS_Vaulting UMETA(DisplayName = "Vaulting")
};

class ACharacter;
class UUserWidget;


UCLASS( ClassGroup=(Custom), Blueprintable )
class CYBERLIFE_API UVaultingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UVaultingComponent();

	UFUNCTION(BlueprintCallable)
	void Vault();

	UFUNCTION(BlueprintCallable)
	bool CanVault();

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Position", meta=(AllowPrivateAccess))
	FVector StartingPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Position", meta=(AllowPrivateAccess))
	FVector EndPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	float MinVaultingHeight { 70.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	float MaxVaultingHeight { 150.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	float Progress { 0.0f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess))
	float VaultSpeed { 0.5f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	EVaultState VaultState { EVaultState::EVS_NotVault };

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	TSubclassOf<UUserWidget> VaultWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UUserWidget* VaultWidget;

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, meta=(BlueprintProtected))
	void VaultTick(float DeltaSeconds);
	
	UFUNCTION(BlueprintCallable, meta=(BlueprintProtected))
	FHitResult TraceToVault(UCapsuleComponent* CapsuleComponent) const;

	void CheckVault();
	
	UFUNCTION(BlueprintCallable, meta=(BlueprintProtected))
	FVector CanVaultToHit(UCapsuleComponent* Capsule, const FHitResult& HitResult);
	UFUNCTION(BlueprintCallable, meta=(BlueprintProtected))
	bool CheckCapsuleCollision(FVector Center, float HalfHeight, float Radius) const;
		
};
