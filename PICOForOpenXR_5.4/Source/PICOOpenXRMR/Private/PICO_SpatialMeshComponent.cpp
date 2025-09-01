// Copyright® 2015-2023 PICO Technology Co., Ltd. All rights reserved.
// This plugin incorporates portions of the Unreal® Engine. Unreal® is a trademark or registered trademark of Epic Games, Inc. in the United States of America and elsewhere.
// Unreal® Engine, Copyright 1998 – 2023, Epic Games, Inc. All rights reserved. 

#include "PICO_SpatialMeshComponent.h"
#include "PICO_MRTypes.h"

USpatialMeshComponentPICO::USpatialMeshComponentPICO(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
}

ESemanticLabelPICO USpatialMeshComponentPICO::GetSemanticByIndex(int32 Index)
{
	return IndexToAnchorSceneLabelMap.Find(Index)?IndexToAnchorSceneLabelMap[Index]:ESemanticLabelPICO::Unknown;
}

void USpatialMeshComponentPICO::AddAnchorToSceneLabel(int32 Index, ESemanticLabelPICO SceneLabel)
{
	IndexToAnchorSceneLabelMap.Emplace(Index,SceneLabel);
}

void USpatialMeshComponentPICO::SetUpdateTime(uint64 Time)
{
	LastUpdateTime=Time;
}

int64 USpatialMeshComponentPICO::GetUpdateTime() const
{
	return static_cast<int64>(LastUpdateTime);
}
