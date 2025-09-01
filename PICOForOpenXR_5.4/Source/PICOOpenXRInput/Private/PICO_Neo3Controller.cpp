// Copyright 2023 PICO Inc. All Rights Reserved.

#include "PICO_Neo3Controller.h"
#include "OpenXRCore.h"
#include "PICO_InputModule.h"

#define LOCTEXT_NAMESPACE "FNeo3ControllerPICO"

// Left
const FKey PICONeo3_Left_X_Click("PICONeo3_Left_X_Click");
const FKey PICONeo3_Left_Y_Click("PICONeo3_Left_Y_Click");
const FKey PICONeo3_Left_X_Touch("PICONeo3_Left_X_Touch");
const FKey PICONeo3_Left_Y_Touch("PICONeo3_Left_Y_Touch");
const FKey PICONeo3_Left_Menu_Click("PICONeo3_Left_Menu_Click");
const FKey PICONeo3_Left_Grip("PICONeo3_Left_Grip_Click");
const FKey PICONeo3_Left_Grip_Axis("PICONeo3_Left_Grip_Axis");
const FKey PICONeo3_Left_Trigger("PICONeo3_Left_Trigger_Click");
const FKey PICONeo3_Left_Trigger_Axis("PICONeo3_Left_Trigger_Axis");
const FKey PICONeo3_Left_Trigger_Touch("PICONeo3_Left_Trigger_Touch");
const FKey PICONeo3_Left_Thumbstick_2D("PICONeo3_Left_Thumbstick_2D");
const FKey PICONeo3_Left_Thumbstick_X("PICONeo3_Left_Thumbstick_X");
const FKey PICONeo3_Left_Thumbstick_Y("PICONeo3_Left_Thumbstick_Y");
const FKey PICONeo3_Left_Thumbstick("PICONeo3_Left_Thumbstick_Click");
const FKey PICONeo3_Left_Thumbstick_Touch("PICONeo3_Left_Thumbstick_Touch");
//Right
const FKey PICONeo3_Right_A_Click("PICONeo3_Right_A_Click");
const FKey PICONeo3_Right_B_Click("PICONeo3_Right_B_Click");
const FKey PICONeo3_Right_A_Touch("PICONeo3_Right_A_Touch");
const FKey PICONeo3_Right_B_Touch("PICONeo3_Right_B_Touch");
const FKey PICONeo3_Right_Menu_Click("PICONeo3_Right_Menu_Click");
const FKey PICONeo3_Right_Grip("PICONeo3_Right_Grip_Click");
const FKey PICONeo3_Right_Grip_Axis("PICONeo3_Right_Grip_Axis");
const FKey PICONeo3_Right_Trigger("PICONeo3_Right_Trigger_Click");
const FKey PICONeo3_Right_Trigger_Axis("PICONeo3_Right_Trigger_Axis");
const FKey PICONeo3_Right_Trigger_Touch("PICONeo3_Right_Trigger_Touch");
const FKey PICONeo3_Right_Thumbstick_2D("PICONeo3_Right_Thumbstick_2D");
const FKey PICONeo3_Right_Thumbstick_X("PICONeo3_Right_Thumbstick_X");
const FKey PICONeo3_Right_Thumbstick_Y("PICONeo3_Right_Thumbstick_Y");
const FKey PICONeo3_Right_Thumbstick("PICONeo3_Right_Thumbstick_Click");
const FKey PICONeo3_Right_Thumbstick_Touch("PICONeo3_Right_Thumbstick_Touch");

FNeo3ControllerPICO::FNeo3ControllerPICO()
{
}

