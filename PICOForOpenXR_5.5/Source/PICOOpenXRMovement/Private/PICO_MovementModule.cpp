// Copyright 2023 PICO Inc. All Rights Reserved.

#include "PICO_MovementModule.h"

DEFINE_LOG_CATEGORY(PICOOpenXRMovement);

void FPICOOpenXRMovementModule::StartupModule()
{
    FaceTrackingPICOExtension.Register();
    BodyTrackingPICOExtension.Register();
    MotionTrackingPICOExtension.Register();
    EyeTrackingPICOExtension.Register();
    ExpandDeviceExtension.Register();
}

void FPICOOpenXRMovementModule::ShutdownModule()
{
    FaceTrackingPICOExtension.Unregister();
    BodyTrackingPICOExtension.Unregister();
    MotionTrackingPICOExtension.Unregister();
    EyeTrackingPICOExtension.Unregister();
    ExpandDeviceExtension.Unregister();
}

TSharedPtr<ILiveLinkSource> FPICOOpenXRMovementModule::GetLiveLinkSource()
{
    if (!MovementSource.IsValid())
    {
        AddLiveLinkSource();
    }
    return MovementSource;
}

bool FPICOOpenXRMovementModule::IsLiveLinkSourceValid() const
{
    return MovementSource.IsValid();
}

void FPICOOpenXRMovementModule::AddLiveLinkSource()
{
    if (!MovementSource.IsValid())
    {
        MovementSource = MakeShared<PICOLiveLink::LiveLinkSource>();
    }
}

void FPICOOpenXRMovementModule::RemoveLiveLinkSource()
{
    MovementSource.Reset();
}

IMPLEMENT_MODULE(FPICOOpenXRMovementModule, PICOOpenXRMovement)
