// Mamont Protaction copy rights


#include "GrabingObject.h"

AGrabingObject::AGrabingObject()
{
	OnActorHit.AddDynamic(this, &AGrabingObject::OnHit);
}

void AGrabingObject::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AGrabingObject::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	SetActorTickEnabled(false);
}
