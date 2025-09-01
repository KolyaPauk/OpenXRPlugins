// Copyright® 2015-2023 PICO Technology Co., Ltd. All rights reserved.
// This plugin incorporates portions of the Unreal® Engine. Unreal® is a trademark or registered trademark of Epic Games, Inc. in the United States of America and elsewhere.
// Unreal® Engine, Copyright 1998 – 2023, Epic Games, Inc. All rights reserved. 

#include "PICO_SpatialMeshActor.h"

#include "MRMeshComponent.h"
#include "PICOOpenXRRuntimeSettings.h"
#include "PICO_MRAsyncActions.h"
#include "PICO_MRFunctionLibrary.h"
#include "PICO_SpatialMesh.h"
#include "ProceduralMeshComponent.h"
#include "Algo/Transform.h"
#include "UObject/ConstructorHelpers.h"

#define UPDATE_FRAME_NUM_MAX 10


ASpatialMeshActorPICO::ASpatialMeshActorPICO(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SpatialMeshMaterial=nullptr;

	for (ESemanticLabelPICO Val : TEnumRange<ESemanticLabelPICO>())
	{
		SemanticToColors.Emplace(Val, FColor::MakeRandomSeededColor(static_cast<int32>(Val)));
	}
}

void ASpatialMeshActorPICO::BeginPlay()
{
	Super::BeginPlay();

	USceneComponent* RootSceneComponent = NewObject<USceneComponent>(this, USceneComponent::StaticClass());
	RootSceneComponent->SetMobility(EComponentMobility::Static);
	RootSceneComponent->RegisterComponent();
	SetRootComponent(RootSceneComponent);

	if (bDrawOnBeginPlay)
	{
		StartDraw();
	}
}

void ASpatialMeshActorPICO::HandleMeshDataUpdatedEvent()
{
	URequestSpatialMeshPICO_AsyncAction* RequestSpatialMeshAction = URequestSpatialMeshPICO_AsyncAction::RequestSpatialMeshInfosPICO_Async();
	RequestSpatialMeshAction->OnSuccess.AddDynamic(this, &ASpatialMeshActorPICO::HandleRequestSpatialMeshContentsEvent);
	RequestSpatialMeshAction->Activate();
}

void ASpatialMeshActorPICO::Tick(float DeltaTime)
{
	if (bEnableDebugFunction)
	{
		NumDrawCalls = GNumDrawCallsRHI[0];
		DrawnPrimitives = GNumPrimitivesDrawnRHI[0];
	}

	TArray<FSpatialMeshInfoPICO> MRMeshInfos;
	MeshInfoQueue.Dequeue(MRMeshInfos);

	for (auto MeshInfo : MRMeshInfos)
	{

		switch (MeshInfo.State)
		{
		case ESpatialMeshStatePICO::Added:
			{
				USpatialMeshComponentPICO* SpatialMesh = NewObject<USpatialMeshComponentPICO>(this);
				SpatialMesh->RegisterComponent();
				SpatialMesh->SetMaterial(0,SpatialMeshMaterial);
				SpatialMesh->SetUseWireframe(false);
				SpatialMesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
				SpatialMesh->SetVisibility(bSpatialMeshVisible);
				SpatialMesh->SetCollisionEnabled(CollisionType);
				SpatialMesh->SetEnableMeshOcclusion(true);
				AddOwnedComponent(SpatialMesh);

				if (EntityToMeshMap.Contains(MeshInfo.UUID))
				{
					if (EntityToMeshMap[MeshInfo.UUID]!=nullptr)
					{
						EntityToMeshMap[MeshInfo.UUID]->SetCollisionEnabled(ECollisionEnabled::NoCollision);
						EntityToMeshMap[MeshInfo.UUID]->DestroyComponent();
					}
					EntityToMeshMap.Remove(MeshInfo.UUID);
				}

				EntityToMeshMap.Emplace(MeshInfo.UUID, SpatialMesh);

				UpdateMeshByMeshInfo(SpatialMesh, MeshInfo);
			}
			break;
		case ESpatialMeshStatePICO::Stable:
			break;
		case ESpatialMeshStatePICO::Updated:
			{
				if (EntityToMeshMap.Contains(MeshInfo.UUID))
				{
					if (EntityToMeshMap[MeshInfo.UUID] == nullptr)
					{
						continue;
					}
					UpdateMeshByMeshInfo(EntityToMeshMap[MeshInfo.UUID], MeshInfo);
				}
			}
			break;
		case ESpatialMeshStatePICO::Removed:
			{
				if (EntityToMeshMap.Contains(MeshInfo.UUID)
					&&EntityToMeshMap[MeshInfo.UUID]!=nullptr)
				{

					EntityToMeshMap[MeshInfo.UUID]->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					EntityToMeshMap[MeshInfo.UUID]->DestroyComponent();
					EntityToMeshMap.Remove(MeshInfo.UUID);
				}
				else
				{
				}
			}
			break;
		default: ;
		}
	}
}

