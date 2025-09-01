// Copyright 2023 PICO Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IOpenXRExtensionPlugin.h"

class FNeo3ControllerPICO : public IOpenXRExtensionPlugin
{
public:
	FNeo3ControllerPICO();
	virtual ~FNeo3ControllerPICO() {}

	void Register();
	void Unregister();

	/** IOpenXRExtensionPlugin */
	virtual FString GetDisplayName() override
	{
		return FString(TEXT("Neo3ControllerPICO"));
	}
	virtual bool GetRequiredExtensions(TArray<const ANSICHAR*>& OutExtensions) override;
	virtual bool GetInteractionProfile(XrInstance InInstance, FString& OutKeyPrefix, XrPath& OutPath, bool& OutHasHaptics) override;
	virtual bool GetControllerModel(XrInstance InInstance, XrPath InInteractionProfile, XrPath InDevicePath, FSoftObjectPath& OutPath) override;
	virtual void GetControllerModelsForCooking(TArray<FSoftObjectPath>& OutPaths) override;

private:
	XrPath InteractionProfile;
	TMap<XrPath, FSoftObjectPath> ControllerModels;
	FSoftObjectPath PicoNeo3TouchLeft = FString(TEXT("/PICOOpenXR/PICOOpenXR/Meshes/PicoNeo3/Left/Mesh_Neo3_Left.Mesh_Neo3_Left"));
	FSoftObjectPath PicoNeo3TouchRight = FString(TEXT("/PICOOpenXR/PICOOpenXR/Meshes/PicoNeo3/Right/Mesh_Neo3_Right.Mesh_Neo3_Right"));
};
