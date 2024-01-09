// Copyright Wiktor Wilga (wilgawiktor@gmail.com)

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BHGameInstance.generated.h"

/**
 * Base GameInstance class. Its BP child is set as project GameInstance.
 */
UCLASS()
class BRAINHACKER_API UBHGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	/** Need init global data for gameplay ability system to use TargetData */
	virtual void Init() override;
};
