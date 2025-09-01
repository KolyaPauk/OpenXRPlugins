// Copyright 2023 PICO Inc. All Rights Reserved.

#include "PICO_PICO4Controller.h"
#include "OpenXRCore.h"
#include "PICO_InputModule.h"

#define LOCTEXT_NAMESPACE "FPICO4ControllerPICO"

// Left
const FKey PICO4_Left_X_Click("PICO4_Left_X_Click");
const FKey PICO4_Left_Y_Click("PICO4_Left_Y_Click");
const FKey PICO4_Left_X_Touch("PICO4_Left_X_Touch");
const FKey PICO4_Left_Y_Touch("PICO4_Left_Y_Touch");
const FKey PICO4_Left_Menu_Click("PICO4_Left_Menu_Click");
const FKey PICO4_Left_Grip("PICO4_Left_Grip_Click");
const FKey PICO4_Left_Grip_Axis("PICO4_Left_Grip_Axis");
const FKey PICO4_Left_Trigger("PICO4_Left_Trigger_Click");
const FKey PICO4_Left_Trigger_Axis("PICO4_Left_Trigger_Axis");
const FKey PICO4_Left_Trigger_Touch("PICO4_Left_Trigger_Touch");
const FKey PICO4_Left_Thumbstick_2D("PICO4_Left_Thumbstick_2D");
const FKey PICO4_Left_Thumbstick_X("PICO4_Left_Thumbstick_X");
const FKey PICO4_Left_Thumbstick_Y("PICO4_Left_Thumbstick_Y");
const FKey PICO4_Left_Thumbstick("PICO4_Left_Thumbstick_Click");
const FKey PICO4_Left_Thumbstick_Touch("PICO4_Left_Thumbstick_Touch");
//Right
const FKey PICO4_Right_A_Click("PICO4_Right_A_Click");
const FKey PICO4_Right_B_Click("PICO4_Right_B_Click");
const FKey PICO4_Right_A_Touch("PICO4_Right_A_Touch");
const FKey PICO4_Right_B_Touch("PICO4_Right_B_Touch");
const FKey PICO4_Right_Grip("PICO4_Right_Grip_Click");
const FKey PICO4_Right_Grip_Axis("PICO4_Right_Grip_Axis");
const FKey PICO4_Right_Trigger("PICO4_Right_Trigger_Click");
const FKey PICO4_Right_Trigger_Axis("PICO4_Right_Trigger_Axis");
const FKey PICO4_Right_Trigger_Touch("PICO4_Right_Trigger_Touch");
const FKey PICO4_Right_Thumbstick_2D("PICO4_Right_Thumbstick_2D");
const FKey PICO4_Right_Thumbstick_X("PICO4_Right_Thumbstick_X");
const FKey PICO4_Right_Thumbstick_Y("PICO4_Right_Thumbstick_Y");
const FKey PICO4_Right_Thumbstick("PICO4_Right_Thumbstick_Click");
const FKey PICO4_Right_Thumbstick_Touch("PICO4_Right_Thumbstick_Touch");

FPICO4ControllerPICO::FPICO4ControllerPICO()
{
}

