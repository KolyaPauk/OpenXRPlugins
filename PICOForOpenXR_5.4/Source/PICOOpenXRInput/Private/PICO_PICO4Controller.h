// Copyright 2023 PICO Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IOpenXRExtensionPlugin.h"

class FPICO4ControllerPICO : public IOpenXRExtensionPlugin
{
public:
	FPICO4ControllerPICO();
	virtual ~FPICO4ControllerPICO() {}

	void Register();
	void Unregister();

	/** IOpenXRExtensionPlugin */
	virtual FString GetDisplayName() override
	{
		return FString(TEXT("PICO4ControllerPICO"));
	}
	virtual bool GetRequiredExtensions(TArray<const ANSICHAR*>& OutExtensions) override;
	virtual bool GetInteractionProfile(XrInstance InInstance, FString& OutKeyPrefix, XrPath& OutPath, bool& OutHasHaptics) override;
	virtual bool GetControllerModel(XrInstance InInstance, XrPath InInteractionProfile, XrPath InDevicePath, FSoftObjectPath& OutPath) override;
	virtual void GetControllerModelsForCooking(TArray<FSoftObjectPath>& OutPaths) override;

private:
	XrPath InteractionProfile;
	TMap<XrPath, FSoftObjectPath> ControllerModels;
	FSoftObjectPath PICO4TouchLeft = FString(TEXT("/PICOOpenXR/PICOOpenXR/Meshes/PICO4/Left/PICO4Left.PICO4Left"));
	FSoftObjectPath PICO4TouchRight = FString(TEXT("/PICOOpenXR/PICOOpenXR/Meshes/PICO4/Right/PICO4Right.PICO4Right"));
};
