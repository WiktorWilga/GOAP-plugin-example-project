// Copyright Wiktor Wilga (wilgawiktor@gmail.com)


#include "BHObjectGrabHandleComponent.h"

#include "BHGrabbableObject.h"


UBHObjectGrabHandleComponent::UBHObjectGrabHandleComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBHObjectGrabHandleComponent::BeginPlay()
{
	Super::BeginPlay();

	// cache required component
	OwnerMesh = Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	ensureMsgf(OwnerMesh, TEXT("Owner actor of UBHObjectGrabHandleComponent need to has skeletal mesh!"));
}

bool UBHObjectGrabHandleComponent::GrabObject(TScriptInterface<IBHGrabbableObject> Object)
{
	AActor* GrabbableActor = Cast<AActor>(Object.GetObject());
	
	if(CurrentObject || !GrabbableActor)
		return false;

	if(!IBHGrabbableObject::Execute_CanBeGrabbed(GrabbableActor))
		return false;
	
	// attach object
	GrabbableActor->AttachToComponent(OwnerMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true), SocketName);
	CurrentObject = Object;
	IBHGrabbableObject::Execute_OnGrab(GrabbableActor, this);
	return true;
}

bool UBHObjectGrabHandleComponent::ReleaseObject()
{
	AActor* GrabbableActor = Cast<AActor>(CurrentObject.GetObject());
	
	if(!GrabbableActor || !IBHGrabbableObject::Execute_CanBeReleased(GrabbableActor))
		return false;

	// detach object
	GrabbableActor->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld,
		EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, true));
	IBHGrabbableObject::Execute_OnRelease(GrabbableActor, this);
	CurrentObject = nullptr;
	return true;
}