void ASpatialMeshActorPICO::HandleRequestSpatialMeshContentsEvent(EResultPICO Result, const TArray<FSpatialMeshInfoPICO>& MeshInfos)
{
	TArray<FSpatialMeshInfoPICO> MRMeshInfos = {};
	int32 Counter = 0;
	bool bIsDone = false;
	const int32 MeshCountPerFrame= FMath::CeilToInt((static_cast<float>(MeshInfos.Num())) / UPDATE_FRAME_NUM_MAX);

	for (auto MeshInfo : MeshInfos)
	{
		Counter++;
		if (Counter < MeshCountPerFrame)
		{
			bIsDone = false;
			MRMeshInfos.Add(MeshInfo);
		}
		else
		{
			bIsDone = true;
			MRMeshInfos.Add(MeshInfo);
			MeshInfoQueue.Enqueue(MRMeshInfos);
			Counter = 0;
			MRMeshInfos.Empty();
		}
	}

	if (!bIsDone)
	{
		MeshInfoQueue.Enqueue(MRMeshInfos);
		MRMeshInfos.Empty();
	}
}

void ASpatialMeshActorPICO::EndPlay(EEndPlayReason::Type Reason)
{
	ClearMesh();
}

bool ASpatialMeshActorPICO::StartDraw()
{
	SetActorTickEnabled(true);
	if (!UMRFunctionLibraryPICO::GetMRDelegateManagerPICO()->MeshDataUpdatedDelegate.Contains(this, GET_FUNCTION_NAME_CHECKED(ASpatialMeshActorPICO, HandleMeshDataUpdatedEvent)))
	{
		UMRFunctionLibraryPICO::GetMRDelegateManagerPICO()->MeshDataUpdatedDelegate.AddDynamic(this, &ASpatialMeshActorPICO::HandleMeshDataUpdatedEvent);
		return true;
	}
	
	return false;
}

bool ASpatialMeshActorPICO::PauseDraw()
{
	SetActorTickEnabled(false);
	if (UMRFunctionLibraryPICO::GetMRDelegateManagerPICO()->MeshDataUpdatedDelegate.Contains(this, GET_FUNCTION_NAME_CHECKED(ASpatialMeshActorPICO, HandleMeshDataUpdatedEvent)))
	{
		UMRFunctionLibraryPICO::GetMRDelegateManagerPICO()->MeshDataUpdatedDelegate.RemoveDynamic(this, &ASpatialMeshActorPICO::HandleMeshDataUpdatedEvent);
		return true;
	}

	return false;
}

void ASpatialMeshActorPICO::SetMeshVisibility(bool visibility)
{
	bSpatialMeshVisible = visibility;
	for (const auto Pair : EntityToMeshMap)
	{
		if (Pair.Value)
		{
			Pair.Value->SetVisibility(visibility);
		}
	}
}

void ASpatialMeshActorPICO::EnableDebugFunction(bool bEnable)
{
	bEnableDebugFunction = bEnable;
}

bool ASpatialMeshActorPICO::ClearMesh()
{
	for (const auto Pair : EntityToMeshMap)
	{
		if (Pair.Value)
		{
			Pair.Value->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Pair.Value->Clear();
			Pair.Value->DestroyComponent();
		}
	}
	EntityToMeshMap.Empty();
	MeshInfoQueue.Empty();
	FSpatialMeshExtensionPICO::GetInstance()->ClearMeshProviderBuffer();
	
	return true;
}

int32 ASpatialMeshActorPICO::GetMeshNum()
{
	return EntityToMeshMap.Num();
}

int32 ASpatialMeshActorPICO::GetDrawsNum()
{
	return NumDrawCalls;
}

