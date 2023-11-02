#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

class UItemObject;

UCLASS()
class CYBERLIFE_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SpawnItemActor(UItemObject* ItemObject, AActor* Actor, bool bClampGround);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	float SpawnDistance;

	template<typename T>
	T* CreateBlueprintDefferd(UWorld* World, const FString& Name, const FTransform& Transform = FTransform::Identity)
	{
		const UBlueprint* Blueprint = LoadObject<UBlueprint>(nullptr, *Name);
		return (World && Blueprint) ? World->SpawnActorDeferred<T>(Blueprint->GeneratedClass, Transform) : nullptr;
	}
};