// Copyright 2023 PICO Inc. All Rights Reserved.

#include "PICO_Controller.h"
#include "OpenXRCore.h"
#include "PICO_InputModule.h"
#include "IOpenXRHMDModule.h"
#include "Haptics/HapticFeedbackEffect_Base.h"
#include "Framework/Application/SlateApplication.h"
#include "Haptics/HapticFeedbackEffect_SoundWave.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"

#if PLATFORM_ANDROID
#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#endif

#define LOCTEXT_NAMESPACE "FControllerPICO"

FControllerPICO::FControllerPICO()
	:SuggestedBindings(false)
{
}

void FControllerPICO::Register()
{
	RegisterOpenXRExtensionModularFeature();
}

void FControllerPICO::Unregister()
{
	UnregisterOpenXRExtensionModularFeature();
}

bool FControllerPICO::GetOptionalExtensions(TArray<const ANSICHAR*>& OutExtensions)
{
	return true;
}

void FControllerPICO::PostCreateInstance(XrInstance InInstance)
{
	Instance = InInstance;
    SubactionPaths.Reset();
	XrPath PathLeft;
	XrResult Result;
	Result = xrStringToPath(Instance, "/user/hand/left", &PathLeft);
	if (XR_SUCCEEDED(Result))
	{
		SubactionPaths.Add(PathLeft);
	}

	XrPath PathRight;
	Result = xrStringToPath(Instance, "/user/hand/right", &PathRight);
	if (XR_SUCCEEDED(Result))
	{
		SubactionPaths.Add(PathRight);
	}

	ActionStateFloats.SetNum(SubactionPaths.Num());
}

void FControllerPICO::PostGetSystem(XrInstance InInstance, XrSystemId InSystem)
{
}

const void* FControllerPICO::OnCreateSession(XrInstance InInstance, XrSystemId InSystem, const void* InNext)
{
	if (ControllerActionSet)
	{
		XR_ENSURE(xrDestroyActionSet(ControllerActionSet));
	}

	if (ControllerBatteryAction)
	{
		XR_ENSURE(xrDestroyAction(ControllerBatteryAction));
	}

	XrActionSetCreateInfo ActionSetInfo = { XR_TYPE_ACTION_SET_CREATE_INFO };
	FCStringAnsi::Strcpy(ActionSetInfo.actionSetName, XR_MAX_ACTION_SET_NAME_SIZE, "openxrbatteryactionset");
	FCStringAnsi::Strcpy(ActionSetInfo.localizedActionSetName, XR_MAX_LOCALIZED_ACTION_SET_NAME_SIZE, "OpenXR Battery Action Set");
	XR_ENSURE(xrCreateActionSet(Instance, &ActionSetInfo, &ControllerActionSet));

	XrActionCreateInfo ActionInfo = { XR_TYPE_ACTION_CREATE_INFO };
	ActionInfo.countSubactionPaths = SubactionPaths.Num();
	ActionInfo.subactionPaths = SubactionPaths.GetData();
	FCStringAnsi::Strcpy(ActionInfo.actionName, XR_MAX_ACTION_NAME_SIZE, "openxrbatteryaction");
	FCStringAnsi::Strcpy(ActionInfo.localizedActionName, XR_MAX_LOCALIZED_ACTION_NAME_SIZE, "OpenXR Battery Action");
	ActionInfo.actionType = XR_ACTION_TYPE_FLOAT_INPUT;
	XrResult Result = xrCreateAction(ControllerActionSet, &ActionInfo, &ControllerBatteryAction);
	if (XR_FAILED(Result))
	{
		UE_LOG(LogHMD, Warning, TEXT("Failed to create OpenXR Battery Action: %s"), OpenXRResultToString(Result));
		if (ControllerActionSet)
		{
			XR_ENSURE(xrDestroyActionSet(ControllerActionSet));
		}
	}

	return InNext;
}

void FControllerPICO::PostCreateSession(XrSession InSession)
{
	Session = InSession;
}

bool FControllerPICO::GetSuggestedBindings(XrPath InInteractionProfile, TArray<XrActionSuggestedBinding>& OutBindings)
{
	if (Instance != XR_NULL_HANDLE && ControllerBatteryAction != XR_NULL_HANDLE && Profiles.Find(InInteractionProfile) != INDEX_NONE)
	{
		XrPath BatteryLeft;
		XrResult Result;
		Result = xrStringToPath(Instance, "/user/hand/left/input/battery/value", &BatteryLeft);
		if (XR_SUCCEEDED(Result))
		{
			OutBindings.Add(XrActionSuggestedBinding{ ControllerBatteryAction ,BatteryLeft });
		}

		XrPath BatteryRight;
		Result = xrStringToPath(Instance, "/user/hand/right/input/battery/value", &BatteryRight);
		if (XR_SUCCEEDED(Result))
		{
			OutBindings.Add(XrActionSuggestedBinding{ ControllerBatteryAction ,BatteryRight });
		}

		SuggestedBindings = true;
		return true;
	}

	return false;
}

void FControllerPICO::AttachActionSets(TSet<XrActionSet>& OutActionSets)
{
	if (SuggestedBindings)
	{
		check(ControllerActionSet != XR_NULL_HANDLE);
		OutActionSets.Add(ControllerActionSet);
	}
}

void FControllerPICO::GetActiveActionSetsForSync(TArray<XrActiveActionSet>& OutActiveSets)
{
	if (SuggestedBindings)
	{
		check(ControllerActionSet != XR_NULL_HANDLE);
		OutActiveSets.Add(XrActiveActionSet{ ControllerActionSet, SubactionPaths[0] });
		OutActiveSets.Add(XrActiveActionSet{ ControllerActionSet, SubactionPaths[1] });
	}
}

void FControllerPICO::PostSyncActions(XrSession InSession)
{
	IInputInterface* InputInterface = nullptr;

	if (FSlateApplication::IsInitialized())
	{
		InputInterface = FSlateApplication::Get().GetInputInterface();
	}

	int32 ControllerID = 0;

	if (SuggestedBindings)
	{
		check(ControllerBatteryAction != XR_NULL_HANDLE);
		for (int i = 0; i < SubactionPaths.Num(); i++)
		{
			XrActionStateGetInfo GetActionStateInfo{ XR_TYPE_ACTION_STATE_GET_INFO };
			GetActionStateInfo.action = ControllerBatteryAction;
			GetActionStateInfo.subactionPath = SubactionPaths[i];
			ActionStateFloats[i] = { XR_TYPE_ACTION_STATE_FLOAT };
			XR_ENSURE(xrGetActionStateFloat(InSession, &GetActionStateInfo, &ActionStateFloats[i]));
		}
	}
}

bool FControllerPICO::GetControllerBatteryLevel(const EControllerHand Hand, float& Level)
{
	if (Hand == EControllerHand::Left)
	{
		Level = ActionStateFloats[0].currentState;
		return ActionStateFloats[0].isActive == XR_TRUE;
	}
	else if (Hand == EControllerHand::Right)
	{
		Level = ActionStateFloats[1].currentState;
		return ActionStateFloats[1].isActive == XR_TRUE;
	}
	return false;
}

void FControllerPICO::AddProfile(XrPath Profile)
{
	Profiles.Add(Profile);
}

#undef LOCTEXT_NAMESPACE