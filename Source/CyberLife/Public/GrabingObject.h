// Mamont Protaction copy rights

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "LaunchableInterface.h"
#include "GrabingObject.generated.h"

/**
 * 
 */
UCLASS()
class CYBERLIFE_API AGrabingObject : public AInteractableActor, public ILaunchableInterface
{
	GENERATED_BODY()

public:
	
	AGrabingObject();
	
protected:
	virtual void Tick(float DeltaSeconds) override;

private:
	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

};