void FNeo3ControllerPICO::Register()
{
	RegisterOpenXRExtensionModularFeature();

	EKeys::AddMenuCategoryDisplayInfo("PICONeo3", LOCTEXT("PICONeo3SubCategory", "PICO Neo3 Controller"), TEXT("GraphEditor.PadEvent_16x"));

	// Left
	EKeys::AddKey(FKeyDetails(PICONeo3_Left_X_Click, LOCTEXT("PICONeo3_Left_X_Click", "PICO Neo3 (L) X Press"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Left_Y_Click, LOCTEXT("PICONeo3_Left_Y_Click", "PICO Neo3 (L) Y Press"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Left_X_Touch, LOCTEXT("PICONeo3_Left_X_Touch", "PICO Neo3 (L) X Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Left_Y_Touch, LOCTEXT("PICONeo3_Left_Y_Touch", "PICO Neo3 (L) Y Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Left_Menu_Click, LOCTEXT("PICONeo3_Left_Menu_Click", "PICO Neo3 (L) Menu"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Left_Grip, LOCTEXT("PICONeo3_Left_Grip_Click", "PICO Neo3 (L) Grip"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Left_Grip_Axis, LOCTEXT("PICONeo3_Left_Grip_Axis", "PICO Neo3 (L) Grip Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Left_Trigger, LOCTEXT("PICONeo3_Left_Trigger_Click", "PICO Neo3 (L) Trigger"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Left_Trigger_Axis, LOCTEXT("PICONeo3_Left_Trigger_Axis", "PICO Neo3 (L) Trigger Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Left_Trigger_Touch, LOCTEXT("PICONeo3_Left_Trigger_Touch", "PICO Neo3 (L) Trigger Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Left_Thumbstick_X, LOCTEXT("PICONeo3_Left_Thumbstick_X", "PICO Neo3 (L) Thumbstick X"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Left_Thumbstick_Y, LOCTEXT("PICONeo3_Left_Thumbstick_Y", "PICO Neo3 (L) Thumbstick Y"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddPairedKey(FKeyDetails(PICONeo3_Left_Thumbstick_2D, LOCTEXT("PICONeo3_Left_Thumbstick_2D", "PICO Neo3 (L) Thumbstick 2D-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis2D | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"), PICONeo3_Left_Thumbstick_X, PICONeo3_Left_Thumbstick_Y);
	EKeys::AddKey(FKeyDetails(PICONeo3_Left_Thumbstick, LOCTEXT("PICONeo3_Left_Thumbstick_Click", "PICO Neo3 (L) Thumbstick"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Left_Thumbstick_Touch, LOCTEXT("PICONeo3_Left_Thumbstick_Touch", "PICO Neo3 (L) Thumbstick Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));

	// Right
	EKeys::AddKey(FKeyDetails(PICONeo3_Right_A_Click, LOCTEXT("PICONeo3_Right_A_Click", "PICO Neo3 (R) A Press"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Right_B_Click, LOCTEXT("PICONeo3_Right_B_Click", "PICO Neo3 (R) B Press"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Right_A_Touch, LOCTEXT("PICONeo3_Right_A_Touch", "PICO Neo3 (R) A Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Right_B_Touch, LOCTEXT("PICONeo3_Right_B_Touch", "PICO Neo3 (R) B Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Right_Menu_Click, LOCTEXT("PICONeo3_Right_Menu_Click", "PICO Neo3 (R) Menu"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Right_Grip, LOCTEXT("PICONeo3_Right_Grip_Click", "PICO Neo3 (R) Grip"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Right_Grip_Axis, LOCTEXT("PICONeo3_Right_Grip_Axis", "PICO Neo3 (R) Grip Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Right_Trigger, LOCTEXT("PICONeo3_Right_Trigger_Click", "PICO Neo3 (R) Trigger"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Right_Trigger_Axis, LOCTEXT("PICONeo3_Right_Trigger_Axis", "PICO Neo3 (R) Trigger Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Right_Trigger_Touch, LOCTEXT("PICONeo3_Right_Trigger_Touch", "PICO Neo3 (R) Trigger Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Right_Thumbstick_X, LOCTEXT("PICONeo3_Right_Thumbstick_X", "PICO Neo3 (R) Thumbstick X"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Right_Thumbstick_Y, LOCTEXT("PICONeo3_Right_Thumbstick_Y", "PICO Neo3 (R) Thumbstick Y"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddPairedKey(FKeyDetails(PICONeo3_Right_Thumbstick_2D, LOCTEXT("PICONeo3_Right_Thumbstick_2D", "PICO Neo3 (R) Thumbstick 2D-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis2D | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"), PICONeo3_Right_Thumbstick_X, PICONeo3_Right_Thumbstick_Y);
	EKeys::AddKey(FKeyDetails(PICONeo3_Right_Thumbstick, LOCTEXT("PICONeo3_Right_Thumbstick_Click", "PICO Neo3 (R) Thumbstick"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
	EKeys::AddKey(FKeyDetails(PICONeo3_Right_Thumbstick_Touch, LOCTEXT("PICONeo3_Right_Thumbstick_Touch", "PICO Neo3 (R) Thumbstick Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICONeo3"));
}

void FNeo3ControllerPICO::Unregister()
{
	UnregisterOpenXRExtensionModularFeature();
}

bool FNeo3ControllerPICO::GetRequiredExtensions(TArray<const ANSICHAR*>& OutExtensions)
{
	OutExtensions.Add("XR_BD_controller_interaction");
	return true;
}

bool FNeo3ControllerPICO::GetInteractionProfile(XrInstance InInstance, FString& OutKeyPrefix, XrPath& OutPath, bool& OutHasHaptics)
{
	UE_LOG(LogPICOOpenXRInput, Log, TEXT("PICO OpenXR GetInteractionProfile /interaction_profiles/bytedance/pico_neo3_controller."));

	XrResult Result = xrStringToPath(InInstance, "/interaction_profiles/bytedance/pico_neo3_controller", &InteractionProfile);
	if (XR_SUCCEEDED(Result))
	{	
		OutKeyPrefix = "PICONeo3";
		OutPath = InteractionProfile;
		OutHasHaptics = true;
		FPICOOpenXRInputModule::Get().RegisterProfile(InteractionProfile);
		return true;
	}
	return false;
}

bool FNeo3ControllerPICO::GetControllerModel(XrInstance InInstance, XrPath InInteractionProfile, XrPath InDevicePath, FSoftObjectPath& OutPath)
{
	UE_LOG(LogPICOOpenXRInput, Verbose, TEXT("PICO OpenXR GetControllerModel PICO Neo 3."));
	if (InInteractionProfile == InteractionProfile)
	{
		XrPath Path;
		XrResult Result;
		Result = xrStringToPath(InInstance, "/user/hand/left", &Path);
		if (XR_FAILED(Result))
		{
			return false;
		}
		ControllerModels.Add(Path, PicoNeo3TouchLeft);

		Result = xrStringToPath(InInstance, "/user/hand/right", &Path);
		if (XR_FAILED(Result))
		{
			return false;
		}
		ControllerModels.Add(Path, PicoNeo3TouchRight);

		OutPath = ControllerModels[InDevicePath];
		return true;
	}
	return false;
}

void FNeo3ControllerPICO::GetControllerModelsForCooking(TArray<FSoftObjectPath>& OutPaths)
{
	UE_LOG(LogPICOOpenXRInput, Log, TEXT("PICO OpenXR GetControllerModelsForCooking PICO Neo 3."));
	OutPaths.Add(PicoNeo3TouchLeft);
	OutPaths.Add(PicoNeo3TouchRight);
}

#undef LOCTEXT_NAMESPACE