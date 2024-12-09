// Fill out your copyright notice in the Description page of Project Settings.

#include "Tarea2UtilsLib.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"

#include "Engine/StaticMeshActor.h"

#pragma region ListAssetsHelpers
FString GenerateIndentation(int32 Level)
{
	FString Indentation;
	for (int32 i = 0; i < Level; ++i)
	{
		Indentation += TEXT("   "); // Tres espais per nivell
	}
	return Indentation;
}

void ListDependenciesStack(const FName& RootAssetName, IAssetRegistry& AssetRegistry, TArray<FString>& OutputLines)
{
	// Pila para procesar los assets
	TArray<TPair<FName, int32>> Stack_AssetLevel; 
	Stack_AssetLevel.Push(TPair<FName, int32>(RootAssetName, 0));

	while (Stack_AssetLevel.Num() > 0)
	{
		TPair<FName, int32> Current = Stack_AssetLevel.Pop(); 
		FName CurrentAssetName = Current.Key;
		int32 Level = Current.Value;

		FString Indentation = GenerateIndentation(Level);
		OutputLines.Add(FString::Printf(TEXT("%s|- %s"), *Indentation, *CurrentAssetName.ToString()));

		TArray<FName> Dependencies;
		AssetRegistry.GetDependencies(CurrentAssetName, Dependencies);

		for (const FName& DependencyName : Dependencies)
		{
			Stack_AssetLevel.Push(TPair<FName, int32>(DependencyName, Level + 1));
		}
	}
}
#pragma endregion ListAssetsHelpers

void UTarea2UtilsLib::ListAssetsDependencies(const FARFilter& Filter, const FString& InFileName)
{
	const auto& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	TArray<FAssetData> AssetDataList;
	AssetRegistry.GetAssets(Filter,AssetDataList);

	TArray<FString> OutputLines;
	
	for (const FAssetData& AssetData : AssetDataList)
	{
		FString RootAssetName = AssetData.AssetName.ToString();
		OutputLines.Add( FString::Printf(TEXT("AssetRoot [ROOT]: %s\n"), *RootAssetName));

		//Recursiva
		ListDependenciesStack(AssetData.PackageName, AssetRegistry, OutputLines);
	}
	
	FString OutputText = FString::Join(OutputLines, TEXT("\n"));	

	FString FilePath = FPaths::ProjectSavedDir() / InFileName + FDateTime::Now().ToString() + TEXT(".log");

	if (FFileHelper::SaveStringToFile(OutputText, *FilePath))
	{
		UE_LOG(LogTemp, Log, TEXT("Archivo generado correctamente: %s"), *FilePath);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No se pudo generar el archivo: %s"), *FilePath);
	}
}

void UTarea2UtilsLib::ExportStringArrayToFile(const TArray<FString>& InExportList, const FString& InFileName)
{
	if (InExportList.IsEmpty())
		return;

	FString OutputText;
	for (const auto& AssetName : InExportList)
	{
		OutputText.Append(AssetName + '\n');
	}

	FString FilePath = FPaths::ProjectSavedDir() / InFileName + FDateTime::Now().ToString() + TEXT(".log");
	if (FFileHelper::SaveStringToFile(OutputText, *FilePath))
	{
		UE_LOG(LogTemp, Log, TEXT("Archivo generado correctamente: %s"), *FilePath);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No se pudo generar el archivo: %s"), *FilePath);
	}
}


bool HasMoreThanXTris(const AStaticMeshActor* InStaticMeshActor, const int32& InNumOfTris)
{
	const UStaticMeshComponent* MeshComponent = InStaticMeshActor->GetStaticMeshComponent();
	if (!MeshComponent)	return false;
	const UStaticMesh* Mesh = MeshComponent->GetStaticMesh();
	if (!Mesh->GetRenderData())	return false;

	int32 TotalTriangles = 0;
	for (int32 LODIndex = 0; LODIndex < Mesh->GetNumLODs(); ++LODIndex)
	{
		const FStaticMeshLODResources& LODResources = Mesh->GetRenderData()->LODResources[LODIndex];
		for (const FStaticMeshSection& Section : LODResources.Sections)
		{
			TotalTriangles += Section.NumTriangles;
		}
	}

	if (TotalTriangles > InNumOfTris)
		return true;

	return false; 
}

bool HasMoreThanXMaterialSlots(const AStaticMeshActor* InStaticMeshActor, const int32& InNumSlots)
{
	const UStaticMeshComponent* MeshComponent = InStaticMeshActor->GetStaticMeshComponent();
	if (!MeshComponent)	return false;
	const UStaticMesh* Mesh = MeshComponent->GetStaticMesh();
	if (!Mesh->GetRenderData())	return false;
	
	const int32 MaterialSlots = Mesh->GetStaticMaterials().Num();
	if (MaterialSlots > InNumSlots)
		return true; 

	return false;
}

bool AbsoluteSpaceHigherThanX(const AStaticMeshActor* InStaticMeshActor, float InNumUnits)
{
	
	const UStaticMeshComponent* MeshComponent = InStaticMeshActor->GetStaticMeshComponent();
	if (!MeshComponent) return false;

	const FBoxSphereBounds Bounds = MeshComponent->Bounds;
	const FVector BoxExtent = Bounds.BoxExtent;
	const FVector BoxSize = BoxExtent * 2.0f;   // Tamaño total (longitud, ancho, altura)

	float AbsoluteSize = BoxSize.X * BoxSize.Y * BoxSize.Z;

	if (AbsoluteSize > InNumUnits)
		return true; 

	return true;
}

void WriteJson(const FString& String, bool bHasManyTris, bool bHasManyMats, bool bIsMassive)
{
	 IFileManager& FileManager = IFileManager::Get();
	
}

bool UTarea2UtilsLib::EvaluateSMConditions(const AStaticMeshActor* InStaticMeshActor)
{
	bool bHasManyTris = HasMoreThanXTris(InStaticMeshActor, 10000);
	bool bHasManyMats = HasMoreThanXMaterialSlots(InStaticMeshActor, 5);
	bool bIsMassive = AbsoluteSpaceHigherThanX(InStaticMeshActor, 6000);

	// SMJsonList.Add(FString::Printf(TEXT("%s { bHasManyTri: %s, bHasManyMats: %s, bIsMassive: %s }"),
	// 	InStaticMeshActor->GetName(),
	// 	bHasManyTris,
	// 	bHasManyMats,
	// 	bIsMassive));
	
	return bHasManyTris && bHasManyMats && bIsMassive;
}
