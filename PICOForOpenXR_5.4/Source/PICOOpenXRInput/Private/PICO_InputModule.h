// Copyright 2023 PICO Inc. All Rights Reserved.

#pragma once

#include "PICO_IInputModule.h"
#include "PICO_Neo3Controller.h"
#include "PICO_PICO4Controller.h"
#include "PICO_G3Controller.h"
#include "PICO_Controller.h"
#include "PICO_PICO4UController.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPICOOpenXRInput, Log, All);

class FPICOOpenXRInputModule : public IPICOOpenXRInputModule
{
public:
	static inline FPICOOpenXRInputModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FPICOOpenXRInputModule>("PICOOpenXRInput");
	}

	FControllerPICO& GetController() { return ControllerExtension; }

	virtual void StartupModule() override;

	virtual void ShutdownModule() override;

	void RegisterProfile(XrPath Profile);

private:
	FNeo3ControllerPICO Neo3ControllerExtension;
	FPICO4ControllerPICO PICO4ControllerExtension;
	FG3ControllerPICO G3ControllerExtension;
	FControllerPICO ControllerExtension;
	F4UControllerPICO PICO4UControllerExtension;
};