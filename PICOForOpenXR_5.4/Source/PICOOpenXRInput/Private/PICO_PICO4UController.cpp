// Copyright 2023 PICO Inc. All Rights Reserved.

#include "PICO_PICO4UController.h"
#include "OpenXRCore.h"
#include "PICO_InputModule.h"

#define LOCTEXT_NAMESPACE "F4UControllerPICO"

// Left
const FKey PICO4U_Left_X_Click("PICO4U_Left_X_Click");
const FKey PICO4U_Left_Y_Click("PICO4U_Left_Y_Click");
const FKey PICO4U_Left_X_Touch("PICO4U_Left_X_Touch");
const FKey PICO4U_Left_Y_Touch("PICO4U_Left_Y_Touch");
const FKey PICO4U_Left_Menu_Click("PICO4U_Left_Menu_Click");
const FKey PICO4U_Left_Grip("PICO4U_Left_Grip_Click");
const FKey PICO4U_Left_Grip_Axis("PICO4U_Left_Grip_Axis");
const FKey PICO4U_Left_Trigger("PICO4U_Left_Trigger_Click");
const FKey PICO4U_Left_Trigger_Axis("PICO4U_Left_Trigger_Axis");
const FKey PICO4U_Left_Trigger_Touch("PICO4U_Left_Trigger_Touch");
const FKey PICO4U_Left_Thumbstick_2D("PICO4U_Left_Thumbstick_2D");
const FKey PICO4U_Left_Thumbstick_X("PICO4U_Left_Thumbstick_X");
const FKey PICO4U_Left_Thumbstick_Y("PICO4U_Left_Thumbstick_Y");
const FKey PICO4U_Left_Thumbstick("PICO4U_Left_Thumbstick_Click");
const FKey PICO4U_Left_Thumbstick_Touch("PICO4U_Left_Thumbstick_Touch");
const FKey PICO4U_Left_ThumbRest_Touch("PICO4U_Left_ThumbRest_Touch");
//Right
const FKey PICO4U_Right_A_Click("PICO4U_Right_A_Click");
const FKey PICO4U_Right_B_Click("PICO4U_Right_B_Click");
const FKey PICO4U_Right_A_Touch("PICO4U_Right_A_Touch");
const FKey PICO4U_Right_B_Touch("PICO4U_Right_B_Touch");
const FKey PICO4U_Right_Grip("PICO4U_Right_Grip_Click");
const FKey PICO4U_Right_Grip_Axis("PICO4U_Right_Grip_Axis");
const FKey PICO4U_Right_Trigger("PICO4U_Right_Trigger_Click");
const FKey PICO4U_Right_Trigger_Axis("PICO4U_Right_Trigger_Axis");
const FKey PICO4U_Right_Trigger_Touch("PICO4U_Right_Trigger_Touch");
const FKey PICO4U_Right_Thumbstick_2D("PICO4U_Right_Thumbstick_2D");
const FKey PICO4U_Right_Thumbstick_X("PICO4U_Right_Thumbstick_X");
const FKey PICO4U_Right_Thumbstick_Y("PICO4U_Right_Thumbstick_Y");
const FKey PICO4U_Right_Thumbstick("PICO4U_Right_Thumbstick_Click");
const FKey PICO4U_Right_Thumbstick_Touch("PICO4U_Right_Thumbstick_Touch");
const FKey PICO4U_Right_ThumbRest_Touch("PICO4U_Right_ThumbRest_Touch");

F4UControllerPICO::F4UControllerPICO()
{
}

