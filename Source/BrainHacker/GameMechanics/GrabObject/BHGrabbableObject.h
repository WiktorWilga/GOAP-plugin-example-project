// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BHGrabbableObject.generated.h"


class UBHObjectGrabHandleComponent;

UINTERFACE(MinimalAPI, BlueprintType)
class UBHGrabbableObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * This interface have to be implemented by actor to allow grab it by UBHObjectGrabHandleComponent.
 */
class BRAINHACKER_API IBHGrabbableObject
{
	GENERATED_BODY()

public:

	/** Return true if this object currently ca by grabbed. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CanBeGrabbed();

	/** Return true if this object currently ca by released. It only applies to the situation when object is currently held. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CanBeReleased();

	/** Called when object is grabbed by UBHObjectGrabHandleComponent. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnGrab(UBHObjectGrabHandleComponent* Instigator);

	/** Called when object is released from UBHObjectGrabHandleComponent. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnRelease(UBHObjectGrabHandleComponent* Instigator);
};