void FPICO4ControllerPICO::Register()
{
	RegisterOpenXRExtensionModularFeature();

	EKeys::AddMenuCategoryDisplayInfo("PICO4", LOCTEXT("PICO4SubCategory", "PICO 4 Controller"), TEXT("GraphEditor.PadEvent_16x"));

	// Left
	EKeys::AddKey(FKeyDetails(PICO4_Left_X_Click, LOCTEXT("PICO4_Left_X_Click", "PICO 4 (L) X Press"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Left_Y_Click, LOCTEXT("PICO4_Left_Y_Click", "PICO 4 (L) Y Press"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Left_X_Touch, LOCTEXT("PICO4_Left_X_Touch", "PICO 4 (L) X Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Left_Y_Touch, LOCTEXT("PICO4_Left_Y_Touch", "PICO 4 (L) Y Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Left_Menu_Click, LOCTEXT("PICO4_Left_Menu_Click", "PICO 4 (L) Menu"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Left_Grip, LOCTEXT("PICO4_Left_Grip_Click", "PICO 4 (L) Grip"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Left_Grip_Axis, LOCTEXT("PICO4_Left_Grip_Axis", "PICO 4 (L) Grip Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Left_Trigger, LOCTEXT("PICO4_Left_Trigger_Click", "PICO 4 (L) Trigger"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Left_Trigger_Axis, LOCTEXT("PICO4_Left_Trigger_Axis", "PICO 4 (L) Trigger Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Left_Trigger_Touch, LOCTEXT("PICO4_Left_Trigger_Touch", "PICO 4 (L) Trigger Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Left_Thumbstick_X, LOCTEXT("PICO4_Left_Thumbstick_X", "PICO 4 (L) Thumbstick X"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Left_Thumbstick_Y, LOCTEXT("PICO4_Left_Thumbstick_Y", "PICO 4 (L) Thumbstick Y"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddPairedKey(FKeyDetails(PICO4_Left_Thumbstick_2D, LOCTEXT("PICO4_Left_Thumbstick_2D", "PICO 4 (L) Thumbstick 2D-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis2D | FKeyDetails::NotBlueprintBindableKey, "PICO4"), PICO4_Left_Thumbstick_X, PICO4_Left_Thumbstick_Y);
	EKeys::AddKey(FKeyDetails(PICO4_Left_Thumbstick, LOCTEXT("PICO4_Left_Thumbstick_Click", "PICO 4 (L) Thumbstick"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Left_Thumbstick_Touch, LOCTEXT("PICO4_Left_Thumbstick_Touch", "PICO 4 (L) Thumbstick Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4"));

	// Right
	EKeys::AddKey(FKeyDetails(PICO4_Right_A_Click, LOCTEXT("PICO4_Right_A_Click", "PICO 4 (R) A Press"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Right_B_Click, LOCTEXT("PICO4_Right_B_Click", "PICO 4 (R) B Press"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Right_A_Touch, LOCTEXT("PICO4_Right_A_Touch", "PICO 4 (R) A Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Right_B_Touch, LOCTEXT("PICO4_Right_B_Touch", "PICO 4 (R) B Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Right_Grip, LOCTEXT("PICO4_Right_Grip_Click", "PICO 4 (R) Grip"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Right_Grip_Axis, LOCTEXT("PICO4_Right_Grip_Axis", "PICO 4 (R) Grip Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Right_Trigger, LOCTEXT("PICO4_Right_Trigger_Click", "PICO 4 (R) Trigger"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Right_Trigger_Axis, LOCTEXT("PICO4_Right_Trigger_Axis", "PICO 4 (R) Trigger Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Right_Trigger_Touch, LOCTEXT("PICO4_Right_Trigger_Touch", "PICO 4 (R) Trigger Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Right_Thumbstick_X, LOCTEXT("PICO4_Right_Thumbstick_X", "PICO 4 (R) Thumbstick X"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Right_Thumbstick_Y, LOCTEXT("PICO4_Right_Thumbstick_Y", "PICO 4 (R) Thumbstick Y"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddPairedKey(FKeyDetails(PICO4_Right_Thumbstick_2D, LOCTEXT("PICO4_Right_Thumbstick_2D", "PICO 4 (R) Thumbstick 2D-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis2D | FKeyDetails::NotBlueprintBindableKey, "PICO4"), PICO4_Right_Thumbstick_X, PICO4_Right_Thumbstick_Y);
	EKeys::AddKey(FKeyDetails(PICO4_Right_Thumbstick, LOCTEXT("PICO4_Right_Thumbstick_Click", "PICO 4 (R) Thumbstick"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
	EKeys::AddKey(FKeyDetails(PICO4_Right_Thumbstick_Touch, LOCTEXT("PICO4_Right_Thumbstick_Touch", "PICO 4 (R) Thumbstick Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4"));
}

void FPICO4ControllerPICO::Unregister()
{
	UnregisterOpenXRExtensionModularFeature();
}

bool FPICO4ControllerPICO::GetRequiredExtensions(TArray<const ANSICHAR*>& OutExtensions)
{
	OutExtensions.Add("XR_BD_controller_interaction");
	return true;
}

bool FPICO4ControllerPICO::GetInteractionProfile(XrInstance InInstance, FString& OutKeyPrefix, XrPath& OutPath, bool& OutHasHaptics)
{
	UE_LOG(LogPICOOpenXRInput, Log, TEXT("PICO OpenXR GetInteractionProfile /interaction_profiles/bytedance/pico4_controller."));

	XrResult Result = xrStringToPath(InInstance, "/interaction_profiles/bytedance/pico4_controller", &InteractionProfile);
	if (XR_SUCCEEDED(Result))
	{
		OutKeyPrefix = "PICO4";
		OutPath = InteractionProfile;
		OutHasHaptics = true;
		FPICOOpenXRInputModule::Get().RegisterProfile(InteractionProfile);
		return true;
	}
	return false;
}

bool FPICO4ControllerPICO::GetControllerModel(XrInstance InInstance, XrPath InInteractionProfile, XrPath InDevicePath, FSoftObjectPath& OutPath)
{
	UE_LOG(LogPICOOpenXRInput, Verbose, TEXT("PICO OpenXR GetControllerModel PICO 4."));
	if (InInteractionProfile == InteractionProfile)
	{
		XrPath Path;
		XrResult Result;
		Result = xrStringToPath(InInstance, "/user/hand/left", &Path);
		if (XR_FAILED(Result))
		{
			return false;
		}
		ControllerModels.Add(Path, PICO4TouchLeft);

		Result = xrStringToPath(InInstance, "/user/hand/right", &Path);
		if (XR_FAILED(Result))
		{
			return false;
		}
		ControllerModels.Add(Path, PICO4TouchRight);

		OutPath = ControllerModels[InDevicePath];
		return true;
	}
	return false;
}

void FPICO4ControllerPICO::GetControllerModelsForCooking(TArray<FSoftObjectPath>& OutPaths)
{
	UE_LOG(LogPICOOpenXRInput, Log, TEXT("PICO OpenXR GetControllerModelsForCooking PICO 4."));
	OutPaths.Add(PICO4TouchLeft);
	OutPaths.Add(PICO4TouchRight);
}

#undef LOCTEXT_NAMESPACE