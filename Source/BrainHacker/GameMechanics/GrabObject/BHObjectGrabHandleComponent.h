// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BHObjectGrabHandleComponent.generated.h"


class IBHGrabbableObject;

/**
 * Component allows grab objects which implement IBHGrabbableObject. It manages objects.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BRAINHACKER_API UBHObjectGrabHandleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UBHObjectGrabHandleComponent();

	/** Grab object. Return true if successfully grabbed. */
	UFUNCTION(BlueprintCallable)
	bool GrabObject(TScriptInterface<IBHGrabbableObject> Object);
	/** Release currently held item. Return true if action performed. */
	UFUNCTION(BlueprintCallable)
	bool ReleaseObject();

	/** Return currently held object or null if not holding any item. */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE AActor* GetCurrentObject() { return Cast<AActor>(CurrentObject.GetObject()); }

protected:

	virtual void BeginPlay() override;

	/** Socket on owner actor's mesh to which object will be attached. */
	UPROPERTY(EditDefaultsOnly)
	FName SocketName;

private:

	/** Reference to currently held item. Null if we are currently not holding any item. */
	TScriptInterface<IBHGrabbableObject> CurrentObject = nullptr;

	/** Reference to owner actor's mesh, to which will be attached object (in socket of name SocketName). */
	USkeletalMeshComponent* OwnerMesh;
		
};
