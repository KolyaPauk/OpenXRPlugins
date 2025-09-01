// Copyright 2023 PICO Inc. All Rights Reserved.

#include "PICO_InputModule.h"

DEFINE_LOG_CATEGORY(LogPICOOpenXRInput);

void FPICOOpenXRInputModule::StartupModule()
{
	Neo3ControllerExtension.Register();
	PICO4ControllerExtension.Register();
	G3ControllerExtension.Register();
	ControllerExtension.Register();
	PICO4UControllerExtension.Register();
}

void FPICOOpenXRInputModule::ShutdownModule()
{
	Neo3ControllerExtension.Unregister();
	PICO4ControllerExtension.Unregister();
	G3ControllerExtension.Unregister();
	ControllerExtension.Unregister();
	PICO4UControllerExtension.Unregister();
}

void FPICOOpenXRInputModule::RegisterProfile(XrPath Profile)
{
	ControllerExtension.AddProfile(Profile);
}

IMPLEMENT_MODULE(FPICOOpenXRInputModule, PICOOpenXRInput)
