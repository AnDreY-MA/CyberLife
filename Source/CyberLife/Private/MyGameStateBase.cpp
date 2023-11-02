#include "MyGameStateBase.h"

#include "Items/Item.h"
#include "Items/ItemObject.h"

void AMyGameStateBase::SpawnItemActor(UItemObject* ItemObject, AActor* Actor, bool bClampGround)
{
	FVector SpawnLocation = Actor->GetActorLocation() + Actor->GetActorForwardVector() * SpawnDistance;
	if (bClampGround)
	{
		FHitResult HitResult;
		if(GetWorld()->LineTraceSingleByChannel(HitResult,SpawnLocation, SpawnLocation - FVector{0.0f, 0.0f, 1000.0f}, ECollisionChannel::ECC_Visibility))
		{
			SpawnLocation = HitResult.Location;
		}
	}

	auto* Item = CreateBlueprintDefferd<AItem>(GetWorld(), ItemObject->GetBPItemName(), FTransform(SpawnLocation));
	Item->SetItemObject(ItemObject);
}