void F4UControllerPICO::Register()
{
	RegisterOpenXRExtensionModularFeature();

	EKeys::AddMenuCategoryDisplayInfo("PICO4U", LOCTEXT("PICO4USubCategory", "PICO 4U Controller"), TEXT("GraphEditor.PadEvent_16x"));

	// Left
	EKeys::AddKey(FKeyDetails(PICO4U_Left_X_Click, LOCTEXT("PICO4U_Left_X_Click", "PICO 4U (L) X Press"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Left_Y_Click, LOCTEXT("PICO4U_Left_Y_Click", "PICO 4U (L) Y Press"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Left_X_Touch, LOCTEXT("PICO4U_Left_X_Touch", "PICO 4U (L) X Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Left_Y_Touch, LOCTEXT("PICO4U_Left_Y_Touch", "PICO 4U (L) Y Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Left_Menu_Click, LOCTEXT("PICO4U_Left_Menu_Click", "PICO 4U (L) Menu"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Left_Grip, LOCTEXT("PICO4U_Left_Grip_Click", "PICO 4U (L) Grip"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Left_Grip_Axis, LOCTEXT("PICO4U_Left_Grip_Axis", "PICO 4U (L) Grip Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Left_Trigger, LOCTEXT("PICO4U_Left_Trigger_Click", "PICO 4U (L) Trigger"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Left_Trigger_Axis, LOCTEXT("PICO4U_Left_Trigger_Axis", "PICO 4U (L) Trigger Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Left_Trigger_Touch, LOCTEXT("PICO4U_Left_Trigger_Touch", "PICO 4U (L) Trigger Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Left_Thumbstick_X, LOCTEXT("PICO4U_Left_Thumbstick_X", "PICO 4U (L) Thumbstick X"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Left_Thumbstick_Y, LOCTEXT("PICO4U_Left_Thumbstick_Y", "PICO 4U (L) Thumbstick Y"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddPairedKey(FKeyDetails(PICO4U_Left_Thumbstick_2D, LOCTEXT("PICO4U_Left_Thumbstick_2D", "PICO 4U (L) Thumbstick 2D-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis2D | FKeyDetails::NotBlueprintBindableKey, "PICO4U"), PICO4U_Left_Thumbstick_X, PICO4U_Left_Thumbstick_Y);
	EKeys::AddKey(FKeyDetails(PICO4U_Left_Thumbstick, LOCTEXT("PICO4U_Left_Thumbstick_Click", "PICO 4U (L) Thumbstick"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Left_Thumbstick_Touch, LOCTEXT("PICO4U_Left_Thumbstick_Touch", "PICO 4U (L) Thumbstick Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Left_ThumbRest_Touch, LOCTEXT("PICO4U_Left_ThumbRest_Touch", "PICO 4U (L) ThumbRest Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));

	// Right
	EKeys::AddKey(FKeyDetails(PICO4U_Right_A_Click, LOCTEXT("PICO4U_Right_A_Click", "PICO 4U (R) A Press"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Right_B_Click, LOCTEXT("PICO4U_Right_B_Click", "PICO 4U (R) B Press"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Right_A_Touch, LOCTEXT("PICO4U_Right_A_Touch", "PICO 4U (R) A Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Right_B_Touch, LOCTEXT("PICO4U_Right_B_Touch", "PICO 4U (R) B Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Right_Grip, LOCTEXT("PICO4U_Right_Grip_Click", "PICO 4U (R) Grip"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Right_Grip_Axis, LOCTEXT("PICO4U_Right_Grip_Axis", "PICO 4U (R) Grip Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Right_Trigger, LOCTEXT("PICO4U_Right_Trigger_Click", "PICO 4U (R) Trigger"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Right_Trigger_Axis, LOCTEXT("PICO4U_Right_Trigger_Axis", "PICO 4U (R) Trigger Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Right_Trigger_Touch, LOCTEXT("PICO4U_Right_Trigger_Touch", "PICO 4U (R) Trigger Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Right_Thumbstick_X, LOCTEXT("PICO4U_Right_Thumbstick_X", "PICO 4U (R) Thumbstick X"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Right_Thumbstick_Y, LOCTEXT("PICO4U_Right_Thumbstick_Y", "PICO 4U (R) Thumbstick Y"), FKeyDetails::GamepadKey | FKeyDetails::Axis1D | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddPairedKey(FKeyDetails(PICO4U_Right_Thumbstick_2D, LOCTEXT("PICO4U_Right_Thumbstick_2D", "PICO 4U (R) Thumbstick 2D-Axis"), FKeyDetails::GamepadKey | FKeyDetails::Axis2D | FKeyDetails::NotBlueprintBindableKey, "PICO4U"), PICO4U_Right_Thumbstick_X, PICO4U_Right_Thumbstick_Y);
	EKeys::AddKey(FKeyDetails(PICO4U_Right_Thumbstick, LOCTEXT("PICO4U_Right_Thumbstick_Click", "PICO 4U (R) Thumbstick"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Right_Thumbstick_Touch, LOCTEXT("PICO4U_Right_Thumbstick_Touch", "PICO 4U (R) Thumbstick Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
	EKeys::AddKey(FKeyDetails(PICO4U_Right_ThumbRest_Touch, LOCTEXT("PICO4U_Right_ThumbRest_Touch", "PICO 4U (R) ThumbRest Touch"), FKeyDetails::GamepadKey | FKeyDetails::NotBlueprintBindableKey, "PICO4U"));
}

void F4UControllerPICO::Unregister()
{
	UnregisterOpenXRExtensionModularFeature();
}

bool F4UControllerPICO::GetRequiredExtensions(TArray<const ANSICHAR*>& OutExtensions)
{
	OutExtensions.Add("XR_BD_controller_interaction");
	return true;
}

bool F4UControllerPICO::GetInteractionProfile(XrInstance InInstance, FString& OutKeyPrefix, XrPath& OutPath, bool& OutHasHaptics)
{
	UE_LOG(LogPICOOpenXRInput, Log, TEXT("PICO OpenXR GetInteractionProfile /interaction_profiles/bytedance/pico4s_controller."));

	XrResult Result = xrStringToPath(InInstance, "/interaction_profiles/bytedance/pico4s_controller", &InteractionProfile);
	if (XR_SUCCEEDED(Result))
	{
		OutKeyPrefix = "PICO4U";
		OutPath = InteractionProfile;
		OutHasHaptics = true;
		FPICOOpenXRInputModule::Get().RegisterProfile(InteractionProfile);
		return true;
	}
	return false;
}

#undef LOCTEXT_NAMESPACE