int32 ASpatialMeshActorPICO::GetDrawnPrimitives()
{
	return DrawnPrimitives;
}

FColor ASpatialMeshActorPICO::GetColorBySceneLabel(ESemanticLabelPICO SceneLabel)
{
	return SemanticToColors.Contains(SceneLabel)?SemanticToColors[SceneLabel]:FColor::MakeRandomSeededColor(static_cast<int32>(SceneLabel));
}

bool ASpatialMeshActorPICO::UpdateMeshByMeshInfo(USpatialMeshComponentPICO* SpatialMesh, const FSpatialMeshInfoPICO& MeshInfo)
{
	if (SpatialMesh)
	{
		TArray<MRMESH_INDEX_TYPE> TempIndices;
		TArray<FVector> TempVertices;
		TArray<FColor> VertexColors;
		const UPICOOpenXRRuntimeSettings* Settings = GetDefault<UPICOOpenXRRuntimeSettings>();
		TArray<FVector> EmptyNormals;
		TArray<FVector2D> EmptyUV;

		if (Settings->bSemanticsAlignWithTriangle)
		{
			for (int32 Index = 0; Index < MeshInfo.Semantics.Num(); ++Index)
			{
				ESemanticLabelPICO Semantic = MeshInfo.Semantics[Index];
				int32 IndicesIndex = Index * 3;

				if (MeshInfo.Indices.IsValidIndex(IndicesIndex + 0)
					&& MeshInfo.Indices.IsValidIndex(IndicesIndex + 1)
					&& MeshInfo.Indices.IsValidIndex(IndicesIndex + 2))
				{
					int32 VerticesIndex0 = MeshInfo.Indices[IndicesIndex + 0];
					int32 VerticesIndex1 = MeshInfo.Indices[IndicesIndex + 1];
					int32 VerticesIndex2 = MeshInfo.Indices[IndicesIndex + 2];

					int32 IndicesStart = TempVertices.Num();

					if (MeshInfo.Vertices.IsValidIndex(VerticesIndex0)
						&& MeshInfo.Vertices.IsValidIndex(VerticesIndex1)
						&& MeshInfo.Vertices.IsValidIndex(VerticesIndex2))
					{
						TempVertices.Add(MeshInfo.Vertices[VerticesIndex0]);
						TempVertices.Add(MeshInfo.Vertices[VerticesIndex1]);
						TempVertices.Add(MeshInfo.Vertices[VerticesIndex2]);

						TempIndices.Add(IndicesStart + 0);
						TempIndices.Add(IndicesStart + 1);
						TempIndices.Add(IndicesStart + 2);

						VertexColors.Add(GetColorBySceneLabel(Semantic));
						VertexColors.Add(GetColorBySceneLabel(Semantic));
						VertexColors.Add(GetColorBySceneLabel(Semantic));

						SpatialMesh->AddAnchorToSceneLabel(Index, Semantic);
					}
				}
			}
		}
		else
		{
			TempVertices = MeshInfo.Vertices;
			if (Settings->bSemanticsAlignWithVertex)
			{
				for (int32 Index = 0; Index < MeshInfo.Semantics.Num(); ++Index)
				{
					ESemanticLabelPICO Semantic = MeshInfo.Semantics[Index];
					VertexColors.Add(GetColorBySceneLabel(Semantic));
				}

				for (int32 Index = 0; Index < MeshInfo.Indices.Num() / 3; ++Index)
				{
					ESemanticLabelPICO SemanticLabel = MeshInfo.Semantics[MeshInfo.Indices[Index * 3]];
					SpatialMesh->AddAnchorToSceneLabel(Index, SemanticLabel);
				}
			}

			if (MeshInfo.Vertices.Num() && MeshInfo.Indices.Num())
			{
				TempIndices.Empty(MeshInfo.Indices.Num());
				Algo::Transform(MeshInfo.Indices, TempIndices, [](const auto& Indice) { return static_cast<MRMESH_INDEX_TYPE>(Indice); });
			}
		}

		if (TempVertices.Num() && TempIndices.Num())
		{
			SpatialMesh->UpdateMesh(MeshInfo.MeshPose.GetLocation(), MeshInfo.MeshPose.GetRotation(),
			                        FVector(1, 1, 1), TempVertices, TempIndices, TArray<FVector2D>(), TArray<FPackedNormal>(), VertexColors);
		}
	}


	return false;
}
