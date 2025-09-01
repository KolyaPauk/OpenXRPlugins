// Copyright 2023 PICO Inc. All Rights Reserved.

#include "PICO_G3Controller.h"
#include "OpenXRCore.h"
#include "PICO_InputModule.h"

#define LOCTEXT_NAMESPACE "FG3ControllerPICO"

// Left
const FKey PICOG3_Left_Menu_Click("PICOG3_Left_Menu_Click");
const FKey PICOG3_Left_Trigger("PICOG3_Left_Trigger_Click");
const FKey PICOG3_Left_Trigger_Axis("PICOG3_Left_Trigger_Axis");
const FKey PICOG3_Left_Thumbstick_2D("PICOG3_Left_Thumbstick_2D");
const FKey PICOG3_Left_Thumbstick_X("PICOG3_Left_Thumbstick_X");
const FKey PICOG3_Left_Thumbstick_Y("PICOG3_Left_Thumbstick_Y");
const FKey PICOG3_Left_Thumbstick("PICOG3_Left_Thumbstick_Click");
//Right
const FKey PICOG3_Right_Menu_Click("PICOG3_Right_Menu_Click");
const FKey PICOG3_Right_Trigger("PICOG3_Right_Trigger_Click");
const FKey PICOG3_Right_Trigger_Axis("PICOG3_Right_Trigger_Axis");
const FKey PICOG3_Right_Thumbstick_2D("PICOG3_Right_Thumbstick_2D");
const FKey PICOG3_Right_Thumbstick_X("PICOG3_Right_Thumbstick_X");
const FKey PICOG3_Right_Thumbstick_Y("PICOG3_Right_Thumbstick_Y");
const FKey PICOG3_Right_Thumbstick("PICOG3_Right_Thumbstick_Click");

FG3ControllerPICO::FG3ControllerPICO()
{
}

void FG3ControllerPICO::Register()
{
	RegisterOpenXRExtensionModularFeature();

	EKeys::AddMenuCategoryDisplayInfo("PICOG3", LOCTEXT("PICOG3SubCategory", "PICO G3 Controller"), TEXT("GraphEditor.PadEvent_16x"));

	// Left
	EKeys::AddKey(FKeyDetails(PICOG3_Left_Menu_Click, LOCTEXT("PICOG3_Left_Menu_Click", "PICO G3 (L) Menu"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICOG3"));
	EKeys::AddKey(FKeyDetails(PICOG3_Left_Trigger, LOCTEXT("PICOG3_Left_Trigger_Click", "PICO G3 (L) Trigger"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICOG3"));
	EKeys::AddKey(FKeyDetails(PICOG3_Left_Trigger_Axis, LOCTEXT("PICOG3_Left_Trigger_Axis", "PICO G3 (L) Trigger Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICOG3"));
	EKeys::AddKey(FKeyDetails(PICOG3_Left_Thumbstick_X, LOCTEXT("PICOG3_Left_Thumbstick_X", "PICO G3 (L) Thumbstick X"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICOG3"));
	EKeys::AddKey(FKeyDetails(PICOG3_Left_Thumbstick_Y, LOCTEXT("PICOG3_Left_Thumbstick_Y", "PICO G3 (L) Thumbstick Y"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICOG3"));
	EKeys::AddPairedKey(FKeyDetails(PICOG3_Left_Thumbstick_2D, LOCTEXT("PICOG3_Left_Thumbstick_2D", "PICO G3 (L) Thumbstick 2D-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis2D | FKeyDetails::NotBlueprintBindableKey, "PICOG3"), PICOG3_Left_Thumbstick_X, PICOG3_Left_Thumbstick_Y);
	EKeys::AddKey(FKeyDetails(PICOG3_Left_Thumbstick, LOCTEXT("PICOG3_Left_Thumbstick_Click", "PICO G3 (L) Thumbstick"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICOG3"));

	// Right
	EKeys::AddKey(FKeyDetails(PICOG3_Right_Menu_Click, LOCTEXT("PICOG3_Right_Menu_Click", "PICO G3 (R) Menu"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICOG3"));
	EKeys::AddKey(FKeyDetails(PICOG3_Right_Trigger, LOCTEXT("PICOG3_Right_Trigger_Click", "PICO G3 (R) Trigger"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICOG3"));
	EKeys::AddKey(FKeyDetails(PICOG3_Right_Trigger_Axis, LOCTEXT("PICOG3_Right_Trigger_Axis", "PICO G3 (R) Trigger Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICOG3"));
	EKeys::AddKey(FKeyDetails(PICOG3_Right_Thumbstick_X, LOCTEXT("PICOG3_Right_Thumbstick_X", "PICO G3 (R) Thumbstick X"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICOG3"));
	EKeys::AddKey(FKeyDetails(PICOG3_Right_Thumbstick_Y, LOCTEXT("PICOG3_Right_Thumbstick_Y", "PICO G3 (R) Thumbstick Y"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICOG3"));
	EKeys::AddPairedKey(FKeyDetails(PICOG3_Right_Thumbstick_2D, LOCTEXT("PICOG3_Right_Thumbstick_2D", "PICO G3 (R) Thumbstick 2D-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis2D | FKeyDetails::NotBlueprintBindableKey, "PICOG3"), PICOG3_Right_Thumbstick_X, PICOG3_Right_Thumbstick_Y);
	EKeys::AddKey(FKeyDetails(PICOG3_Right_Thumbstick, LOCTEXT("PICOG3_Right_Thumbstick_Click", "PICO G3 (R) Thumbstick"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICOG3"));
}

void FG3ControllerPICO::Unregister()
{
	UnregisterOpenXRExtensionModularFeature();
}

bool FG3ControllerPICO::GetRequiredExtensions(TArray<const ANSICHAR*>& OutExtensions)
{
	OutExtensions.Add("XR_BD_controller_interaction");
	return true;
}

bool FG3ControllerPICO::GetInteractionProfile(XrInstance InInstance, FString& OutKeyPrefix, XrPath& OutPath, bool& OutHasHaptics)
{
	UE_LOG(LogPICOOpenXRInput, Log, TEXT("PICO OpenXR GetInteractionProfile /interaction_profiles/bytedance/pico_g3_controller."));
	
	XrPath InteractionProfile;
	XrResult Result = xrStringToPath(InInstance, "/interaction_profiles/bytedance/pico_g3_controller", &InteractionProfile);
	if (XR_SUCCEEDED(Result))
	{
		OutKeyPrefix = "PICOG3";
		OutPath = InteractionProfile;
		OutHasHaptics = false;
		FPICOOpenXRInputModule::Get().RegisterProfile(InteractionProfile);
		return true;
	}
	return false;
}

#undef LOCTEXT_NAMESPACE